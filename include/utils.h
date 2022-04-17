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

    void* memcopy(void* ptr, size_t nmembn, size_t __sizeof);

    char* doublestr(double d);

#ifdef __cplusplus
};
#endif //__cplusplus
#endif // C_UTILS_H