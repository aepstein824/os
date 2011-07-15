#include "string.h"

void *memcpy(void *dest, const void *src, int count) {
    char *dst8 = (char *)dest;
    const char *src8 = (const char *)src;

    while (count--) {
        *dst8 = *src8;
        dst8++;
        src8++;
    }
    return dest;
}
