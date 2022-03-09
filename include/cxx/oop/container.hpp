#ifndef CPP_CONTAINER_HPP
#define CPP_CONTAINER_HPP
#include "type_traits.hpp"
#include "object.h"

/* HEADER : CLASS DEFINITION */

namespace UCA_L2INFO_PW4
{
    template < typename T, typename _Traits = Traits<T> >
    struct Iterator
    {
        typedef _Traits traits_type;
    protected:
        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

    public:
        ptr_t _F_begin, _F_end;

        Iterator(ptr_t begin, ptr_t end);
        virtual ~Iterator() = delete;
    };

    template < typename T, typename _Traits = Traits<T> >
    struct Iterable : public Object
    {
        typedef _Traits traits_type;
        typedef typename traits_type::ptr_t         ptr_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        virtual Iterator<T, traits_type> iterator() = 0;

        ptr_t begin();
        ptr_t end();

        ptr_t rbegin();
        ptr_t rend();

        const_ptr_t cbegin() const;
        const_ptr_t cend() const;

        const_ptr_t crbegin() const;
        const_ptr_t crend() const;
    };

    template<typename E>
    class Collection : public Iterable< E, Traits<E> >
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

    };

    template<typename E>
    class List /* interface */ : public Collection<E>
    {
    protected:
        typedef typename Collection<E>::traits_type traits_type;

        typedef typename Collection<E>::value_t   value_t;
        typedef typename Collection<E>::ref_t     ref_t;
        typedef typename Collection<E>::ptr_t     ptr_t;
        typedef typename Collection<E>::rvalue_t  rvalue_t;

        typedef typename Collection<E>::const_t       const_t;
        typedef typename Collection<E>::const_ref_t   const_ref_t;
        typedef typename Collection<E>::const_ptr_t   const_ptr_t;
    public:
        List() = default;
        virtual ~List() = 0;

        /* GETTER */
        virtual int size() const = 0;
        virtual ref_t get(uint_t index) = 0;

        /* SETTER */
        virtual ptr_t set(value_t elem, uint_t index) = 0;

        /* ACTIONS */
        virtual bool add(value_t elem) = 0;

        virtual bool remove(rvalue_t elem) = 0;
        virtual bool remove(const_ref_t elem) = 0;

        /* OPERATORS */
        virtual ref_t operator[](uint_t index)
        {
            return get(index);
        }

        virtual bool operator +=(value_t elem)
        {
            return add(elem);
        }

        virtual bool operator -=(const_t elem)
        {
            return remove(elem);
        }
    };

    template<typename E>
    class ArrayList : public List<E>
    {
    protected:
        typedef typename List<E>::traits_type traits_type;

        typedef typename List<E>::value_t   value_t;
        typedef typename List<E>::ref_t     ref_t;
        typedef typename List<E>::ptr_t     ptr_t;
        typedef typename List<E>::rvalue_t  rvalue_t;

        typedef typename List<E>::const_t       const_t;
        typedef typename List<E>::const_ref_t   const_ref_t;
        typedef typename List<E>::const_ptr_t   const_ptr_t;
    public:
        ArrayList();
        ArrayList(const ArrayList<E>& obj);
        virtual ~ArrayList() override;

        virtual bool add(value_t elem) = 0;
    };

    template < typename E >
    class Vector : public List<E>
    {

    };

    template<typename E>
    class Set : public Collection<E>
    {
    protected:
        typedef typename Collection<E>::traits_type traits_type;

        typedef typename Collection<E>::value_t   value_t;
        typedef typename Collection<E>::ref_t     ref_t;
        typedef typename Collection<E>::ptr_t     ptr_t;
        typedef typename Collection<E>::rvalue_t  rvalue_t;

        typedef typename Collection<E>::const_t       const_t;
        typedef typename Collection<E>::const_ref_t   const_ref_t;
        typedef typename Collection<E>::const_ptr_t   const_ptr_t;
    public:
        bool add(value_t elem) = 0;
    };

    template <typename E>
    class HashSet : public Set<E>
    {

    };

    template<typename K, typename V>
    class Map
    {
    public:
        const Set<K>& keySet() const = 0;
        const List<V>& values() const = 0;
    };

    template<typename K, typename V>
    class HashMap : public Map<K, V>
    {

    };
}

/* TEMPLATE CLASS IMPLEMENTATION */
namespace UCA_L2INFO_PW4
{

}

#endif //CPP_CONTAINER_HPP
