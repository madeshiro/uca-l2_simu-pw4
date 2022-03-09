#ifndef CPP_SIMULATION_H
#define CPP_SIMULATION_H

#include "cxx/oop/event.hpp"

namespace UCA_L2INFO_PW4
{
    class Simulation final
    {
    public:
        event(const Simulation&) on_start;
        event()                  on_quit;
        event(bool)              on_pause;
        event(const Simulation&) on_replication;
    private:

    protected:
        bool caching(List<>)
    public:
        virtual ~Simulation();

        void start();

        void pause();
        void requestQuit(bool wait = false);
    };
}

#endif //CPP_SIMULATION_H
