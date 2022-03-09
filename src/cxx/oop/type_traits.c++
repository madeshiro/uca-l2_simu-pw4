#include <malloc.h>
#include "cxx/oop/type_traits.hpp"
#include "cxx/oop/object.h"

namespace UCA_L2INFO_PW4
{
    template < typename T >
    hash_t Traits<T>::hash_code(const_t obj)
    {
        if (dynamic_cast<Object*>(&obj))
        {
            return ((Object*)&obj)->hashCode();
        }
        else
        {
            return static_cast<hash_t>(obj);
        }
    }

    template < typename T >
    typename Traits<T>::ptr_t Traits<T>::copy(const_ptr_t ptr, size_t __size)
    {
        ptr_t cpy = malloc(sizeof(T)*__size);
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
}