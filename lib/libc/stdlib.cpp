#include <stddef.h>
#include <stdlib.h>

extern "C" {

char *utoa(unsigned value, char *str, int base) {
  const char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  // Ensure we support whatever base was specified
  if ((base < 2) || (base > 36)) {
    str[0] = '\0';
    return NULL;
  }

  // Stringify! Works backwards, so we need to reverse the string later
  size_t i = 0;
  do {
    unsigned remainder = value % base;
    str[i++] = digits[remainder];
    value = value / base;
  } while (value != 0);
  str[i--] = '\0';

  // Reverse string
  for (size_t j = 0; j < i; j++, i--) {
    char c = str[j];
    str[j] = str[i];
    str[i] = c;
  }

  return str;
}

char *itoa(int value, char *str, int base) {
  size_t i = 0;
  // Check if we are negative
  if (value < 0 && base == 10) {
    value = -value;
    str[i++] = '-';
  }
  utoa((unsigned)value, &str[i], base);
  return str;
}
}