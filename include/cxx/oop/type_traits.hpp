#ifndef CPP_TYPE_TRAITS_HPP
#define CPP_TYPE_TRAITS_HPP
#include "defines.h"
#include "object.h"
#include <stdlib.h>

namespace UCA_L2INFO_PW4
{
    template <typename T>
    struct Traits
    {
        typedef T   value_t;
        typedef T&  ref_t;
        typedef T&& rvalue_t;
        typedef T*  ptr_t;

        typedef const T     const_t;
        typedef const T*    const_ptr_t;
        typedef const T&    const_ref_t;

        typedef ulong_t     size_t;

        static hash_t hash_code(const_ref_t obj);
        static ptr_t  copy(const_ptr_t ptr, size_t __size);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
    };
    
    template < typename T >
    struct Traits<T[]>
    {
        typedef T   value_t;
        typedef T&  ref_t;
        typedef T&& rvalue_t;
        typedef T*  ptr_t;

        typedef const T     const_t;
        typedef const T*    const_ptr_t;
        typedef const T&    const_ref_t;

        typedef ulong_t     size_t;

        static ptr_t  copy(const_ptr_t ptr, size_t __sizeof);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
    };

    template < typename T >
    struct Traits<T&>
    {
        typedef T&  value_t;
        typedef T&  ref_t;
        typedef T&& rvalue_t;
        typedef T*  ptr_t;

        typedef const T&    const_t;
        typedef const T*    const_ptr_t;
        typedef const T&    const_ref_t;

        typedef ulong_t     size_t;

        static hash_t hash_code(const_t obj);
        static ptr_t  copy(const_ptr_t ptr, size_t __sizeof);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
    };

    template < typename T >
    struct Traits<T*>
    {
        typedef T*   value_t;
        typedef T*&  ref_t;
        typedef T*&& rvalue_t;
        typedef T**  ptr_t;

        typedef const T*     const_t;
        typedef const T**    const_ptr_t;
        typedef const T*&    const_ref_t;

        typedef ulong_t     size_t;

        static hash_t hash_code(const_t obj);
        static ptr_t  copy(const_ptr_t ptr, size_t __sizeof);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
    };
    
    template <>
    struct Traits<char>
    {
        typedef char   value_t;
        typedef char&  ref_t;
        typedef char&& rvalue_t;
        typedef char*  ptr_t;

        typedef const char     const_t;
        typedef const char*    const_ptr_t;
        typedef const char&    const_ref_t;

        typedef ulong_t     size_t;

        static hash_t hash_code(const_t obj);
        static ptr_t  copy(const_ptr_t str);
        static ptr_t  copy(const_ptr_t str, size_t __sizeof);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
        static size_t len(const_ptr_t str);
    };
    

    template <>
    struct Traits<wchar_t>
    {
        typedef wchar_t   value_t;
        typedef wchar_t&  ref_t;
        typedef wchar_t&& rvalue_t;
        typedef wchar_t*  ptr_t;

        typedef const wchar_t     const_t;
        typedef const wchar_t*    const_ptr_t;
        typedef const wchar_t&    const_ref_t;

        typedef ulong_t     size_t;

        static hash_t hash_code(const_t obj);
        static ptr_t  copy(const_ptr_t str);
        static ptr_t  copy(const_ptr_t str, size_t __sizeof);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
        static size_t len(const_ptr_t str);
    };

    template < typename T >
    hash_t Traits<T>::hash_code(const_ref_t obj)
    {
        if (dynamic_cast<const Object*>(&obj))
        {
            return dynamic_cast<const Object*>(&obj)->hashCode();
        }
        else
        {
            return 0;
        }
    }

    template < typename T >
    typename Traits<T>::ptr_t Traits<T>::copy(const_ptr_t ptr, size_t __size)
    {
        ptr_t cpy = (ptr_t) malloc(sizeof(T)*__size);
        if (cpy)
        {

        }
    }

    template < typename T >
    hash_t Traits<T&>::hash_code(const_t obj)
    {
        return Traits<T>::hash_code(obj);
    }

    Traits<char>::size_t Traits<char>::len(Traits<char>::const_ptr_t str)
    {
        size_t len = 0;
        while(str[len] != '\0') len++;
        return len;
    }

    template < typename T >
    hash_t Traits<T*>::hash_code(const_t obj)
    {
        return (hash_t) obj;
    }
}

#endif //CPP_TYPE_TRAITS_HPP
