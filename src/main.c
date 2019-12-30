#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "yeelight.h"
#include "logger.h"

LOGGER * gLogger = NULL;

int main() {
  gLogger = Logger_New(STDOUT, ALL_MESSAGES);

  YEELIGHT_LAMP * lamps = yeelight_get_lamps();

  int index = 0;

  for (;index < 1; index++) {
    lamps->power = 0;
    lamps->set_power(lamps);
    sleep(1);

    lamps->power = 1;
    lamps->set_power(lamps);
    sleep(1);
  }

  lamps->dispose(&lamps);
  gLogger->Dispose(gLogger);

  return 0;
}
