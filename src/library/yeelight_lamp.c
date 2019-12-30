#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "yeelight.h"
#include "yeelight_internals.h"
#include "logger.h"

#define YEELIGHT_COMMAND_FORMAT "{\"id\": %d, \"method\": \"%s\", \"params\": [%s]}\r\n"

YEELIGHT_LAMP * yeelight_lamp_new() {
  YEELIGHT_LAMP * lamp = calloc(1, sizeof(YEELIGHT_LAMP));

  lamp->send_command = yeelight_send_command;
  lamp->set_power = yeelight_udp_set_lamp;
  lamp->dispose = yeelight_lamp_dispose;

  return lamp;
}

YEELIGHT_LAMP * yeelight_get_lamps() {
  char * p_buffer = NULL;
  char * buffer = yeelight_udp_get_lamps();
  YEELIGHT_LAMP * lamp = NULL;

  if (strlen(buffer) == 0) {
    ERROR("Couldn't identify Yeelight lamps, try again...");
    goto FINISH;
  }

  lamp = yeelight_lamp_new();
  
  char ip[1024] = { 0 };

  p_buffer = strstr(buffer, "id: ");
  sscanf(p_buffer, "id: %x\r\n", &(lamp->id));
  p_buffer = strstr(buffer, "Location: ");
  sscanf(p_buffer, "Location: yeelight://%[^:]s:55443\r\n", ip);

  lamp->location = calloc(strlen(ip), sizeof(char));
  strcpy(lamp->location, ip);

FINISH:
  free(buffer);

  return lamp;
}

void yeelight_lamp_dispose(YEELIGHT_LAMP ** this) {
  if (*this != NULL) {
    free(*this);
  }
  *this = NULL;
}

static inline char * extract_parameters(va_list args){
  char * buffer = calloc(1024, sizeof(char));
  char * pointer;
  int size = 0;

  for (;;) {
    pointer = va_arg(args, char*);

    if (pointer == NULL) break;

    size = strlen(buffer);
    if (atoi(pointer) != 0 || (strlen(pointer) == 1)) {
      sprintf(buffer + size, "%s, ", pointer);
    } else {
      sprintf(buffer + size, "\"%s\", ", pointer);
    }
  }

  size = strlen(buffer);
  buffer[size - 2] = '\0';

  return buffer;
}

void yeelight_send_command(YEELIGHT_LAMP * this, const char * command, ...) {
  char * variables;
  char buffer[1024] = { 0 };
  int index = 0;

  va_list args;
  va_start(args, command);
  variables = extract_parameters(args); 
  va_end(args);

  sprintf(buffer, YEELIGHT_COMMAND_FORMAT, this->id, command, variables);

  yeelight_udp_send_command(this, buffer);

  free(variables);
}
