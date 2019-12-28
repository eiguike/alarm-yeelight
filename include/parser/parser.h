#ifndef PARSER_H
#define PARSER_H

typedef struct _PARSER {
  void * buffer;
  int buffer_size;

  int last_symbol;

  void (*load_buffer)(struct _PARSER * this, void * buffer, int buffer_size);
  void * (*parse)(struct _PARSER * this);
  void (*dispose)(struct _PARSER *this);

  // Internal commands
  void (*next_token)(struct _PARSER * this);
} PARSER;

PARSER * parser_new();

#endif
