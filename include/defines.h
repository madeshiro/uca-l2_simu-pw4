#ifndef DEFINES_H
#define DEFINES_H

typedef unsigned char       bool_t;
typedef unsigned int        uint_t;
typedef unsigned long long  ulong_t;
typedef long double         ldouble_t;
typedef unsigned long long  hash_t;

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
