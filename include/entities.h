#ifndef CPP_ENTITIES_H
#define CPP_ENTITIES_H
#include "defines.h"

namespace UCA_L2INFO_PW4
{
    class Entities
    {
    private:
        uint_t lifetime;
    public:
        enum Type {
            Rabbit = 0x100,
            Predator = 0x200
        };

        Entities() = default;
        virtual ~Entities() = 0;

        hash_t hashCode() const;
        virtual Entities& reproduction() = 0;
        virtual Entities::Type getEntityType() const = 0;

        virtual uint_t getLifetime() const final;
    };

    class Rabbit : public Entities
    {
    public:
        Rabbit() = default;
        virtual ~Rabbit();

        Entities::Type getEntityType() const noexcept override;
    };
}

#endif //CPP_ENTITIES_H
