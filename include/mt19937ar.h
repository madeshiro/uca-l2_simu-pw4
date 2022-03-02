#ifndef MT19937AR_H
#define MT19937AR_H
/* Matsumoto's Mersenne Twister C implementation
 * Define @file mt19937ar.c header
 */
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

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