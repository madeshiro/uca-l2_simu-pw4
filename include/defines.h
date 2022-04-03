#ifndef DEFINES_H
#define DEFINES_H

typedef unsigned short      ushort_t;
typedef unsigned int        uint_t;
typedef unsigned long long  ulong_t;

typedef signed short        short_t;
typedef signed int          int_t;
typedef signed long long    long_t;
typedef long double         ldouble_t;

typedef unsigned char       bool_t;
typedef unsigned long long  hash_t;
typedef __SIZE_TYPE__       size_t;

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
#else
#define foreach(type, elem, obj) { \
        Iterator<type>& __iter = obj.iterator(); \
        if (__iter.hasNext())\
        {\
            for (auto elem ;__iter.hasNext(); elem=__iter.next()) { \
                \
            } \
        }

#define cforeach(type, elem, obj)  \
        ConstIterator<type> __iter = obj.const_iterator(); \
        for (const type* __begin = __iter._F_begin; __begin < __iter._F_end; __begin++) \
        { const auto elem = *__begin;

#endif

#ifndef __nullable
#define __nullable
#endif // __nullable

#endif // DEFINES_H
