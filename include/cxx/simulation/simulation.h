#ifndef CPP_SIMULATION_H
#define CPP_SIMULATION_H
#include "cxx/oop/object"
#include "cxx/oop/binary.h"
#include "entities.h"

namespace UCA_L2INFO_PW4
{
    class Experiment;
    class Simulation final : public Binaries
    {
    public:
        // event(const Simulation*) on_replication;
        // event(const Simulation*) on_progress;
    private:
        Experiment* parent;
    public:
        Simulation(Experiment* parent = nullptr);
        virtual ~Simulation();

        virtual BinaryStream exportBinary() const override;
        virtual Simulation&  loadBinary(BinaryStream stream) override;

        void run();
    };
}

#endif //CPP_SIMULATION_H
