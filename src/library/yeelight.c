#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "yeelight.h"
#include "../library/yeelight_internal_headers.h"
#include "logger.h"

void yeelight_lamp_dispose(YEELIGHT_LAMP ** this) {
  if (*this != NULL) {
    free(*this);
  }
  *this = NULL;
}

YEELIGHT_LAMP * yeelight_lamp_new() {
  YEELIGHT_LAMP * lamp = calloc(1, sizeof(YEELIGHT_LAMP));

  lamp->set_power = yeelight_udp_set_lamp;

  lamp->dispose = yeelight_lamp_dispose;

  return lamp;
}

YEELIGHT_LAMP * yeelight_get_lamps() {
  char * buffer = yeelight_udp_get_lamps();
  char * p_buffer = NULL;

  int buffer_size = strlen(buffer);

  YEELIGHT_LAMP * lamp = yeelight_lamp_new();
  
  char ip[1024] = { 0 };

  p_buffer = strstr(buffer, "id: ");
  sscanf(p_buffer, "id: %x\r\n", &(lamp->id));
  p_buffer = strstr(buffer, "Location: ");
  sscanf(p_buffer, "Location: yeelight://%[^:]s:55443\r\n", ip);

  lamp->location = calloc(strlen(ip), sizeof(char));
  strcpy(lamp->location, ip);

  return lamp;
}
