#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "yeelight.h"
#include "logger.h"

LOGGER * gLogger = NULL;

int main() {
  int index = 0;
  YEELIGHT_LAMP * lamps = NULL;

  gLogger = Logger_New(STDOUT, INFOS_AND_ERRORS);

  for(index = 0; lamps == NULL && index < 3; index++) {
    INFO("Trying to find for new lamps");
    lamps = yeelight_get_lamps();
  }

  if (lamps == NULL) {
    ERROR("Failed to connect to Yeelight lamp");
    goto FINISH;
  }

  char buffer[1024] = { 0 };

  for (;index < 150; index++) {
    lamps->send_command(lamps, "set_power", "off", NULL);
    sleep(1);

    lamps->send_command(lamps, "set_power", "on", NULL);
    sleep(1);
  }
  lamps->dispose(&lamps);

FINISH:
  gLogger->Dispose(gLogger);

  return 0;
}
