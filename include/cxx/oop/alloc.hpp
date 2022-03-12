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

    template <typename T, typename _Traits>
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
