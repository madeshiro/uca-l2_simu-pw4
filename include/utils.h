#ifndef C_UTILS_H
#define C_UTILS_H
#include "defines.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    __uint128_t fibo(uint_t n);
    void open_webpage(const char* url);

    char* int128str(llong_t);
    char* uint128str(ullong_t);

#ifdef __cplusplus
};
#endif //__cplusplus
#endif // C_UTILS_H