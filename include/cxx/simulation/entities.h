#ifndef CPP_ENTITIES_H
#define CPP_ENTITIES_H
#include "defines.h"
#include "cxx/oop/object.h"
#include "cxx/oop/container.hpp"
#include "cxx/json/json.h"
#include "cxx/oop/binary.h"
#include "statisticaltools.h"

namespace UCA_L2INFO_PW4
{
    using json::JsonStringifyable;
    using json::Json;

    /**
     * Female rabbits
     */
    class Rabbit final : public JsonStringifyable
    {
        friend class EntityManager;
    private:
        hash_t _F_hash_code;
        uint_t _F_lifetime;
        bool   _F_female;
        ushort _F_maturity;

        int _F_litter;
    public:
        Rabbit(bool isFemale, hash_t hash, ushort_t maturity);
        ~Rabbit() noexcept override;

        hash_t hashCode() const override;
        uint_t getLifetime() const;
        bool isFertile() const;
        bool isFemale() const;
        bool isAdult() const;

        void setLitter(int litter);
        bool doLitter();

        double deathProbability() const;
        // virtual String toString() const override;
        uint_t getMaturity() const;
        void increaseLifetime();
    };

    class Simulation;
    class EntityManager final : public JsonStringifyable, Binaries
    {
        friend class Simulation;

        hash_t hashCodeMaleRabbits   = 0x0;
        hash_t hashCodeFemaleRabbits = 0x0;

        SharedPointer<Vector<Rabbit*>> maleRabbits;
        SharedPointer<Vector<Rabbit*>> femaleRabbits;

        Simulation* parent;
    events:
        event(uint_t /*lifetime*/) die;
        event() die_from_age;
        event() die_childbirth;
        event(const Rabbit*) reproduction;
    public:
        EntityManager(Simulation* parent);
        virtual ~EntityManager() final;

        Rabbit *createAdult(bool female);

        void doReproduction(Rabbit*);
        bool doSurvive(Rabbit*);

        hash_t generateHashCode(bool female);

        virtual BinaryStream exportBinary() const override;
        virtual Binaries&  loadBinary(BinaryStream stream) override;

        EntityManager& operator =(const EntityManager& entityManager);
    };
}

#endif //CPP_ENTITIES_H
