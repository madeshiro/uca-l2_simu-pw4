/*
 * Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * 3. The names of its contributors may not be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * Any feedback is very welcome.
 * http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 * email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
 */
#ifndef MT19937AR_H
#define MT19937AR_H
/* Matsumoto's Mersenne Twister C implementation
 * Define @file mt19937ar.c header
 */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/* Period parameters */
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

    struct mt_state
    {
        unsigned long *mt;
        int mti;
    };

    struct mt_state get_mt_state();
    void set_mt_state(unsigned long _mt[N], int _mti);

    void init_genrand(unsigned long s);
    void init_by_array(unsigned long init_key[], int key_length);
    unsigned long genrand_int32(void);
    long genrand_int31(void);
    double genrand_real1(void);
    double genrand_real2(void);
    double genrand_real3(void);
    double genrand_res53(void);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // MT19937AR_H