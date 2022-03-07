#include "cxx/oop/container.hpp"

namespace UCA_L2INFO_PW4
{
    template < typename T, typename _Traits >
    Iterator<T, _Traits>::Iterator(ptr_t begin, ptr_t end)
    {
        _F_begin = begin;
        _F_end   = end;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::ptr_t Iterable<T, _Traits>::begin()
    {
        return iterator()._F_begin;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::ptr_t Iterable<T, _Traits>::end()
    {
        return iterator()._F_end;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::const_ptr_t Iterable<T, _Traits>::cbegin() const
    {
        return iterator()._F_begin;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::const_ptr_t Iterable<T, _Traits>::cend() const
    {
        return iterator()._F_end;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::ptr_t Iterable<T, _Traits>::rbegin()
    {
        return iterator()._F_end-1;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::ptr_t Iterable<T, _Traits>::rend()
    {
        return iterator()._F_begin - 1;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::const_ptr_t Iterable<T, _Traits>::crbegin() const
    {
        return iterator()._F_end-1;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::const_ptr_t Iterable<T, _Traits>::crend() const
    {
        return iterator()._F_begin-1;
    }
}
