/**
 * @file event.hpp
 * @author Rin Baudelet
 *
 * @brief Let's reproduce a really interresting C# feature : event/delegate object !
 */
#ifndef CPP_EVENT_HPP
#define CPP_EVENT_HPP
#include "object.h"
#include "../../defines.h"
#include "pointer.hpp"
#include "container.hpp"

#define delegate
#define event

namespace UCA_L2INFO_PW4
{
    template < typename... Args > class Event;
    template < typename... Args >
    class Delegate : public Object
    {
        int _F_priority = 0x2;
        friend class Event<Args...>;

    protected:
        Delegate(int priority): _F_priority(priority) {/* ... */}
    public:
        virtual void operator ()(Args... args) final;
        virtual void call(Args... args) = 0;

        virtual uint_t argsLength() const final
        {
            return sizeof...(Args);
        }

        virtual int priority() const final
        {
            return _F_priority;
        }
    };

    template < typename ... Args >
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
        HashSet< SharedPointer< Delegate<Args...> > > _F_dlgts;
    public:

    };

    template < typename... Args >
    class GlobalDelegate : public Delegate<Args...>
    {
        typedef void (*function)(Args...);

        function _F_fn;
    public:
        GlobalDelegate(function fn, int priority = Event<Args...>::Priority::Normal);
        GlobalDelegate(const GlobalDelegate<Args...> &obj);
        virtual ~GlobalDelegate() override = delete;

        virtual void call(Args... args) override;
        virtual hash_t hashCode() override;
    };

    template < class Class, typename... Args >
    class ClassDelegate : public Delegate<Args...>
    {
        typedef void (Class::*Function)(Args...);

        Class* _F_obj;
        Function _F_fn;
    public:
        ClassDelegate(Class* obj, Function fn, int priority = Event<Args...>::Priority::Normal);
        ClassDelegate(const ClassDelegate<Class, Args...> & obj);
        virtual ~ClassDelegate() override = delete;

        Class& getClassInstance();
        Class* getParent();

        virtual void call(Args... args) override;
        virtual hash_t hashCode() override;
    };
}

#include "../../../src/cxx/oop/event.c++"
#endif //CPP_EVENT_HPP
