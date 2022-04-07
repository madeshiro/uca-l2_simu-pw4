#include "cxx/simulation/simulation.h"
#include "cxx/simulation/experiment.h"

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
        for (uint_t month(0); month < parent->getMonthDuration(); month++)
        {
            for (Rabbit *rabbit: *manager.maleRabbits)
            {
                if (manager.doSurvive(rabbit))
                {
                    rabbit->increaseLifetime();
                }
            }

            for (Rabbit *rabbit: *manager.femaleRabbits)
            {
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
}