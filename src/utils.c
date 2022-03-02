#include "utils.h"

ulong_t fibo(uint_t n)
{
    static ulong_t init_state[2] = {1, 1};

    if (n < 2)
        return init_state[n];
    else
        return fibo(n-1) + fibo(n-2);
}