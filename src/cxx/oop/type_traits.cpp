#include "cxx/oop/type_traits.hpp"

namespace UCA_L2INFO_PW4
{
    hash_t Traits<char>::hash_code(const_t obj)
    {
        return (hash_t) obj;
    }

    Traits<char>::ptr_t Traits<char>::copy(const_ptr_t str)
    {
        size_t cpylen(len(str));
        ptr_t cpy = new value_t[cpylen+1];
        cpy[cpylen] = '\0';
        fill(str, cpy, cpylen);
        return cpy;
    }

    Traits<char>::ptr_t Traits<char>::copy(const_ptr_t str, size_t nmemb)
    {
        ptr_t cpy = new value_t[nmemb+1];
        cpy[nmemb] = '\0';
        fill(str, cpy, nmemb);
        return cpy;
    }

    Traits<char>::size_t Traits<char>::fill(const_ptr_t src, ptr_t dest, size_t size)
    {
        size_t i(0);
        for (; i < size; i++)
        {
            dest[i] = src[i];
        }
        return i;
    }

    Traits<char>::size_t Traits<char>::len(Traits<char>::const_ptr_t str)
    {
        size_t len = 0;
        while(str[len] != '\0') len++;
        return len;
    }

    hash_t Traits<wchar_t>::hash_code(const_t obj)
    {
        return (hash_t) obj;
    }

    Traits<wchar_t>::ptr_t Traits<wchar_t>::copy(const_ptr_t str)
    {
        size_t cpylen(len(str));
        ptr_t cpy = new value_t[cpylen+1];
        cpy[cpylen] = L'\0';
        fill(str, cpy, cpylen);
        return cpy;
    }

    Traits<wchar_t>::ptr_t Traits<wchar_t>::copy(const_ptr_t str, size_t nmemb)
    {
        ptr_t cpy = new value_t[nmemb+1];
        cpy[nmemb] = L'\0';
        fill(str, cpy, nmemb);
        return cpy;
    }

    Traits<wchar_t>::size_t Traits<wchar_t>::fill(const_ptr_t src, ptr_t dest, size_t size)
    {
        size_t i(0);
        for (; i < size; i++)
        {
            dest[i] = src[i];
        }
        return i;
    }

    Traits<wchar_t>::size_t Traits<wchar_t>::len(Traits<wchar_t>::const_ptr_t str)
    {
        size_t len = 0;
        while(str[len] != L'\0') len++;
        return len;
    }
}
