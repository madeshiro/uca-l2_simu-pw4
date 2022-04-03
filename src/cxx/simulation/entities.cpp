#include "cxx/simulation/entities.h"
#include "cxx/simulation/experiment.h"
#include "mt19937ar.h"
#include "cxx/application.h"


namespace UCA_L2INFO_PW4
{
    Rabbit::Rabbit(bool isFemale, hash_t hash, ushort_t maturity): _F_hash_code(hash),
        _F_lifetime(0),
        _F_female(isFemale),
        _F_maturity(maturity)
    {
        /* ... */
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
            if (_F_lifetime < 7)
            {
                return .75;
            }
            else
            {
                return .75 - (.15 * (_F_lifetime-7.));
            }
        }
        else return .50;
    }

    EntityManager::EntityManager(Simulation* parent):
            pdfReproduction("reproduction"),
            pdfLitter("litter"),
            pdfMaturity("maturity"),
            parent(parent)
    {

    }

    EntityManager::~EntityManager()
    {
        delete maleRabbits;
        delete femaleRabbits;

        delete cdfReproduction;
        delete cdfLitter;
        delete cdfMaturity;
    }

    void EntityManager::doReproduction(Rabbit & rabbit)
    {
        // Condition for a Rabbit to be able to reproduce:
        // - There remain males
        // - Rabbit is a female
        // - Rabbit is fertile
        // - Rabbit hasn't done it maximum number of litter this year
        if (maleRabbits->size() > 0 && rabbit.isFemale() && rabbit.isFertile())
        {
            if (rabbit.getLifetime()%12 == 0)
            {
                rabbit.setLitter(cdfLitter->draw()+3);
            }

            if (rabbit.doLitter())
            {
                int birthAmount(cdfReproduction->draw()+2);
                for (int i(0); i < birthAmount; i++)
                {
                    bool female(genrand_real1() < .50);
                    ushort_t maturity(cdfMaturity->draw() + 5); // group 0 == 5 month to be mature

                    Rabbit kitten(female, generateHashCode(female), maturity);
                    reproduction(kitten);

                    // Test childbirth
                    if (genrand_real1() < .50)
                    {
                        die_childbirth();
                    } else
                    {
                        (female ? femaleRabbits : maleRabbits)->add(kitten);
                    }
                }
            }
        }
    }

    void EntityManager::doSurvive(Rabbit & rabbit)
    {
        if (genrand_real1() < rabbit.deathProbability())
        {
            if (rabbit.isFemale())
            {
                if (!femaleRabbits->remove(rabbit))
                    Application::app->out->severe().println("Unable to remove a rabbit from the collection !");
            }
            else
            {
                if (!maleRabbits->remove(rabbit))
                    Application::app->out->severe().println("Unable to remove a rabbit from the collection !");
            }

            die();
            if (rabbit.getLifetime() == 12)
            {
                die_from_age();
            }
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

    BinaryStream EntityManager::exportBinary() const
    {
        return BinaryStream(); // Todo exportBinary
    }

    Binaries& EntityManager::loadBinary(BinaryStream stream [[gnu::unused]])
    {
        // Todo loadBinary
        return *this;
    }
}
