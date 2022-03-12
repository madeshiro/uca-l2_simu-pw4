#ifndef CPP_CONTAINER_HPP
#define CPP_CONTAINER_HPP
#include "pointer.hpp"

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
    public:
        virtual bool add(value_t elem) = 0;
        virtual bool addAll(const Collection<E>& c) = 0;

        virtual void clear() = 0;

        virtual bool contains(value_t elem) = 0;
        virtual bool containsAll(const Collection<E>& c) = 0;

        virtual bool isEmpty() const = 0;

        virtual bool remove(value_t elem) = 0;
        virtual bool removeAll(const Collection<E>& c) = 0;
        virtual bool removeIf(const Predicate<E>& filter) = 0;

        virtual bool retainAll(const Collection<E>& c) = 0;

        virtual size_t size() const = 0;

        virtual UniquePointer<E> toArray() const = 0;

        /* OPERATORS */

        virtual bool operator +=(value_t elem) {return add(elem);}
        virtual bool operator -=(const_t elem) {return remove(elem);}
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

        virtual ptr_t set(value_t elem, uint_t index) = 0;
        virtual ref_t get(uint_t index) = 0;
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

        ptr_t  _F_array;
        uint_t _F_size;
    public:
        ArrayList();
        ArrayList(const ArrayList<E>& obj);
        virtual ~ArrayList() override;

        virtual bool add(value_t elem) = 0;
        virtual bool addAll(const Collection<E>& c) = 0;

        virtual void clear() = 0;

        virtual bool contains(value_t elem) = 0;
        virtual bool containsAll(const Collection<E>& c) = 0;

        virtual bool isEmpty() const = 0;

        virtual bool remove(value_t elem) = 0;
        virtual bool removeAll(const Collection<E>& c) = 0;
        virtual bool removeIf(const Predicate<E>& filter) = 0;

        virtual bool retainAll(const Collection<E>& c) = 0;

        virtual size_t size() const = 0;

        virtual UniquePointer<E> toArray() const = 0;

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

        bool _F_needUpdate;
        UniquePointer<E[]> _F_toArray;

        Set(): _F_needUpdate(false), _F_toArray(nullptr) {}
        virtual void setNeedUpdate(bool status = true) final {_F_needUpdate=status;}
        virtual bool needUpdate() const final {return _F_needUpdate;}
    public:
        virtual Iterator<E> iterator() override;
    };

    template<typename E>
    /**
     * @warning E needs to have these 3 operators {<, >, ==} !
     */
    class SortedSet : public Set<E>
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
        SortedSet();
        virtual ~SortedSet() override;

        virtual bool add(value_t elem);
        virtual bool addAll(const Collection<E>& c);

        virtual void clear();

        virtual bool contains(value_t elem);
        virtual bool containsAll(const Collection<E>& c);

        virtual bool isEmpty() const;

        virtual bool remove(value_t elem);
        virtual bool removeAll(const Collection<E>& c);
        virtual bool removeIf(const Predicate<E>& filter);

        virtual bool retainAll(const Collection<E>& c);

        virtual size_t size() const;

        virtual UniquePointer<E> toArray() const;
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

    template < typename E >
    Iterator<E> Set<E>::iterator()
    {
        if (needUpdate())
        {
            _F_toArray = this->toArray();
        }

        return Iterable<E>(_F_toArray.pointer(), _F_toArray.pointer()+this->size());
    }
}

#endif //CPP_CONTAINER_HPP
