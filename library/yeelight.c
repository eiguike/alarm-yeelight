#include <stdlib.h>
#include <stdio.h>

#include "yeelight.h"
#include "../library/yeelight_internal_headers.h"

void not_implemented() {
  printf("Not implemented.\n");
}

void yeelight_set_lamp(YEELIGHT_DETECTOR * this, YEELIGHT_INFORMATION * lamp) {
  yeelight_udp_set_lamp();
}

YEELIGHT_INFORMATION ** yeelight_get_lamp(YEELIGHT_DETECTOR * this) {
  char * pointer = yeelight_udp_get_lamp();
  printf("%s\n", pointer);

  free(pointer);
  return NULL;
}

YEELIGHT_DETECTOR * yeelight_new() {
  YEELIGHT_DETECTOR * p_yeelight = NULL;

  p_yeelight = calloc(1, sizeof(YEELIGHT_DETECTOR));

  if (p_yeelight == NULL) {
    printf("Something is not cool...\n");
    exit(1);
  }

  p_yeelight->get_lamp = yeelight_get_lamp;
  p_yeelight->set_lamp = yeelight_set_lamp;
  p_yeelight->dispose = not_implemented;

  return p_yeelight;
}
