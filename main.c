#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "yeelight.h"
#include "logger.h"

LOGGER * gLogger = NULL;

int main() {
  gLogger = Logger_New(STDOUT);

  YEELIGHT_LAMP * lamps = yeelight_get_lamps();

  lamps->power = 0;
  lamps->set_power(lamps);
  sleep(2);

  lamps->power = 1;
  lamps->set_power(lamps);
  sleep(2);

  lamps->dispose(&lamps);

  return 0;
}
