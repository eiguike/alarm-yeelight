#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#include "yeelight_datagram.h"

#define MAXLINE 1024 

char *hello = "M-SEARCH * HTTP/1.1\r\nMAN: \"ssdp:discover\"\r\nST: wifi_bulb\r\n"; 

// Driver code 
int lokura_connect() { 
  // Structs needed
  struct in_addr localInterface;
  struct sockaddr_in groupSock;
  struct sockaddr_in localSock;
  struct ip_mreq group;

  // Create the Socket
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
  localInterface.s_addr = inet_addr("192.168.64.234");

  setsockopt(udpSocket, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));

  // Bind to the proper port number with the IP address specified as INADDR_ANY.
  memset((char *) &localSock, 0, sizeof(localSock));
  localSock.sin_family = AF_INET;
  localSock.sin_port = htons(1982);
  localSock.sin_addr.s_addr = INADDR_ANY;

  bind(udpSocket, (struct sockaddr*)&localSock, sizeof(localSock));

  // Join the multicast group on the local interface. Note that this IP_ADD_MEMBERSHIP option must be called for each local interface over which the multicast datagrams are to be received.
  group.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
  group.imr_interface.s_addr = inet_addr("192.168.64.234");

  setsockopt(udpSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));

  sendto(udpSocket, hello, 68, 0, (struct sockaddr*)&groupSock, sizeof(groupSock));


  struct sockaddr_in si_other;
  socklen_t slen = sizeof(si_other);
  char buffer[1024];

  recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *) &si_other, &slen);
  printf("%s", buffer);
} 
