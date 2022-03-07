#ifndef CPP_OBJECT_H
#define CPP_OBJECT_H
#include "defines.h"
#include "alloc.hpp"

namespace UCA_L2INFO_PW4
{
    template <typename _CharT, typename _Traits = Traits<_CharT>, typename _Alloc = Alloc<_CharT>>
    class __String__;

    using String    = __String__<char>;
    using WString   = __String__<wchar_t>;

    class Object
    {
    public:
        Object()            = default;
        virtual ~Object()   = default;

        virtual bool equals(Object &&obj);
        virtual bool equals(Object & obj);
        virtual bool equals(Object * obj);

        virtual bool operator ==(Object &&obj);
        virtual bool operator ==(Object & obj);
        virtual bool operator ==(Object * obj);

        virtual String toString();
        virtual hash_t hashCode();
        virtual Object* clone();
    };

    template < typename T >
    class Comparable
    {
        /**
         * Compares the class instance with another value.
         * <ul>
         *  <li>Returns -1 if *this < obj</li>
         *  <li>Returns 0 if equals</li>
         *  <li>Return 1 if *this > obj</li>
         * </ul>
         * This function may be useful for sorted list. Otherwise, if this function
         * isn't implemented, SortedList will use Object#hashCode() if available.
         * @param obj The object to compare this instance with.
         * @return -1, 0 or 1 depends of the comparaison results
         */
        virtual int compareTo(const T& obj) = 0;
    };
}

#endif // CPP_OBJECT_H

#ifndef CPP_STRING_HPP
#include "string.hpp"
#endif  // CPP_STRING_HPP
