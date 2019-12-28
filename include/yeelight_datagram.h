#include <stdio.h>
#include <stdlib.h>

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
