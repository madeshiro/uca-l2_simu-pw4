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
#ifndef CPP_THREAD_H
#define CPP_THREAD_H
#include "object.h"

namespace UCA_L2INFO_PW4
{
    class ThreadEntry : public Object
    {
        void* _F_args = nullptr;
    public:
        virtual int start();
        virtual int start(void* args) = 0;

        virtual int operator()();
        virtual int operator()(void* args);

        void setArguments(void* args);
        void* arguments() const;
    };

    class ThreadFunction : public ThreadEntry
    {
        typedef int (*thread_f)(void*);

        thread_f _F_function;
    public:
        ThreadFunction(thread_f f);
        ThreadFunction(const ThreadFunction& func);

        virtual int start(void* args) override;

        virtual hash_t hashCode() const override;
        virtual bool equals(const Object& tf) const override;
    };

    template < class C >
    class ThreadClassFunction : public ThreadEntry
    {
        typedef int (C::*thread_f)(void*);

        C*       _F_instance;
        thread_f _F_function;
    public:
        ThreadClassFunction(C* instance, thread_f f);
        ThreadClassFunction(const ThreadClassFunction<C>& tcf);

        virtual int start(void* args) override;

        virtual hash_t hashCode() const override;
        virtual bool equals(const Object& tcf) const override;
    };

    class Thread : public Object
    {
        friend int __thread_entrypoint(void*);
    protected:
        ThreadEntry* const _F_entry;

        bool _Mt_running;
    public:
        Thread(ThreadEntry* entry);
        virtual ~Thread() override;

        int run();
        void wait();
        int kill(int _exit);

        bool isRunning() const;
    };

    template < class C >
    ThreadClassFunction<C>::ThreadClassFunction(C *instance, thread_f f):
        _F_instance(instance), _F_function(f)
    { /* ... */ }

    template < class C >
    ThreadClassFunction<C>::ThreadClassFunction(const ThreadClassFunction<C> &tcf):
        _F_instance(tcf._F_instance), _F_function(tcf._F_function)
    { /* ... */ }

    template < class C >
    int ThreadClassFunction<C>::start(void *args)
    {
        return (_F_instance->*_F_function)(args);
    }

    template < class C >
    hash_t ThreadClassFunction<C>::hashCode() const
    {
        return ((hash_t) reinterpret_cast<void*>(_F_function)) << 32 | (hash_t) _F_instance;
    }

    template < class C >
    bool ThreadClassFunction<C>::equals(const Object &tcf) const
    {
        if (dynamic_cast<const ThreadClassFunction<C>*>(&tcf) == nullptr)
        {
            return false;
        }
        else
        {
            const ThreadClassFunction<C>* pTCF(dynamic_cast<const ThreadClassFunction<C>*>(&tcf));
            return pTCF->_F_function == _F_function && pTCF->_F_instance == _F_instance;
        }
    }
}

#endif //TP4_THREAD_H
