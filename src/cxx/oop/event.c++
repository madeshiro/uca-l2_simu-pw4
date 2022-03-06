#include "../../../include/cxx/oop/event.hpp"

namespace UCA_L2INFO_PW4
{
    template < typename ...Args >
    void Delegate<Args...>::operator ()(Args... args)
    {
        call(args...);
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
    void GlobalDelegate<Args...>::call(Args ...args)
    {
        _F_fn(args...);
    }

    template < typename ...Args >
    hash_t GlobalDelegate<Args...>::hashCode()
    {
        return (hash_t) _F_fn;
    }

    template < class Class, typename ...Args >
    ClassDelegate<Class, Args...>::ClassDelegate(Class *obj, Function fn, int priority):
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
    void ClassDelegate<Class, Args...>::call(Args ...args)
    {
        ((*_F_obj).*_F_fn)(args...);
    }

    template < class Class, typename ...Args >
    hash_t ClassDelegate<Class, Args...>::hashCode()
    {
        return (((hash_t) _F_fn) << 32) | (hash_t) _F_obj;
    }
}