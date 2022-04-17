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
#ifndef CPP_EVENT_HPP
#define CPP_EVENT_HPP
#include "object.h"
#include "defines.h"
#include "pointer.hpp"
#include "container.hpp"

/**
 * @file event.hpp
 * @author Rin Baudelet
 *
 * @brief Let's reproduce a really interresting C# feature : event/delegate object !
 */

#define event(args...) Event<args>
#define events public
#define delegates

namespace UCA_L2INFO_PW4
{
    template < typename... Args > class Event;
    template < typename... Args >
    class Delegate : public Object
    {
        const int _F_priority = 0x2;
        friend class Event<Args...>;

    protected:
        Delegate(int priority): _F_priority(priority) {/* ... */}
    public:
        virtual bool operator ()(Args... args) final;
        virtual bool call(Args... args) = 0;

        virtual uint_t argsLength() const final
        {
            return sizeof...(Args);
        }

        virtual int priority() const final
        {
            return _F_priority;
        }
    };

    template < typename ...Args >
    class Event : public Object
    {
    public:
        enum Priority : int
        {
            Lowest   = 0x0,
            Low      = 0x1,
            Normal   = 0x2,
            High     = 0x3,
            Highest  = 0x4,
            Critical = 0x5
        };
    private:
        SharedPointer< HashSet<Delegate<Args...>*>[] > _F_dlgts;
    public:
        Event();
        Event(const Event&);
        virtual ~Event() override = default;

        void connect(Delegate<Args...>* dlgt);
        void disconnect(const Delegate<Args...>& dlgt);

        virtual void emit(Args... args);
        virtual void operator ()(Args... args) final;

        virtual uint_t connectedCount() const final;
        virtual uint_t argsLength() const final
        {
            return sizeof...(Args);
        }

        virtual Event<Args...>& operator =(const Event<Args...>& cpy);
    };

    template < typename... Args >
    class GlobalDelegate : public Delegate<Args...>
    {
        typedef bool (*function)(Args...);

        function _F_fn;
    public:
        GlobalDelegate(function fn, int priority = Event<Args...>::Priority::Normal);
        GlobalDelegate(const GlobalDelegate<Args...> &obj);
        virtual ~GlobalDelegate() override {
            /* empty */
        };

        virtual bool call(Args... args) override;
        virtual hash_t hashCode() const override;
    };

    template < class Class, typename... Args >
    class ClassDelegate : public Delegate<Args...>
    {
        typedef bool (Class::*Function)(Args...);

        Class& _F_obj;
        Function _F_fn;
    public:
        ClassDelegate(Class& obj, Function fn, int priority = Event<Args...>::Priority::Normal);
        ClassDelegate(const ClassDelegate<Class, Args...> & obj);
        virtual ~ClassDelegate() override {
            /* empty */
        }

        Class& getClassInstance();
        Class* getParent();

        virtual bool call(Args... args) override;
        virtual hash_t hashCode() const override;
    };

    template < typename ...Args >
    bool Delegate<Args...>::operator ()(Args... args)
    {
        return call(args...);
    }

    template < typename ...Args >
    Event<Args...>::Event(): _F_dlgts(new HashSet<Delegate<Args...>*>[6])
    {
        /* ... */
    }

    template < typename ...Args >
    Event<Args...>::Event(const Event<Args...>& obj): _F_dlgts(obj._F_dlgts)
    {
        /* ... */
    }

    template < typename ...Args >
    void Event<Args...>::connect(Delegate<Args...> *dlgt)
    {
        _F_dlgts[dlgt->priority()].add(dlgt);
    }

    template < typename ...Args >
    void Event<Args...>::disconnect(const Delegate<Args...> &dlgt)
    {
        _F_dlgts[dlgt.priority()].remove(dlgt);
    }

    template < typename ...Args >
    void Event<Args...>::emit(Args ...args)
    {
        for (int p = Critical; p >= Lowest; p--)
        {
            if (_F_dlgts[p].size())
            {
                for (Delegate<Args...> *dlgt: _F_dlgts[p])
                {
                    if (!dlgt->call(args...))
                    {
                        return;
                    }
                }
            }
        }
    }

    template < typename ...Args >
    void Event<Args...>::operator()(Args... args)
    {
        emit(args...);
    }

    template < typename ...Args >
    uint_t Event<Args...>::connectedCount() const
    {
        uint_t connected = 0;
        for (uint_t i = 0; i <= Priority::Critical; i++)
        {
            connected += _F_dlgts[i].size();
        }
        return connected;
    }

    template < typename ...Args >
    Event<Args...> & Event<Args...>::operator=(const Event<Args...> &cpy)
    {
        _F_dlgts = cpy._F_dlgts;
        return *this;
    }

    template < typename ...Args >
    GlobalDelegate<Args...>::GlobalDelegate(function fn, int priority):
            Delegate<Args...>(priority),
            _F_fn(fn)
    { /* ... */ }

    template < typename ...Args >
    GlobalDelegate<Args...>::GlobalDelegate(const GlobalDelegate<Args...> &obj):
            Delegate<Args...>(obj.priority()),
            _F_fn(obj._F_fn)
    { /* ... */ }

    template < typename ...Args >
    bool GlobalDelegate<Args...>::call(Args ...args)
    {
        return _F_fn(args...);
    }

    template < typename ...Args >
    hash_t GlobalDelegate<Args...>::hashCode() const
    {
        return (hash_t) _F_fn;
    }

    template < class Class, typename ...Args >
    ClassDelegate<Class, Args...>::ClassDelegate(Class &obj, Function fn, int priority):
            Delegate<Args...>(priority), _F_obj(obj), _F_fn(fn)
    { /* ... */ }

    template < class Class, typename ...Args >
    ClassDelegate<Class, Args...>::ClassDelegate(const ClassDelegate<Class, Args...> &obj):
            Delegate<Args...>(obj.priority()),
            _F_obj(obj._F_obj),
            _F_fn(obj._F_fn)
    { /* ... */ }

    template < class Class, typename ...Args >
    Class& ClassDelegate<Class, Args...>::getClassInstance()
    {
        return *_F_obj;
    }

    template < class Class, typename ...Args >
    Class* ClassDelegate<Class, Args...>::getParent()
    {
        return _F_obj;
    }

    template < class Class, typename ...Args >
    bool ClassDelegate<Class, Args...>::call(Args ...args)
    {
        return (_F_obj.*_F_fn)(args...);
    }

    template < class Class, typename ...Args >
    hash_t ClassDelegate<Class, Args...>::hashCode() const
    {
        return ((hash_t) reinterpret_cast<void*>(_F_fn) << 32) | (hash_t) &_F_obj;
    }
}

#endif //CPP_EVENT_HPP
