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

        Simulation** _F_simulations;
        File _F_directory;

    public:
        ProbabilityDF pdfReproduction;
        ProbabilityDF pdfLitter;
        ProbabilityDF pdfMaturity;

        CumulativeDF* cdfReproduction;
        CumulativeDF* cdfLitter;
        CumulativeDF* cdfMaturity;
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
