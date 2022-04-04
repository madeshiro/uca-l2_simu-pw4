#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

__uint128_t fibo_r(uint_t n, uint_t i, __uint128_t f_1, __uint128_t f_2)
{
    if (i == n)
    {
        return f_1 + f_2;
    }
    else
    {
        return fibo_r(n, i+1, f_1 + f_2, f_1);
    }
}

__uint128_t fibo(uint_t n)
{
    return n < 2 ? n%2 : fibo_r(n, 2, 1, 0);
}

uint_t int128strlen(ullong_t ulld)
{
    uint_t strlen = 0;
    do
    {
        ulld/=10;
        strlen++;
    } while(ulld > 0);

    return strlen;
}

char* int128str(llong_t lld)
{
    bool_t neg      = lld < 0 ? true : false;
    lld             = neg ? -lld : lld;
    uint_t strlen   = int128strlen((ullong_t) lld);
    char*  str      = malloc(sizeof(char)*(neg+1+strlen));

    str[strlen+neg] = '\0';
    for (int i = strlen-1; i >= 0; i--)
    {
        str[i] = '0' + lld%10;
        lld/=10;
    }
    return str;
}

char* uint128str(ullong_t ulld)
{
    uint_t strlen   = int128strlen(ulld);
    char*  str      = malloc(sizeof(char)*(1+strlen));

    str[strlen] = '\0';
    for (int i = strlen-1; i >= 0; i--)
    {
        str[i] = '0' + ulld % 10;
        ulld/=10;
    }
    return str;
}

void open_webpage(const char* url)
{
    char* cmd;
    cmd = malloc(sizeof(char)*(strlen(url)+20));
    if (cmd)
    {
#ifdef WIN32
        sprintf(cmd, "start %s", url);
#else
        sprintf(cmd, "firefox %s & jobs", url);
#endif
        system("start");
        free(cmd);
    }
}

void* memcopy(void* ptr, size_t nmemb, size_t __sizeof)
{
    void *cpy = malloc(__sizeof*nmemb);
    if (cpy)
    {
        for (uint_t i = 0; i < nmemb*__sizeof; i++)
        {
            // movb
            ((char*) cpy)[i] = ((char*) ptr)[i];
        }
        return cpy;
    }
    else
    {
        return NULL;
    }
}

char* doublestr(double d)
{
    char* str = calloc(32, sizeof(char));
    sprintf(str, "%lf", d);
    return str;
}