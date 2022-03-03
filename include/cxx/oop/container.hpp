#ifndef CPP_CONTAINER_HPP
#define CPP_CONTAINER_HPP
#include "type_traits.hpp"
#include "object.h"

/* HEADER : CLASS DEFINITION */

namespace UCA_L2INFO_PW4
{
    template <typename T, typename traits_type>
    struct Iterator
    {
    protected:
        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;
    public:

    };

    template <typename T, typename traits_type>
    class Iterable : public Object
    {
    protected:
        Iterator<T, traits_type> iterator;
    public:
        Iterable(Iterator<T, traits_type> it): iterator(it)
        {/* ... */}

        virtual ~Iterable() = 0;


    };

    template<typename E>
    class List /* interface */ : public Iterable<E, Traits<E>>
    {
    protected:
        typedef Traits<E> traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;
    public:
        List() = default;
        virtual ~List() = 0;

        /* GETTER */
        virtual int size() const = 0;

        /* SETTER */

        virtual ptr_t set(value_t elem, uint_t index) throw();

        /* ACTIONS */
        virtual bool add(value_t elem) = 0;
        virtual bool remove(const_t elem) = 0;

    };

    template<typename E>
    class ArrayList : public List<E>
    {

    };

    template<typename E>
    class HashList : public List<E>
    {

    };

    template<typename E>
    class Set : public List<E>
    {

    };

    template <typename E>
    class HashSet : public Set<E>
    {

    };

    template<typename K, typename V>
    class HashMap
    {

    };
}

/* TEMPLATE CLASS IMPLEMENTATION */
namespace UCA_L2INFO_PW4
{

}

#endif //CPP_CONTAINER_HPP
