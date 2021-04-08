#pragma once

#ifdef __cplusplus
extern "C" {
#endif

char *itoa(int value, char *str, int base);
char *utoa(unsigned value, char *str, int base);

#ifdef __cplusplus
}
#endif