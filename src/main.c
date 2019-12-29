#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "yeelight.h"
#include "logger.h"

LOGGER * gLogger = NULL;

int main() {
  gLogger = Logger_New(STDOUT);

  YEELIGHT_LAMP * lamps = yeelight_get_lamps();

  int index = 0;

  for (;index < 150; index++) {
    lamps->power = 0;
    lamps->set_power(lamps);
    sleep(1);

    lamps->power = 1;
    lamps->set_power(lamps);
    sleep(1);
  }

  return 0;
}
