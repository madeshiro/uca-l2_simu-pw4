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

        virtual UniquePointer<E[]> toArray() const = 0;

        /* OPERATORS */

        virtual bool operator +=(value_t elem) { return add(elem); }
        virtual bool operator -=(const_t elem) { return remove(elem); }
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

        virtual ref_t operator[](uint_t index) { return get(index); }
    };

    template<typename E>
    class AbstractList : public List<E>
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

        AbstractList();
        AbstractList(ptr_t array, uint_t size = 0);
    public:
        AbstractList(const AbstractList<E>& obj);
        virtual ~AbstractList() override;

        virtual void clear() override;

        virtual bool contains(value_t elem) override;
        virtual bool containsAll(const Collection<E>& c) override;

        virtual ref_t get(uint_t index) override;

        virtual bool isEmpty() const override;

        virtual bool retainAll(const Collection<E>& c) override;

        virtual ptr_t set(value_t elem, uint_t index) override;

        virtual size_t size() const override;

        virtual UniquePointer<E[]> toArray() const override;
    };

    template<typename E>
    class ArrayList : public List<E>
    {
    protected:
        typedef typename AbstractList<E>::traits_type traits_type;

        typedef typename AbstractList<E>::value_t   value_t;
        typedef typename AbstractList<E>::ref_t     ref_t;
        typedef typename AbstractList<E>::ptr_t     ptr_t;
        typedef typename AbstractList<E>::rvalue_t  rvalue_t;

        typedef typename AbstractList<E>::const_t       const_t;
        typedef typename AbstractList<E>::const_ref_t   const_ref_t;
        typedef typename AbstractList<E>::const_ptr_t   const_ptr_t;
    public:
        ArrayList();
        ArrayList(const ArrayList<E>& obj);
        virtual ~ArrayList() override;

        virtual bool add(value_t elem) override;
        virtual bool addAll(const Collection<E>& c) override;

        virtual bool remove(value_t elem);
        virtual bool removeAll(const Collection<E>& c);
        virtual bool removeIf(const Predicate<E>& filter);
    };

    template < typename E >
    class Vector : public AbstractList<E>
    {
    protected:
        typedef typename AbstractList<E>::traits_type traits_type;

        typedef typename AbstractList<E>::value_t   value_t;
        typedef typename AbstractList<E>::ref_t     ref_t;
        typedef typename AbstractList<E>::ptr_t     ptr_t;
        typedef typename AbstractList<E>::rvalue_t  rvalue_t;

        typedef typename AbstractList<E>::const_t       const_t;
        typedef typename AbstractList<E>::const_ref_t   const_ref_t;
        typedef typename AbstractList<E>::const_ptr_t   const_ptr_t;

        uint_t _F_capacity;
        uint_t _F_capacityIncrement;

        bool growVector();
    public:
        Vector(uint_t capacityIncrement = 32);
        Vector(const Vector<E>& obj);
        virtual ~Vector() override;

        virtual bool add(value_t elem) override;
        virtual bool addAll(const Collection<E>& c) override;

        virtual uint_t capacity() const final;

        virtual void clear() override;
        virtual void clearUnused();

        virtual bool remove(value_t elem) override;
        virtual bool removeAll(const Collection<E>& c) override;
        virtual bool removeIf(const Predicate<E>& filter) override;

        virtual void setCapacityIncrement(uint_t increment) final;
        virtual uint_t getCapacityIncrement() const final;
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
        virtual void needUpdate(bool status = true) final {_F_needUpdate=status;}
        virtual bool doNeedUpdate() const final {return _F_needUpdate;}
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

        struct Node
        {
            Node* parent, *left, *right;
            E element;
        };
    public:
        enum SortMethod : int
        {
            ASC = 0x1,
            DESC = 0x2
        };
    private:
        Node *_F_tree;
        SortMethod _F_sortMethod = ASC;
    public:
        SortedSet(SortMethod sort = ASC);
        SortedSet(const SortedSet<E> &cpy);
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

        virtual UniquePointer<E[]> toArray() const;
    };

    template <typename E>
    class HashSet : public Set<E>
    {
        template<typename K, typename V>
        friend class HashMap;
    protected:
        typedef Traits<E> traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        struct Node
        {
            Node* parent, *left, *right;
            E element;
        } *_F_set;

        uint_t _F_size;

        /**
         * Replaces or adds an element to the set. Because hashCode implementation may differ from time to time,
         * in order to especially optimize HashMap, we have created this function that add or replace the current
         * element in the HashSet.
         * @param elem The element to put in the set, replacing or adding it to the list.
         */
        virtual bool setElement(E elem, bool replace = true);
    public:
        HashSet();
        HashSet(const HashSet<E>& set);
        virtual ~HashSet() override;

        virtual bool add(value_t elem) override {return setElement(elem, false);}
        virtual bool addAll(const Collection<E>& c) override;

        virtual void clear() override;

        virtual bool contains(value_t elem) override;
        virtual bool containsAll(const Collection<E>& c) override;

        virtual bool isEmpty() const override;

        virtual bool remove(value_t elem) override;
        virtual bool removeAll(const Collection<E>& c) override;
        virtual bool removeIf(const Predicate<E>& filter) override;

        virtual bool retainAll(const Collection<E>& c) override;

        virtual size_t size() const override;

        virtual UniquePointer<E[]> toArray() const override;
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

        struct Chain
        {
            Chain* prev, *next;
            E elem;
        };

        Chain* _F_first;
        uint_t _F_size;
    public:
        ChainedList();
        ChainedList(const Collection<E>& collection);
        virtual ~ChainedList() override;

        virtual bool add(value_t elem) override;
        virtual bool addAll(const Collection<E>& c) override;

        virtual void clear() override;

        virtual bool contains(value_t elem) override;
        virtual bool containsAll(const Collection<E>& c) override;

        virtual bool isEmpty() const override;

        virtual bool remove(value_t elem) override;
        virtual bool removeAll(const Collection<E>& c) override;
        virtual bool removeIf(const Predicate<E>& filter) override;

        virtual bool retainAll(const Collection<E>& c) override;

        virtual size_t size() const override;

        virtual UniquePointer<E[]> toArray() const override;
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

        void push(value_t v);
        value_t pop();

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
    protected:
        typedef Traits<K> key_traits;
        typedef typename key_traits::value_t   key_t;
        typedef typename key_traits::ref_t     key_ref_t;
        typedef typename key_traits::ptr_t     key_ptr_t;
        typedef typename key_traits::rvalue_t  key_rvalue_t;

        typedef typename key_traits::const_t       key_const_t;
        typedef typename key_traits::const_ref_t   key_const_ref_t;
        typedef typename key_traits::const_ptr_t   key_const_ptr_t;

        typedef Traits<V> value_traits;
        typedef typename value_traits::value_t   value_t;
        typedef typename value_traits::ref_t     value_ref_t;
        typedef typename value_traits::ptr_t     value_ptr_t;
        typedef typename value_traits::rvalue_t  value_rvalue_t;

        typedef typename value_traits::const_t       value_const_t;
        typedef typename value_traits::const_ref_t   value_const_ref_t;
        typedef typename value_traits::const_ptr_t   value_const_ptr_t;

    public:
        virtual Set<K>  keySet() const = 0;
        virtual List<V> values() const = 0;
        
        virtual bool addAll(const Map<K,V>& map) = 0;

        virtual void clear() = 0;

        virtual bool contains(key_t elem) = 0;
        virtual bool containsAll(const Collection<K>& c) = 0;
        
        virtual bool isEmpty() const = 0;

        virtual bool remove(key_t elem) = 0;
        virtual bool removeAll(const Set<K>& c) = 0;
        
        virtual bool retainAll(const Set<K>& c) = 0;

        virtual bool set(key_t key, value_t value) = 0;
        virtual value_t* get(key_t key) = 0;
        
        virtual size_t size() const = 0;
    };

    template<typename K, typename V>
    class HashMap : public Map<K, V>
    {
    protected:
        typedef typename Map<K, V>::key_traits key_traits;
        typedef typename key_traits::value_t   key_t;
        typedef typename key_traits::ref_t     key_ref_t;
        typedef typename key_traits::ptr_t     key_ptr_t;
        typedef typename key_traits::rvalue_t  key_rvalue_t;

        typedef typename key_traits::const_t       key_const_t;
        typedef typename key_traits::const_ref_t   key_const_ref_t;
        typedef typename key_traits::const_ptr_t   key_const_ptr_t;

        typedef typename Map<K, V>::value_traits value_traits;
        typedef typename value_traits::value_t   value_t;
        typedef typename value_traits::ref_t     value_ref_t;
        typedef typename value_traits::ptr_t     value_ptr_t;
        typedef typename value_traits::rvalue_t  value_rvalue_t;

        typedef typename value_traits::const_t       value_const_t;
        typedef typename value_traits::const_ref_t   value_const_ref_t;
        typedef typename value_traits::const_ptr_t   value_const_ptr_t;

        struct HashNode : public Object
        {
            K key;
            V value;

            virtual hash_t hashCode() const override
            {
                return key_traits::hash_code(key);
            }
        };

        HashSet<HashNode> _F_nodes;
    public:
        HashMap();
        HashMap(const Map<K, V>& map);
        virtual ~HashMap();

        virtual Set<K>  keySet() const override;
        virtual List<V> values() const override;

        virtual bool addAll(const Map<K,V>& map) override;

        virtual void clear() override;

        virtual bool contains(key_t elem) override;
        virtual bool containsAll(const Collection<K>& c) override;

        virtual bool isEmpty() const override;

        virtual bool remove(key_t elem) override;
        virtual bool removeAll(const Set<K>& c) override;

        virtual bool retainAll(const Set<K>& c) override;

        virtual bool set(key_t key, value_t value) override;
        virtual value_t* get(key_t key) override;

        virtual size_t size() const override;
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

    template < typename E >
    UniquePointer<E[]> AbstractList<E>::toArray() const
    {
        return UniquePointer<E[]>(traits_type::copy(_F_array, _F_size));
    }
}

#endif //CPP_CONTAINER_HPP
