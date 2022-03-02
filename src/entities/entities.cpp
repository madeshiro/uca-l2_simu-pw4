#include "entities.h"

namespace UCA_L2INFO_PW4
{
    hash_t Entities::hashCode() const
    {
        return (getEntityType() << 8);
    }

    uint_t Entities::getLifetime() const
    {
        return this->lifetime;
    }
}
