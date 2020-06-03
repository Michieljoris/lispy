#ifndef __IO_H_
#define __IO_H_

#include <stdio.h>

#include "debug.h"

#define printf(...) \
  if (*pdebug_level) printf(__VA_ARGS__);

#define putchar(...) \
  if (*pdebug_level) putchar(__VA_ARGS__);

#endif  // __IO_H_
