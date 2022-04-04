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
                return .75;
            }
            else
            {
                return .75 - (.15 * ((uint_t)(_F_lifetime-7*12)%12));
            }
        }
        else return .50;
    }

    uint_t Rabbit::getMaturity() const
    {
        return _F_maturity;
    }

    EntityManager::EntityManager(Simulation* parent):
            pdfReproduction("reproduction"),
            pdfLitter("litter"),
            pdfMaturity("maturity"),
            parent(parent)
    {
        maleRabbits = new Vector<Rabbit*>(256);
        femaleRabbits = new Vector<Rabbit*>(256);

        pdfReproduction.addGroup("2", 0.125);
        pdfReproduction.addGroup("3", 0.25);
        pdfReproduction.addGroup("4", 0.25);
        pdfReproduction.addGroup("5", 0.25);
        pdfReproduction.addGroup("6", 0.125);
        cdfReproduction = new CumulativeDF(pdfReproduction);

        pdfLitter.addGroup("3",0.08);
        pdfLitter.addGroup("4",0.13);
        pdfLitter.addGroup("5",0.18);
        pdfLitter.addGroup("6",0.22);
        pdfLitter.addGroup("7",0.18);
        pdfLitter.addGroup("8",0.13);
        pdfLitter.addGroup("9",0.08);
        cdfLitter = new CumulativeDF(pdfLitter);

        pdfMaturity.addGroup("5", 0.25);
        pdfMaturity.addGroup("6", 0.20);
        pdfMaturity.addGroup("7", 0.25);
        pdfMaturity.addGroup("8", 0.30);
        cdfMaturity = new CumulativeDF(pdfMaturity);
    }

    EntityManager::~EntityManager()
    {
        delete maleRabbits;
        delete femaleRabbits;

        delete cdfReproduction;
        delete cdfLitter;
        delete cdfMaturity;
    }

    void EntityManager::doReproduction(Rabbit * rabbit)
    {
        // Condition for a Rabbit to be able to reproduce:
        // - There remain males
        // - Rabbit is a female
        // - Rabbit is fertile
        // - Rabbit hasn't done it maximum number of litter this year
        if (maleRabbits->size() > 0 && rabbit->isFemale() && rabbit->isFertile())
        {
            if (rabbit->getLifetime()-rabbit->getMaturity()%12 == 0)
            {
                rabbit->setLitter(cdfLitter->drawFromId());
            }

            if (rabbit->doLitter())
            {
                int birthAmount(cdfReproduction->drawFromId());
                for (int i(0); i < birthAmount; i++)
                {
                    bool female(genrand_real1() < .50);
                    ushort_t maturity(cdfMaturity->drawFromId());

                    Rabbit* kitten = new Rabbit(female, generateHashCode(female), maturity);
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

    bool EntityManager::doSurvive(Rabbit * rabbit)
    {
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
            if (rabbit->getLifetime() == 12)
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
        Rabbit *adult = new Rabbit(female, generateHashCode(female), cdfMaturity->drawFromId());
        (female ? femaleRabbits : maleRabbits)->add(adult);
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

        pdfLitter = entityManager.pdfLitter;
        pdfReproduction = entityManager.pdfReproduction;
        pdfMaturity = entityManager.pdfMaturity;

        cdfReproduction = new CumulativeDF(pdfReproduction);
        cdfLitter       = new CumulativeDF(pdfLitter);
        cdfMaturity     = new CumulativeDF(pdfMaturity);

        parent = entityManager.parent;
        return *this;
    }
}
