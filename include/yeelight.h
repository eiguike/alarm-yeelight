#ifndef YEELIGHT_H
#define YEELIGHT_H

#define NEW_LINE_CHARS 2
#define START_CHAR 18
#define HOST_CHAR 20
#define MAN_CHAR 13 
#define ST_CHAR 9

typedef struct _YEELIGHT_DATAGRAM {
  char start[START_CHAR + NEW_LINE_CHARS];
  char host[HOST_CHAR + NEW_LINE_CHARS];
  char man[MAN_CHAR + NEW_LINE_CHARS];
  char st[ST_CHAR + NEW_LINE_CHARS];
} YEELIGHT_DATAGRAM;

typedef struct _YEELIGHT_INFORMATION {
  int cache_control;
  char * date;
  char * ext;
  char * location;
  char * server;
  char * id;
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
} YEELIGHT_INFORMATION;

typedef struct _YEELIGHT_DETECTOR {
  YEELIGHT_INFORMATION** (*get_lamp)(struct _YEELIGHT * this); 
  void (*set_lamp)(struct _YEELIGHT_DETECTOR * this, YEELIGHT_INFORMATION * lamp);
  void (*dispose)(struct _YELLIGHT_DETECTOR ** this);
} YEELIGHT_DETECTOR;

YEELIGHT_DETECTOR * yeelight_new();

#endif
