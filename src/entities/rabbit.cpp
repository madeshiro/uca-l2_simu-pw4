#include "../../include/entities.h"

namespace UCA_L2INFO_PW4
{
    Rabbit::~Rabbit()
    {

    }

    Entities::Type Rabbit::getEntityType() const noexcept
    {
        return Entities::Rabbit;
    }
}
