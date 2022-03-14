#ifndef CPP_OBJECT_H
#define CPP_OBJECT_H
#include "defines.h"

namespace UCA_L2INFO_PW4
{
    template <typename T>
    struct Traits;

    template <typename T, typename _Traits = Traits<T>>
    struct Alloc;

    template <typename _CharT, typename _Traits = Traits<_CharT>, typename _Alloc = Alloc<_CharT>>
    class __String__;
    using String    = __String__<char>;

    class Object
    {
    public:
        Object()            = default;
        virtual ~Object()   = default;

        virtual bool equals(const Object &&obj) const;
        virtual bool equals(const Object & obj) const;
        virtual bool equals(const Object * obj) const;

        virtual bool operator ==(const Object &&obj) const;
        virtual bool operator ==(const Object & obj) const;
        virtual bool operator ==(const Object * obj) const;

        virtual String toString() const;
        virtual hash_t hashCode() const;
        virtual Object* clone() const;
    };

    template < typename T >
    struct Comparable
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
        virtual int compareTo(const T& obj) const = 0;

        virtual bool operator <(const T& obj) const { return compareTo(obj) == -1; }
        virtual bool operator >(const T& obj) const { return compareTo(obj) == 1; }
        virtual bool operator ==(const T& obj) const { return compareTo(obj) == 0; }

        static int CompareTo(const T& obj1, const T& obj2);
    };

    template<typename T>
    int Comparable<T>::CompareTo(const T& obj1, const T& obj2)
    {
        if (obj1 == obj2) return 0;
        else return obj1 < obj2 ? -1 : 1;
    }

    template < typename T >
    struct Predicate
    {
        bool test(const T&) const = 0;
    };
}

#endif // CPP_OBJECT_H
