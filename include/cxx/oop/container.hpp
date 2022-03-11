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

        virtual Iterator<T, traits_type> iterator() const = 0;

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
    public:
        bool add(value_t elem) = 0;
        bool remove(value_t elem) = 0;

        ptr_t set(uint_t index, value_t elem) = 0;
        ref_t get(uint_t index) = 0;
        bool isEmpty() const = 0;
        size_t size() const = 0;

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

        /* SETTER */
        virtual ptr_t set(value_t elem, uint_t index) = 0;

        /* ACTIONS */

        /* OPERATORS */

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

    template<typename E>
    class SortedSet : public Set<E>
    {

    };

    template <typename E>
    class HashSet : public Set<E>
    {

    };

    template<typename E>
    class ChainedList : public Collection<E>
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
        ChainedList();
        ChainedList(const Collection<E>& collection);
        virtual ~ChainedList() override;

    };

    template<typename E>
    class Queue : public ChainedList<E>
    {
    protected:
        typedef typename ChainedList<E>::traits_type traits_type;

        typedef typename ChainedList<E>::value_t   value_t;
        typedef typename ChainedList<E>::ref_t     ref_t;
        typedef typename ChainedList<E>::ptr_t     ptr_t;
        typedef typename ChainedList<E>::rvalue_t  rvalue_t;

        typedef typename ChainedList<E>::const_t       const_t;
        typedef typename ChainedList<E>::const_ref_t   const_ref_t;
        typedef typename ChainedList<E>::const_ptr_t   const_ptr_t;

        uint_t _F_limit;
    public:
        Queue(uint_t limit = 0);
        Queue(const Collection<E>& collection);

        value_t next();
        uint_t getLimit() const;

        /**
         * Defines a new limit size for this Queue list. If the limit is lower than
         * the current queue's size, all values beyonds the limit will be removed.
         * @note newLimit = 0 equivalent to infinite
         * @param newLimit the new queue size's limit.
         * @return
         */
        void   setLimit(uint_t newLimit);
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

#endif //CPP_CONTAINER_HPP
