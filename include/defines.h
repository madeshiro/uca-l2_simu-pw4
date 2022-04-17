/*
 * UCA-L2 simulation "practical work #4" : a realistic simulation of rabbit population growth
 * Copyright (C) 2022 -- Rin Baudelet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
#endif

#ifndef __nullable
#define __nullable
#endif // __nullable

#endif // DEFINES_H
