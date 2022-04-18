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
#ifndef CPP_ALLOC_HPP
#define CPP_ALLOC_HPP
#include "type_traits.hpp"

namespace UCA_L2INFO_PW4
{
    template < typename T, typename _Traits  >
    struct Alloc
    {
        typedef _Traits traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static ptr_t alloc();
        static ptr_t alloc(size_t nmemb);
        static ptr_t calloc(size_t nmemb);

        static size_t sizeOf();
    };

    template < typename T, typename _Traits  >
    struct Alloc<T[], _Traits>
    {
        typedef _Traits traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static ptr_t alloc();
        static ptr_t alloc(size_t nmemb);
        static ptr_t calloc(size_t nmemb);

        static size_t sizeOf();
    };

    template < typename T, typename _Traits = Traits<T> >
    struct Delete
    {
        typedef _Traits traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static void free(ptr_t ptr);
    };

    template <typename T, typename _Traits >
    struct Delete<T[], _Traits>
    {
        typedef _Traits traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static void free(ptr_t ptr);
    };

    template<typename T, typename _Traits>
    typename Alloc<T, _Traits>::ptr_t Alloc<T, _Traits>::alloc()
    {
        return (ptr_t) ::malloc(sizeof(T));
    }

    template<typename T, typename _Traits>
    typename Alloc<T, _Traits>::ptr_t Alloc<T, _Traits>::alloc(size_t nmemb)
    {
        return new T[nmemb];
    }

    template<typename T, typename _Traits>
    typename Alloc<T, _Traits>::ptr_t Alloc<T, _Traits>::calloc(size_t nmemb)
    {
        return (ptr_t) ::calloc(nmemb, sizeof(value_t));
    }

    template<typename T, typename _Traits>
    typename Alloc<T, _Traits>::size_t Alloc<T, _Traits>::sizeOf()
    {
        return sizeof(value_t);
    }

    template<typename T, typename _Traits>
    typename Alloc<T[], _Traits>::ptr_t Alloc<T[], _Traits>::alloc()
    {
        return new T[1u];
    }

    template<typename T, typename _Traits>
    typename Alloc<T[], _Traits>::ptr_t Alloc<T[], _Traits>::alloc(size_t nmemb)
    {
        return new T[nmemb];
    }

    template<typename T, typename _Traits>
    typename Alloc<T[], _Traits>::ptr_t Alloc<T[], _Traits>::calloc(size_t nmemb)
    {
        return (ptr_t) ::calloc(nmemb, sizeof(value_t));
    }

    template<typename T, typename _Traits>
    typename Alloc<T[], _Traits>::size_t Alloc<T[], _Traits>::sizeOf()
    {
        return sizeof(value_t);
    }

    template<typename T, typename _Traits>
    void Delete<T, _Traits>::free(ptr_t ptr)
    {
        delete ptr;
    }

    template<typename T, typename _Traits>
    void Delete<T[], _Traits>::free(ptr_t ptr)
    {
        delete[] ptr;
    }
}

#endif //CPP_ALLOC_HPP
