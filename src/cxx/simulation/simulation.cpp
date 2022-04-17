#include "cxx/simulation/simulation.h"
#include "cxx/simulation/experiment.h"
#include "cxx/application.h"

namespace UCA_L2INFO_PW4
{
    Simulation::Simulation(Experiment *parent):
        parent(parent), manager(this)
    {

    }

    Simulation::~Simulation()
    {
    }

    BinaryStream Simulation::exportBinary() const
    {
        return BinaryStream(); // Todo Simulation::exportBinary
    }

    Simulation& Simulation::loadBinary(BinaryStream stream [[gnu::unused]])
    {
        // Todo Simulation::loadBinary
        return *this;
    }

    void Simulation::init()
    {
        for (uint_t i(0); i < parent->getRequestFemale(); i++)
        {
            manager.createAdult(true);
        }

        for (uint_t i(0); i < parent->getRequestMale(); i++)
        {
            manager.createAdult(false);
        }
    }

    void Simulation::run()
    {
        UniquePointer<Rabbit*[]> males, females;

        for (uint_t month(0); month < parent->getMonthDuration(); month++)
        {
            males = manager.maleRabbits->toArray();
            females = manager.femaleRabbits->toArray();
            uint_t malesSize = manager.maleRabbits->size();
            uint_t femalesSize = manager.femaleRabbits->size();

            if (malesSize == 0 && femalesSize == 0)
            {
                Application::app->out->info().format("month({0}): decimated population !\n", (int)month);
                return;
            }

            for (uint_t i(0); i < malesSize; i++)
            {
                Rabbit* rabbit(males[i]);
                if (manager.doSurvive(rabbit))
                {
                    rabbit->increaseLifetime();
                }
            }

            for (uint_t i(0); i < femalesSize; i++)
            {
                Rabbit* rabbit(females[i]);
                if (manager.doSurvive(rabbit))
                {
                    manager.doReproduction(rabbit);
                    rabbit->increaseLifetime();
                }
            }
        }

        // Todo Build statistic and free memory
    }

    Simulation& Simulation::operator=(Simulation &sim)
    {
        parent = sim.parent;
        manager = sim.manager;
        return *this;
    }

    Experiment *Simulation::experiment()
    {
        return parent;
    }

    bool Simulation::register_childbirth()
    {
        return true;
    }

    bool Simulation::register_birth(Rabbit *kitten)
    {
        return true;
    }
}