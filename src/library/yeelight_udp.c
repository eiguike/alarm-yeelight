#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include "yeelight.h"
#include "logger.h"

#define FIXED_LOCAL_ADDRESS "192.168.0.1"
#define SEARCH_PROTOCOL "M-SEARCH * HTTP/1.1\r\nMAN: \"ssdp:discover\"\r\nST: wifi_bulb\r\n"
#define TURN_LAMP "{\"id\": %d, \"method\": \"set_power\", \"params\": [\"%s\"]}\r\n"

const char * turn_lamp_func(int i) {
  if (i){
    return "on";
  }
  return "off";
}

char * yeelight_udp_get_lamps() { 
  struct in_addr localInterface;
  struct sockaddr_in groupSock;
  struct sockaddr_in localSock;
  struct ip_mreq group;

  int udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

  // Enable SO_REUSEADDR to allow multiple instances of this application to receive copies of the multicast datagrams.
  int reuse = 1;
  setsockopt(udpSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));

  // Initialize the group sockaddr structure with a group address of 239.255.255.250 and port 1900.
  memset((char *) &groupSock, 0, sizeof(groupSock));

  groupSock.sin_family = AF_INET;
  groupSock.sin_addr.s_addr = inet_addr("239.255.255.250");
  groupSock.sin_port = htons(1982);

  // Disable loopback so you do not receive your own datagrams.
  char loopch = 0;
  setsockopt(udpSocket, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch));

  // Set local interface for outbound multicast datagrams. The IP address specified must be associated with a local, multicast capable interface.
  localInterface.s_addr = inet_addr(FIXED_LOCAL_ADDRESS);

  setsockopt(udpSocket, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));

  // Bind to the proper port number with the IP address specified as INADDR_ANY.
  memset((char *) &localSock, 0, sizeof(localSock));
  localSock.sin_family = AF_INET;
  localSock.sin_port = htons(1982);
  localSock.sin_addr.s_addr = INADDR_ANY;

  bind(udpSocket, (struct sockaddr*)&localSock, sizeof(localSock));

  // Join the multicast group on the local interface. Note that this IP_ADD_MEMBERSHIP option must be called for each local interface over which the multicast datagrams are to be received.
  group.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
  group.imr_interface.s_addr = inet_addr(FIXED_LOCAL_ADDRESS);

  setsockopt(udpSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));

  sendto(udpSocket, SEARCH_PROTOCOL, 68, 0, (struct sockaddr*)&groupSock, sizeof(groupSock));

  struct sockaddr_in si_other;
  socklen_t slen = sizeof(si_other);
  char * buffer = calloc(1024, sizeof(char));

  recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *) &si_other, &slen);

  return buffer;
}

void yeelight_udp_set_lamp(YEELIGHT_LAMP * this) { 
  int sockfd, connfd;
  struct sockaddr_in servaddr, cli;

  // socket create and varification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    return;
  }
  else
    printf("Socket successfully created..\n");

  bzero(&servaddr, sizeof(servaddr));

  // assign IP, PORT
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(this->location);
  servaddr.sin_port = htons(55443);

  // connect the client socket to server socket
  if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
  }
  else {
    printf("connected to the server..\n");

    DEBUG("this->id %d", this->id);
    DEBUG("this->location %s", this->location);
    DEBUG("this->power %s", turn_lamp_func(this->power));

    char buffer[1024] = { 0 };
    sprintf(buffer, TURN_LAMP, this->id, turn_lamp_func(this->power));

    DEBUG(buffer);

    write(sockfd, buffer, 62);

    close(sockfd);
  }
} 
