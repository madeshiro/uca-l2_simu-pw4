#include "cxx/simulation/experiment.h"
#include "mt19937ar.h"
#include "cxx/oop/file.h"

namespace UCA_L2INFO_PW4
{
    Experiment::Experiment(uint_t replication, uint_t month_duration, uint_t male, uint_t female):
        _F_replication(replication), _F_duration(month_duration),
        _F_initMale(male), _F_initFemale(female),
        mt_keys(nullptr), mt_key_length(0u),
        _F_directory(String::toHexString(uuid()))
    {
        _F_simulations = new Simulation[_F_replication];
    }

    Experiment::~Experiment()
    {
        if (mt_keys)
            delete mt_keys;

        if (_F_simulations)
            delete[] _F_simulations;
    }

    void Experiment::run()
    {
        init_by_array((unsigned long*) mt_keys, mt_key_length);

        for (uint_t i = 0; i < _F_replication; i++)
        {
            Simulation simulation(this);
            _F_simulations[i] = simulation;

            on_replication(i + 1, _F_replication, _F_simulations[i]);

            _F_simulations[i].init();
            _F_simulations[i].run();

            on_simulation_end(i+1, _F_replication, _F_simulations[i]);
        }

        on_experiment_end(this);
    }

    void Experiment::set_mt_key(ulong_t *mtKeys, ulong_t mtKeyLength)
    {
        this->mt_keys = Traits<ulong_t>::copy(mtKeys, mtKeyLength);
        this->mt_key_length = mtKeyLength;
    }

    void Experiment::join()
    {
        /* for 1.0 release w/ thread */
    }

    void Experiment::stop()
    {
        /* for 1.0 release w/ thread */
    }

    void Experiment::pause()
    {
        /* for 1.0 release w/ thread */
    }

    ullong_t Experiment::uuid() const
    {
        ullong_t uuid = (ullong_t) ~0x0;
        for (uint_t i(0); i < mt_key_length; i++)
        {
            uuid &= mt_keys[i];
            uuid <<= 11*i % 31;
        }

        uuid &= _F_replication;
        uuid <<= 4;

        uuid &= _F_duration;
        uuid <<= 8;

        uuid &= _F_initFemale << 16 | _F_initMale;

        return uuid;
    }

    uint_t Experiment::getReplicationAmount() const
    {
        return _F_replication;
    }

    uint_t Experiment::getMonthDuration() const
    {
        return _F_duration;
    }

    uint_t Experiment::getRequestMale() const
    {
        return _F_initMale;
    }

    uint_t Experiment::getRequestFemale() const
    {
        return _F_initFemale;
    }
}