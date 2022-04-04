#ifndef CPP_EXPERIMENT_H
#define CPP_EXPERIMENT_H
#include "simulation.h"
#include "cxx/oop/file.h"

namespace UCA_L2INFO_PW4
{
    class Experiment // : public Thread
    {
        friend class Simulation;

        uint_t _F_replication, _F_duration, _F_initMale, _F_initFemale;
        ulong_t * mt_keys, mt_key_length;

        Simulation* _F_simulations;
        File _F_directory;
    events:
        event(int, int, Simulation&) on_replication;
        event(int, int, Simulation&) on_simulation_end;
        event(Experiment*) on_experiment_end;
    public:
        Experiment(uint_t replication, uint_t month_duration, uint_t male, uint_t female);
        virtual ~Experiment();

        void set_mt_key(ulong_t mtKeys[], ulong_t mtKeyLength);

        void run();
        void join();
        void stop();
        void pause();

        uint_t getReplicationAmount() const;
        uint_t getMonthDuration() const;

        uint_t getRequestMale() const;
        uint_t getRequestFemale() const;
        virtual ullong_t uuid() const;
    };
}

#endif //CPP_EXPERIMENT_H
