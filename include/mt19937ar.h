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