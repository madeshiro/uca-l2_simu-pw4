#include "cxx/oop/event.hpp"
namespace UCA_L2INFO_PW4
{
    template < typename ...Args >
    bool Delegate<Args...>::operator ()(Args... args)
    {
        return call(args...);
    }

    template < typename ...Args >
    Event<Args...>::Event(): _F_dlgts(new Delegate<Args...>[5])
    {
        /* ... */
    }

    template < typename ...Args >
    Event<Args...>::Event(const Event<Args...>& obj): _F_dlgts(obj._F_dlgts)
    {
        /* ... */
    }

    template < typename ...Args >
    Event<Args...>::~Event<Args...>()
    {
        delete[] _F_dlgts;
    }

    template < typename ...Args >
    void Event<Args...>::connect(Delegate<Args...> *&&dlgt)
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
        for (Priority p = Critical; p >= Lowest; --p)
        {
            for (Delegate<Args...> &dlgt : _F_dlgts[p])
            {
                if (!dlgt.call(args...))
                {
                    return;
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
    hash_t GlobalDelegate<Args...>::hashCode()
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
    hash_t ClassDelegate<Class, Args...>::hashCode()
    {
        return (((hash_t) _F_fn) << 32) | (hash_t) _F_obj;
    }
}