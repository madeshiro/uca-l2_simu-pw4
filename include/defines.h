#ifndef DEFINES_H
#define DEFINES_H

typedef unsigned int        uint_t;
typedef unsigned long long  ulong_t;

typedef signed int          int_t;
typedef signed long long    long_t;
typedef long double         ldouble_t;

typedef unsigned char       bool_t;
typedef unsigned long long  hash_t;

#ifdef __SIZEOF_INT128__
typedef __uint128_t         ullong_t;
typedef __int128_t          llong_t;
#else
typedef unsigned long long  ullong_t;
typedef long long           llong_t;
#endif // __SIZEOF_INT128__


#ifndef __cplusplus
#define true    1
#define false   0
#endif

#define __in
#define __out
#ifndef __nullable
#define __nullable
#endif // __nullable

#endif // DEFINES_H
