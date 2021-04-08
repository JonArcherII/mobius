#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *memset(void *s, int c, size_t n);

size_t strlen(const char *s);

#ifdef __cplusplus
}
#endif