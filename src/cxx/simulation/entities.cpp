#include "cxx/simulation/entities.h"

namespace UCA_L2INFO_PW4
{
    hash_t Rabbit::hashCode()
    {
        return hash_code;
    }

    uint_t Rabbit::getLifetime() const
    {
        return this->lifetime;
    }

    EntityManager::EntityManager(): unusedHash(1000000)
    {
        /* ... */
    }

    hash_t EntityManager::generateHashCode()
    {
        if (currentUnusedHash != 0xffffffffffffffff)
        {
            return currentUnusedHash++;
        }
        else if (!unusedHash.isEmpty())
        {
            return unusedHash.next();
        }
        else
        {
        }
    }
}
