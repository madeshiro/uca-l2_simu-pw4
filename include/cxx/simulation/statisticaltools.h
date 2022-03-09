#ifndef CPP_STATISTICALTOOLS_H
#define CPP_STATISTICALTOOLS_H
#include "cxx/oop/container.hpp"
#include "cxx/json/json.h"
#include "cxx/oop/binary.h"

namespace UCA_L2INFO_PW4
{
    using json::JsonStringifyable;

    class Histogram : public JsonStringifyable, Binaries
    {
    protected:
        HashMap<Object, ulong_t> _F_bins;
        ulong_t _F_total;
        ulong_t _F_pop;
    public:
        Histogram();
        Histogram(const Histogram& histo);
        virtual ~Histogram() = default;

        virtual ulong_t getPopulation() const;
        virtual ulong_t getValuesSum() const;

        virtual ulong_t add(const Object& which, ulong_t amount);
        virtual ulong_t set(const Object& which, ulong_t amount);
        virtual void    remove(const Object& which);
    };

    class StatisticalBins : public Histogram
    {
        struct Interval : public Object
        {
            double min, max;

            virtual hash_t hashCode() override;
        } _F_interval;
    public:
        StatisticalBins(double min, double interval, uint_t count);
        virtual ~StatisticalBins() override;

        long_t increment(double which, long_t many = 1);

        String toString() override;
    };
}

#endif //CPP_STATISTICALTOOLS_H
