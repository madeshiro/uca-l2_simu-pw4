/*
 * UCA-L2 simulation "practical work #4" : a realistic simulation of rabbit population growth
 * Copyright (C) 2022 -- Rin Baudelet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
    events:
        // event(const Simulation*) on_replication;
        // event(const Simulation*) on_progress;
    public delegates:
        bool register_childbirth();
        bool register_birth(Rabbit* kitten);
    private:
        Experiment* parent;
        EntityManager manager;


    public:
        Simulation(Experiment* parent = nullptr);
        virtual ~Simulation();

        virtual BinaryStream exportBinary() const override;
        virtual Simulation&  loadBinary(BinaryStream stream) override;

        void init();
        void run();

        Simulation& operator =(Simulation& sim);

        Experiment* experiment();
    };
}

#endif //CPP_SIMULATION_H
