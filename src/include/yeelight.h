#ifndef YEELIGHT_H
#define YEELIGHT_H

typedef struct _YEELIGHT_LAMP {
  int cache_control;
  char * date;
  char * ext;
  char * location;
  char * server;
  unsigned int id;
  char * model;
  char * firmware_version;
  char * features_supported;
  int power;
  int bright;
  int color_mode;
  int ct;
  int rgb;
  int hue;
  int sat;
  char * name;

  void (*send_command) (struct _YEELIGHT_LAMP * this, const char * command, ...); 
  void (*dispose) (struct _YEELIGHT_LAMP ** this);
} YEELIGHT_LAMP;

YEELIGHT_LAMP * yeelight_lamp_new();
YEELIGHT_LAMP * yeelight_get_lamps();
#endif
