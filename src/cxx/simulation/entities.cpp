#include "cxx/simulation/entities.h"
#include "cxx/simulation/experiment.h"
#include "mt19937ar.h"
#include "cxx/application.h"


namespace UCA_L2INFO_PW4
{
    Rabbit::Rabbit(bool isFemale, hash_t hash, ushort_t maturity): _F_hash_code(hash),
        _F_lifetime(0),
        _F_female(isFemale),
        _F_maturity(maturity),
        _F_litter(0)
    {
        /* ... */
    }

    Rabbit::~Rabbit() noexcept
    {
        /* */
    }

    hash_t Rabbit::hashCode() const
    {
        return _F_hash_code;
    }

    uint_t Rabbit::getLifetime() const
    {
        return _F_lifetime;
    }

    bool Rabbit::isFemale() const
    {
        return _F_female;
    }

    bool Rabbit::isAdult() const
    {
        return _F_lifetime >= _F_maturity;
    }

    void Rabbit::setLitter(int litter)
    {
        _F_litter = litter;
    }

    bool Rabbit::doLitter()
    {
        if (_F_litter > 0)
        {
            _F_litter--;
            return true;
        }
        else return false;
    }

    bool Rabbit::isFertile() const
    {
        return genrand_real2() < .90;
    }

    double Rabbit::deathProbability() const
    {
        if (isAdult())
        {
            if (_F_lifetime < 7*12)
            {
                return .25;
            }
            else
            {
                return .25 + (.15 * ((uint_t)(_F_lifetime-7*12)%12));
            }
        }
        else return .50;
    }

    uint_t Rabbit::getMaturity() const
    {
        return _F_maturity;
    }

    void Rabbit::increaseLifetime()
    {
        _F_lifetime++;
    }

    EntityManager::EntityManager(Simulation* parent):
        parent(parent)
    {
        maleRabbits = new Vector<Rabbit*>(256);
        femaleRabbits = new Vector<Rabbit*>(256);
    }

    EntityManager::~EntityManager()
    {
        if (maleRabbits->size() > 0)
        {
            for (Rabbit *rabbit: *maleRabbits)
                delete rabbit;
        }

        if (femaleRabbits->size() > 0)
        {
            for (Rabbit *rabbit: *femaleRabbits)
                delete rabbit;
        }
    }

    void EntityManager::doReproduction(Rabbit * rabbit)
    {
        // Condition for a Rabbit to be able to reproduce:
        // - There remain males
        // - Rabbit is a female
        // - Rabbit is fertile
        // - Rabbit hasn't done it maximum number of litter this year
        if (maleRabbits->size() > 0 && rabbit->isFemale())
        {
            if ((rabbit->getLifetime()-rabbit->getMaturity())%12 == 0 && rabbit->isFertile())
            {
                rabbit->setLitter(parent->experiment()->cdfLitter->drawFromId());
            }

            if (rabbit->doLitter())
            {
                int birthAmount(parent->experiment()->cdfReproduction->drawFromId());
                for (int i(0); i < birthAmount; i++)
                {
                    bool female(genrand_real1() < .50);
                    ushort_t maturity(parent->experiment()->cdfMaturity->drawFromId());

                    Rabbit* kitten = new Rabbit(female, generateHashCode(female), maturity);
                    Application::app->out->format("new <kitten> Rabbit("
                                                  "female:{0}, maturity:{1})\n",
                                                  female, maturity);
                    reproduction(kitten);

                    // Test childbirth
                    if (genrand_real1() < .15)
                    {
                        die_childbirth();
                        delete kitten;
                    }
                    else
                    {
                        (female ? femaleRabbits : maleRabbits)->add(kitten);
                    }
                }
            }
        }
    }

    bool EntityManager::doSurvive(Rabbit * rabbit)
    {
        Application::app->out->format("death probability: {0}\n", rabbit->deathProbability());
        if (genrand_real1() < rabbit->deathProbability())
        {
            if (rabbit->isFemale())
            {
                if (!femaleRabbits->remove(rabbit))
                    Application::app->out->severe().println("Unable to drop a rabbit from the collection !");
            }
            else
            {
                if (!maleRabbits->remove(rabbit))
                    Application::app->out->severe().println("Unable to drop a rabbit from the collection !");
            }

            die(rabbit->getLifetime());
            if (rabbit->getLifetime() == 240)
            {
                die_from_age();
            }

            delete rabbit;
            return false;
        }
        else
        {
            return true;
        }
    }

    hash_t EntityManager::generateHashCode(bool isFemale)
    {
        if (isFemale)
        {
            return hashCodeFemaleRabbits++;
        }
        else
        {
            return hashCodeMaleRabbits++;
        }
    }

    Rabbit* EntityManager::createAdult(bool female)
    {
        Rabbit *adult = new Rabbit(female, generateHashCode(female), parent->experiment()->cdfMaturity->drawFromId());
        adult->_F_lifetime = 8;
        (female ? femaleRabbits : maleRabbits)->add(adult);

        // Application::app->out->format("new <adult> Rabbit("
        //                               "female:{0}, maturity:{1})\n",
        //                               female, adult->_F_maturity);
        return adult;
    }

    BinaryStream EntityManager::exportBinary() const
    {
        return BinaryStream(); // Todo exportBinary
    }

    Binaries& EntityManager::loadBinary(BinaryStream stream [[gnu::unused]])
    {
        // Todo loadBinary
        return *this;
    }

    EntityManager& EntityManager::operator=(const EntityManager &entityManager)
    {
        hashCodeMaleRabbits = entityManager.hashCodeMaleRabbits;
        hashCodeFemaleRabbits = entityManager.hashCodeFemaleRabbits;

        maleRabbits = entityManager.maleRabbits;
        femaleRabbits = entityManager.femaleRabbits;

        parent = entityManager.parent;
        return *this;
    }
}
