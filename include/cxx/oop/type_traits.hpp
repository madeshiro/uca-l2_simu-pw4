#ifndef CPP_TYPE_TRAITS_HPP
#define CPP_TYPE_TRAITS_HPP
#include "defines.h"
#include "object.h"
#include "utils.h"
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
        static ptr_t  copy(const_ptr_t ptr);
        static ptr_t  copy(const_ptr_t ptr, size_t nmemb);
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

        static ptr_t  copy(const_ptr_t ptr, size_t nmemb);
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
        static ptr_t  copy(const_ptr_t ptr);
        static ptr_t  copy(const_ptr_t ptr, size_t nmemb);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
    };

    template < typename T >
    struct Traits<T*>
    {
        typedef T*   value_t;
        typedef T*&  ref_t;
        typedef T*&& rvalue_t;
        typedef T**  ptr_t;

        typedef T*  const    const_t;
        typedef T** const    const_ptr_t;
        typedef T*  const &  const_ref_t;

        typedef ulong_t     size_t;

        static hash_t hash_code(const_t obj);
        static ptr_t  copy(const_ptr_t ptr);
        static ptr_t  copy(const_ptr_t ptr, size_t nmemb);
        static size_t fill(const ptr_t src, ptr_t dest, size_t size);
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
        static ptr_t  copy(const_ptr_t str, size_t nmemb);
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
    typename Traits<T>::ptr_t Traits<T>::copy(const_ptr_t ptr)
    {
        return (ptr_t) memcopy((void*)ptr, 1u, sizeof(T));
    }
    
    template < typename T >
    typename Traits<T>::ptr_t Traits<T>::copy(const_ptr_t ptr, size_t nmemb)
    {
        return (ptr_t) memcopy((void*)ptr, nmemb, sizeof(T));
    }
    
    template < typename T >
    typename Traits<T>::size_t Traits<T>::fill(const_ptr_t src, ptr_t dest, size_t size)
    {
        size_t i(0);
        for (; i < size; i++)
        {
            dest[i] = src[i];
        }
        return i;
    }

    template < typename T >
    typename Traits<T[]>::ptr_t Traits<T[]>::copy(const_ptr_t ptr, size_t nmemb)
    {
        return (ptr_t) memcopy((void*)ptr, nmemb, sizeof(T));
    }
    
    template < typename T >
    hash_t Traits<T&>::hash_code(const_t obj)
    {
        return Traits<T>::hash_code(obj);
    }

    template < typename T >
    typename Traits<T&>::size_t Traits<T&>::fill(const_ptr_t src, ptr_t dest, size_t size)
    {
        size_t i(0);
        for (; i < size; i++)
        {
            dest[i] = src[i];
        }
        return i;
    }

    template < typename T >
    typename Traits<T&>::ptr_t Traits<T&>::copy(const_ptr_t ptr)
    {
        return (ptr_t) memcopy((void*)ptr, 1u, sizeof(T));
    }
    
    template < typename T >
    typename Traits<T&>::ptr_t Traits<T&>::copy(const_ptr_t ptr, size_t nmemb)
    {
        return (ptr_t) memcopy((void*)ptr, nmemb, sizeof(T));
    }
    
    template < typename T >
    hash_t Traits<T*>::hash_code(const_t obj)
    {
        return (hash_t) reinterpret_cast<const void*>(obj);
    }
    
    template < typename T >
    typename Traits<T*>::ptr_t Traits<T*>::copy(const_ptr_t ptr)
    {
        return (ptr_t) memcopy((void*)ptr, 1u, sizeof(T*));
    }
    
    template < typename T >
    typename Traits<T*>::ptr_t Traits<T*>::copy(const_ptr_t ptr, size_t nmemb)
    {
        ptr_t cpy = new value_t[nmemb];
        for (uint_t i(0); i < nmemb; i++)
        {
            cpy[i] = ptr[i];
        }

        return cpy;
    }
    
    template < typename T >
    typename Traits<T*>::size_t Traits<T*>::fill(const ptr_t src, ptr_t dest, size_t size)
    {
        size_t i(0);
        for (; i < size; i++)
        {
            dest[i] = (value_t) src[i];
        }
        return i;
    }
}

#endif //CPP_TYPE_TRAITS_HPP
