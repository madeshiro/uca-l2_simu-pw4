#ifndef CPP_ENTITIES_H
#define CPP_ENTITIES_H
#include "defines.h"
#include "cxx/oop/object.h"
#include "cxx/oop/container.hpp"
#include "cxx/json/json.h"
#include "cxx/oop/binary.h"

namespace UCA_L2INFO_PW4
{
    using json::JsonStringifyable;

    class Rabbit : public JsonStringifyable
    {
    private:
        hash_t hash_code;
        uint_t lifetime;
    public:

        Rabbit() = default;
        virtual ~Rabbit() = default;

        virtual hash_t hashCode() override;
        virtual uint_t getLifetime() const final;
        virtual String toString() override;
    };

    class EntityManager final : public JsonStringifyable, Binaries
    {
        hash_t currentUnusedHash = 0;
        Queue<hash_t> unusedHash;

        Collection<Rabbit>* collection;
    public:
        EntityManager();
        virtual ~EntityManager() final;

        hash_t generateHashCode();
    };
}

#endif //CPP_ENTITIES_H
