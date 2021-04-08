#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern "C" {

void *memset(void *s, int c, size_t n) {
  uint8_t *p = (uint8_t *)s;
  while (n > 0) {
    *p = c;
    ++p;
    --n;
  }
  return s;
}

size_t strlen(const char *str) {
  size_t i = 0;
  while (str[i])
    ++i;
  return i;
}
}