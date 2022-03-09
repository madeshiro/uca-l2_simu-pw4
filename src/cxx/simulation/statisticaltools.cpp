#include "cxx/simulation/statisticaltools.h"

namespace UCA_L2INFO_PW4
{
    hash_t StatisticalBins::Interval::hashCode()
    {
        union {
            double v;
            void*  ptr;
        } b1, b2;

        b1.v = min;
        b2.v = max;

        return (hash_t) b1.ptr << 32 | (hash_t) b2.ptr;
    }
}