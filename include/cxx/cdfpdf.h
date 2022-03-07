#ifndef CPP_CDFPDF_H
#define CPP_CDFPDF_H
#include "../defines.h"
#include "oop/container.hpp"

namespace UCA_L2INFO_PW4
{
    class ProbabilityDF
    {
        HashMap<String, double> pdf;
    public:
        ProbabilityDF() = default;
        ProbabilityDF(const ProbabilityDF& obj);
        virtual ~ProbabilityDF() = default;

        double getProbabilityFrom(String group) const;
    };

    class CumulativeDF
    {
        struct CDFNode : public Comparable<CDFNode>
        {
            double cumulativeProbability;

            int compareTo(const CDFNode &node) override;
        };

        SortedList<CDFNode> _F_cdf;
    public:
        CumulativeDF(const ProbabilityDF& df);
        CumulativeDF(const CumulativeDF& obj);
        virtual ~CumulativeDF() = default;

        double getCdfFrom(String group) const;
        uint_t drawVariate();
    };
}

#endif //CPP_CDFPDF_H
