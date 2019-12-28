#include <stdio.h>
#include <stdlib.h>
#include "yeelight.h"

//int lokura_connect();

int main() {
  printf("Hello world!\n");

  YEELIGHT_DETECTOR * yeelight = yeelight_new();
  YEELIGHT_INFORMATION ** lamps = yeelight->get_lamp(yeelight);

  yeelight->set_lamp(yeelight, NULL);
  yeelight->dispose(&yeelight);

  return 0;
}
