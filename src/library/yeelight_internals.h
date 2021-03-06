// yeelight_integration.c
char * yeelight_integration_get_lamps();
void yeelight_integration_send_command(YEELIGHT_LAMP * this, const char * command);

// yeelight_lamp.c
void yeelight_send_command(YEELIGHT_LAMP * this, const char * command, ...);
void yeelight_lamp_dispose(YEELIGHT_LAMP ** this);
static inline char * extract_parameters(va_list args);
