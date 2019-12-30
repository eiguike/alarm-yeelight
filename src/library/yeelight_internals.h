char * yeelight_udp_get_lamps();
void yeelight_udp_set_lamp(YEELIGHT_LAMP * this);
void yeelight_udp_send_command(YEELIGHT_LAMP * this, const char * command);
void yeelight_send_command(YEELIGHT_LAMP * this, const char * command, ...);
void yeelight_lamp_dispose(YEELIGHT_LAMP ** this);
