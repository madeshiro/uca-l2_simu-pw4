#include "cxx/simulation/cdfpdf.h"

namespace UCA_L2INFO_PW4
{
    int CumulativeDF::CDFNode::compareTo(const CDFNode &node)
    {
        if (this->cumulativeProbability == node.cumulativeProbability)
        {
            return 0;
        }
        else
        {
            return this->cumulativeProbability < node.cumulativeProbability ?
                -1 : 1;
        }
    }
}