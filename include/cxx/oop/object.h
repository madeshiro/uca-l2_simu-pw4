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
#ifndef CPP_OBJECT_H
#define CPP_OBJECT_H
#include "defines.h"
#include <utility>

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

        virtual bool equals(const Object & obj) const;
        virtual bool equals(const Object * obj) const;

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

    template < class F >
    class Function;

    template <class R, class... Args>
    class Function<R(Args...)>
    {
    protected:
        typedef R(*function_t)(Args...);
        function_t _F_function;
    public:
        Function(): _F_function(nullptr) {/*...*/}
        Function(std::nullptr_t): _F_function(nullptr) {/* ... */}
        Function(function_t function): _F_function(function) {/* ... */}
        Function(const Function<R(Args...)>& function): _F_function(function._F_function) {/*...*/}

        template < class F >
        Function(F&& f) {
            _F_function = std::forward<F>(f);
        }

        virtual ~Function() = default;

        void swap(Function<R(Args...)> & f)
        {
            function_t tmp = f._F_function;
            f._F_function = this->_F_function;
            this->_F_function = tmp;
        }

        R operator()(Args... args) const
        {
            return _F_function(args...);
        }

        operator bool() { return _F_function != nullptr; }

        Function<R(Args...)> & operator =(const Function<R(Args...)>& function)
        {
            _F_function=function._F_function;
            return *this;
        }

        template < class F >
        Function<R(Args...)> & operator =(F &&predicate)
        {
            Predicate(std::forward<F>(predicate)).swap(*this);
            return *this;
        }

        Function<R(Args...)> & operator =(function_t&& function)
        {
            _F_function=function;
            return *this;
        }
    };

    template <class... Args>
    using Predicate = Function<bool(Args...)>;

    template <class... Args>
    using SortMethod = Function<int(Args...)>;

#ifndef OOP_IMPL_TEMPLATE_STRING
    //extern template class __String__<char>;
    //extern template class __String__<wchar_t>;
#endif
}

#endif // CPP_OBJECT_H
