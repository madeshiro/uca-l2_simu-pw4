#ifndef CPP_CONTAINER_HPP
#define CPP_CONTAINER_HPP
#include "pointer.hpp"

/* HEADER : CLASS DEFINITION */

namespace UCA_L2INFO_PW4
{
    template < typename T, typename _Traits = Traits<T> >
    struct Iterator
    {
    public:
        typedef _Traits traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        ptr_t _F_begin, _F_end;

        Iterator(ptr_t begin, ptr_t end);
        virtual ~Iterator() = delete;
    };

    template < typename T, typename _Traits = Traits<T> >
    struct ConstIterator
    {
    public:
        typedef _Traits traits_type;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        const_ptr_t _F_begin, _F_end;

        ConstIterator(const_ptr_t begin, const_ptr_t end);
        virtual ~ConstIterator() = delete;
    };

    template < typename T, typename _Traits = Traits<T> >
    struct Iterable : public Object
    {
        typedef _Traits traits_type;
        typedef typename traits_type::ptr_t         ptr_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        virtual Iterator<T, traits_type> iterator() = 0;
        virtual ConstIterator<T, traits_type> const_iterator() const = 0;

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
    public:
        typedef Traits<E>                traits_type;
        typedef Alloc<E[], traits_type>  allocator;
        typedef Delete<E[], traits_type> deleter;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        virtual bool add(value_t elem) = 0;
        virtual bool addAll(const Collection<E>& c) = 0;

        virtual void clear() = 0;

        virtual bool contains(value_t elem) const = 0;
        virtual bool containsAll(const Collection<E>& c) const = 0;

        virtual bool isEmpty() const = 0;

        virtual bool remove(value_t elem) = 0;
        virtual bool removeAll(const Collection<E>& c) = 0;
        virtual bool removeIf(Predicate<const_ref_t>& filter) = 0;

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
    public:
        typedef typename Collection<E>::traits_type traits_type;
        typedef typename Collection<E>::allocator allocator;
        typedef typename Collection<E>::deleter   deleter;

        typedef typename Collection<E>::value_t   value_t;
        typedef typename Collection<E>::ref_t     ref_t;
        typedef typename Collection<E>::ptr_t     ptr_t;
        typedef typename Collection<E>::rvalue_t  rvalue_t;

        typedef typename Collection<E>::const_t       const_t;
        typedef typename Collection<E>::const_ref_t   const_ref_t;
        typedef typename Collection<E>::const_ptr_t   const_ptr_t;

        List() = default;
        virtual ~List() = 0;

        virtual bool remove(uint_t index) = 0;
        virtual UniquePointer<E> set(value_t elem, uint_t index) = 0;
        virtual ref_t get(uint_t index) = 0;

        virtual int indexOf(const_ref_t elem) const = 0;

        virtual ref_t operator[](uint_t index) { return get(index); }
    };

    template<typename E>
    class AbstractList : public List<E>
    {
    public:
        typedef typename List<E>::traits_type traits_type;
        typedef typename List<E>::allocator   allocator;
        typedef typename List<E>::deleter     deleter;

        typedef typename List<E>::value_t   value_t;
        typedef typename List<E>::ref_t     ref_t;
        typedef typename List<E>::ptr_t     ptr_t;
        typedef typename List<E>::rvalue_t  rvalue_t;

        typedef typename List<E>::const_t       const_t;
        typedef typename List<E>::const_ref_t   const_ref_t;
        typedef typename List<E>::const_ptr_t   const_ptr_t;

    protected:
        ptr_t  _F_array;
        size_t _F_size;

        AbstractList(uint_t initCapacity = 0);
        AbstractList(ptr_t array, size_t size = 0);

        virtual bool grow(size_t currentCapacity, size_t addCapacity = 1u);
    public:
        AbstractList(const AbstractList<E>& obj);
        virtual ~AbstractList() override;

        virtual void clear() override;

        virtual bool contains(value_t elem) const override;
        virtual bool containsAll(const Collection<E>& c) const override;

        virtual ref_t get(uint_t index) override;

        virtual int indexOf(const_ref_t elem) const override;

        virtual bool isEmpty() const override;

        virtual bool retainAll(const Collection<E>& c) override;

        virtual UniquePointer<E> set(value_t elem, uint_t index) override;

        virtual size_t size() const override;

        virtual UniquePointer<E[]> toArray() const override;

        virtual Iterator<E, traits_type> iterator();
        virtual ConstIterator<E, traits_type> const_iterator() const;
    };

    template<typename E>
    class ArrayList : public List<E>
    {
    public:
        typedef typename AbstractList<E>::traits_type traits_type;
        typedef typename AbstractList<E>::allocator   allocator;
        typedef typename AbstractList<E>::deleter     deleter;

        typedef typename AbstractList<E>::value_t   value_t;
        typedef typename AbstractList<E>::ref_t     ref_t;
        typedef typename AbstractList<E>::ptr_t     ptr_t;
        typedef typename AbstractList<E>::rvalue_t  rvalue_t;

        typedef typename AbstractList<E>::const_t       const_t;
        typedef typename AbstractList<E>::const_ref_t   const_ref_t;
        typedef typename AbstractList<E>::const_ptr_t   const_ptr_t;

        ArrayList();
        ArrayList(const ArrayList<E>& obj);

        virtual bool add(value_t elem) override;
        virtual bool addAll(const Collection<E>& c) override;

        virtual bool remove(value_t elem) override;
        virtual bool remove(uint_t index) override;
        virtual bool removeAll(const Collection<E>& c);
        virtual bool removeIf(Predicate<const_ref_t>& filter);
    };

    template < typename E >
    class Vector : public AbstractList<E>
    {
    public:
        typedef typename AbstractList<E>::traits_type traits_type;
        typedef typename AbstractList<E>::allocator   allocator;
        typedef typename AbstractList<E>::deleter     deleter;

        typedef typename AbstractList<E>::value_t   value_t;
        typedef typename AbstractList<E>::ref_t     ref_t;
        typedef typename AbstractList<E>::ptr_t     ptr_t;
        typedef typename AbstractList<E>::rvalue_t  rvalue_t;

        typedef typename AbstractList<E>::const_t       const_t;
        typedef typename AbstractList<E>::const_ref_t   const_ref_t;
        typedef typename AbstractList<E>::const_ptr_t   const_ptr_t;

    protected:
        uint_t _F_capacity;
        uint_t _F_capacityIncrement;

        bool growVector();
    public:
        Vector(uint_t capacityIncrement = 32);
        Vector(const Vector<E>& obj);

        virtual bool add(value_t elem) override;
        virtual bool addAll(const Collection<E>& c) override;

        virtual uint_t capacity() const final;

        virtual void clear() override;
        virtual void clearUnused();

        virtual bool remove(value_t elem) override;
        virtual bool remove(uint_t index) override;
        virtual bool removeAll(const Collection<E>& c) override;
        virtual bool removeIf(Predicate<const_ref_t>& filter) override;

        virtual void setCapacityIncrement(uint_t increment) final;
        virtual uint_t getCapacityIncrement() const final;
    };

    template<typename E>
    class Set : public Collection<E>
    {
    public:
        typedef typename Collection<E>::traits_type traits_type;

        typedef typename Collection<E>::value_t   value_t;
        typedef typename Collection<E>::ref_t     ref_t;
        typedef typename Collection<E>::ptr_t     ptr_t;
        typedef typename Collection<E>::rvalue_t  rvalue_t;

        typedef typename Collection<E>::const_t       const_t;
        typedef typename Collection<E>::const_ref_t   const_ref_t;
        typedef typename Collection<E>::const_ptr_t   const_ptr_t;

    protected:
        bool _F_needUpdate;
        UniquePointer<E[]> _F_toArray;

        Set(): _F_needUpdate(false), _F_toArray(nullptr) {}

        // TODO: Recheck the update thing about Iterator
        virtual void needUpdate(bool status = true) final {_F_needUpdate=status;}
        virtual bool doNeedUpdate() const final {return _F_needUpdate;}
    public:
        virtual Iterator<E> iterator() override;
        virtual ConstIterator<E> const_iterator() const override;
    };

    template<typename E>
    /**
     * @warning E needs to have these 3 operators {<, >, ==} !
     */
    class SortedSet : public Set<E>
    {
    public:
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
            Node *left, *right;
            E element;

            Node(): left(nullptr), right(nullptr) {/*...*/}
            virtual ~Node()
            {
                if (left) delete left;
                if (right) delete right;
            }
        };
    private:
        Node *_F_tree;
        uint_t _F_size;
        SortMethod<const E&, const E&> _F_sortMethod;

    protected:
        void recursive_assign(Node* current, const Node * const node);
    public:
        SortedSet(SortMethod<const E&, const E&> sortMethod = [](const E& e1, const E& e2) -> int
                {
                    return Comparable<E>::CompareTo(e1, e2);
                }
        );
        SortedSet(const SortedSet<E> &cpy);
        virtual ~SortedSet() override;

        virtual bool add(value_t elem);
        virtual bool addAll(const Collection<E>& c);

        virtual void clear();

        virtual bool contains(value_t elem) const;
        virtual bool containsAll(const Collection<E>& c) const;

        virtual bool isEmpty() const;

        virtual bool remove(value_t elem);
        virtual bool removeAll(const Collection<E>& c);
        virtual bool removeIf(Predicate<const_ref_t>& filter);

        virtual bool retainAll(const Collection<E>& c);

        virtual size_t size() const;

        virtual UniquePointer<E[]> toArray() const;
    };

    template <typename E>
    class HashSet : public Set<E>
    {
        template<typename K, typename V>
        friend class HashMap;
    public:
        typedef Traits<E> traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

    private:
        struct Bucket
        {
            value_t *element;

            Bucket(): element(nullptr) {/* ... */}
            virtual ~Bucket() {
                if (element)
                {
                    delete element;
                }
            };

            virtual bool operator ==(const_ref_t elem) {
                return element ? hashCode() == traits_type::hash_code(elem) : false;
            }

            virtual hash_t hashCode() {
                return traits_type::hash_code(*element);
            }

            virtual Bucket& operator =(value_t v) {
                if (element == nullptr)
                {
                    element = new value_t(v);
                }
                else
                {
                    *element = v;
                }
                return *this;
            }

            virtual operator bool() const {
                return element == nullptr;
            }

            virtual void clear() {
                delete element;
                element = nullptr;
            }
        } *_F_set;

        uint_t _F_size;
        uint_t _F_capacity;
        uint_t _F_padding=0;

        float _F_loadFactor;

        /**
         * Replaces or adds an element to the set. Because hashCode implementation may differ from time to time,
         * in order to especially optimize HashMap, we have created this function that add or replace the current
         * element in the HashSet.
         * @param elem The element to put in the set, replacing or adding it to the list.
         */
        virtual bool setElement(value_t elem, bool replace = true);

        /**
         *
         * @param padding
         */
        virtual void setPadding(uint_t padding);

        virtual void grow(uint_t addCapacity);
    public:
        HashSet(uint_t initialCapacity);
        HashSet(uint_t initialCapacity = 16u, float loadFactor = 0.75);
        HashSet(const Collection<E>& collection);
        virtual ~HashSet() override;

        virtual bool add(value_t elem) override {return setElement(elem, false);}
        virtual bool addAll(const Collection<E>& c) override;

        virtual void clear() override;

        virtual bool contains(value_t elem) const override;
        virtual bool containsAll(const Collection<E>& c) const override;

        virtual bool isEmpty() const override;

        virtual bool remove(value_t elem) override;
        virtual bool removeAll(const Collection<E>& c) override;
        virtual bool removeIf(Predicate<const_ref_t>& filter) override;

        virtual bool retainAll(const Collection<E>& c) override;

        virtual size_t size() const override;

        virtual UniquePointer<E[]> toArray() const override;
    };

    template<typename E>
    class ChainedList : public Collection<E>
    {
    public:
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

            Chain() = default;
            Chain(E elem, Chain* prev = nullptr): prev(prev), next(nullptr), elem(elem) {
                if (prev)
                {
                    prev->next = this;
                }
            }

            void unchain() {
                prev = nullptr;
                next = nullptr;
            }

            virtual ~Chain() {
                if (next)
                {
                    delete next;
                }
            }
        };
    protected:
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
        virtual bool removeIf(Predicate<const_ref_t>& filter) override;

        virtual bool retainAll(const Collection<E>& c) override;

        virtual size_t size() const override;

        virtual UniquePointer<E[]> toArray() const override;
    };

    template<typename K, typename V>
    class Map
    {
    public:
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
        virtual value_ptr_t get(key_t key) const = 0;
        
        virtual size_t size() const = 0;

        inline virtual value_ptr_t operator[](key_const_t key) const {
            return this->get(key);
        };

        inline virtual operator bool() const {
            return !this->isEmpty();
        }
    };

    template<typename K, typename V>
    class HashMap : public Map<K, V>
    {
    public:
        typedef typename Map<K, V>::key_traits    key_traits;
        typedef typename Map<K, V>::value_t       key_t;
        typedef typename Map<K, V>::ref_t         key_ref_t;
        typedef typename Map<K, V>::ptr_t         key_ptr_t;
        typedef typename Map<K, V>::rvalue_t      key_rvalue_t;

        typedef typename Map<K, V>::const_t       key_const_t;
        typedef typename Map<K, V>::const_ref_t   key_const_ref_t;
        typedef typename Map<K, V>::const_ptr_t   key_const_ptr_t;

        typedef typename Map<K, V>::value_traits  value_traits;
        typedef typename Map<K, V>::value_t       value_t;
        typedef typename Map<K, V>::ref_t         value_ref_t;
        typedef typename Map<K, V>::ptr_t         value_ptr_t;
        typedef typename Map<K, V>::rvalue_t      value_rvalue_t;

        typedef typename Map<K, V>::const_t       value_const_t;
        typedef typename Map<K, V>::const_ref_t   value_const_ref_t;
        typedef typename Map<K, V>::const_ptr_t   value_const_ptr_t;

        struct HashNode : public Object
        {
            K key;
            V value;

            virtual hash_t hashCode() const override
            {
                return key_traits::hash_code(key);
            }
        };

    private:
        HashSet<HashNode> _F_nodes;
    public:
        HashMap();
        HashMap(const HashMap<K, V>& map);
        virtual ~HashMap() = default;

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
        virtual value_ptr_t get(key_t key) const override;

        virtual size_t size() const override;
    };

    template < typename T, typename _Traits >
    Iterator<T, _Traits>::Iterator(ptr_t begin, ptr_t end)
    {
        _F_begin = begin;
        _F_end   = end;
    }

    template < typename T, typename _Traits >
    ConstIterator<T, _Traits>::ConstIterator(const_ptr_t begin, const_ptr_t end)
    {
        _F_begin = begin;
        _F_end = end;
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
        return const_iterator()._F_begin;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::const_ptr_t Iterable<T, _Traits>::cend() const
    {
        return const_iterator()._F_end;
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
        return const_iterator()._F_end-1;
    }

    template < typename T, typename _Traits >
    typename Iterable<T, _Traits>::const_ptr_t Iterable<T, _Traits>::crend() const
    {
        return const_iterator()._F_begin-1;
    }

    template < typename E >
    AbstractList<E>::AbstractList(uint_t initCapacity):
        _F_array(initCapacity ? allocator::alloc(initCapacity) : nullptr),
        _F_size(0u)
    {
        /* ... */
    }

    template < typename E >
    AbstractList<E>::AbstractList(ptr_t array, size_t size):
        _F_array(array), _F_size(size)
    {
        /* ... */
    }

    template < typename E >
    bool AbstractList<E>::grow(size_t currentCapacity, size_t addCapacity)
    {
        ptr_t newArray(allocator::alloc(currentCapacity+addCapacity));
        if (newArray)
        {
            return _F_size == traits_type::fill(_F_array, newArray, _F_size);
        }
        else return false;
    }

    template < typename E >
    AbstractList<E>::AbstractList(const AbstractList<E> &obj):
        AbstractList<E>(traits_type::copy(obj._F_array, obj._F_size), obj._F_size)
    {
        /* ... */
    }

    template < typename E >
    AbstractList<E>::~AbstractList()
    {
        AbstractList<E>::clear();
    }

    template < typename E >
    void AbstractList<E>::clear()
    {
        if (_F_array)
        {
            delete[] _F_array;
        }

        _F_size = 0u;
    }

    template < typename E >
    bool AbstractList<E>::contains(value_t elem) const
    {
        for (value_t e : (*this))
        {
            if (e == elem)
                return true;
        }

        return false;
    }

    template < typename E >
    bool AbstractList<E>::containsAll(const Collection<E> &c) const
    {
        for (value_t elem : c)
        {
            if (contains(elem) == false)
                return false;
        }

        return true;
    }

    template < typename E >
    typename AbstractList<E>::ref_t AbstractList<E>::get(uint_t index)
    {
        return _F_array[index];
    }

    template < typename E >
    int AbstractList<E>::indexOf(const_ref_t elem) const
    {
        for (int i = 0; (uint_t) i < _F_size; i++)
        {
            if (_F_array[i] == elem)
                return i;
        }
        return -1;
    }

    template < typename E >
    bool AbstractList<E>::isEmpty() const
    {
        return _F_size > 0;
    }

    template < typename E >
    bool AbstractList<E>::retainAll(const Collection<E> &c)
    {
        ptr_t newArray = allocator::alloc(c.size()), __p = newArray;
        if (newArray)
        {
            for (const_t elem : c)
            {
                int _indexOf(indexOf(elem));
                if (_indexOf >= 0)
                {
                    (*__p) = _F_array[_indexOf];
                    __p++;
                }
            }

            this->clear();

            _F_array = newArray;
            _F_size  = (__p - newArray)/sizeof(value_t);
        }
        else return false;
    }

    template < typename E >
    UniquePointer<E> AbstractList<E>::set(value_t elem, uint_t index)
    {
        if (index >= _F_size)
            return UniquePointer<E>(nullptr);
        else
        {
            ptr_t p = allocator::alloc();
            if (p) (*p) = _F_array[index];

            _F_array[index] = elem;
            return p;
        }
    }

    template < typename E >
    size_t AbstractList<E>::size() const
    {
        return _F_size;
    }

    template < typename E >
    UniquePointer<E[]> AbstractList<E>::toArray() const
    {
        return UniquePointer<E[]>(traits_type::copy(_F_array, _F_size));
    }

    template < typename E >
    Iterator<E, typename AbstractList<E>::traits_type> AbstractList<E>::iterator()
    {
        return Iterator<E, traits_type>(_F_array, (&_F_array[_F_size]) - 1);
    }

    template < typename E >
    ConstIterator<E, typename AbstractList<E>::traits_type> AbstractList<E>::const_iterator() const
    {
        return ConstIterator<E, traits_type>(_F_array, (&_F_array[_F_size]) - 1);
    }

    template < typename E >
    ArrayList<E>::ArrayList(): AbstractList<E>()
    {
        /* ... */
    }

    template < typename E >
    ArrayList<E>::ArrayList(const ArrayList<E> &obj): AbstractList<E>(obj)
    {
        /* ... */
    }

    template < typename E >
    bool ArrayList<E>::add(value_t elem)
    {
        if (AbstractList<E>::grow(this->_F_size))
        {
            this->_F_array[this->_F_size] = elem;
            this->_F_size++;
        }
        else
        {
            return false;
        }
    }

    template < typename E >
    bool ArrayList<E>::addAll(const Collection<E> &c)
    {
        if (AbstractList<E>::grow(this->_F_size, c.size()))
        {
            UniquePointer<E[]> collection = c.toArray();
            for (size_t i = 0; i < c.size(); i++)
            {
                this->_F_array[i+this->_F_size] = collection[i];
            }

            return true;
        }
        else
        {
            return false;
        }
    }

    template < typename E >
    bool ArrayList<E>::remove(value_t elem)
    {
        Predicate<const_ref_t> predicate = [elem](const_ref_t e) -> bool {
            return elem == e;
        };

        return removeIf(predicate);
    }

    template < typename E >
    bool ArrayList<E>::remove(uint_t index)
    {
        if (index < this->_F_size)
        {
            ptr_t newArray = allocator::alloc(this->_F_size - 1);
            if (newArray)
            {
                for (uint_t i(0), j(0); i < this->_F_size; i++)
                {
                    if (i != index)
                    {
                        newArray[j] = this->_F_array[i];
                        j++;
                    }
                }

                this->_F_size--;
            }
            else return false;
        }
        return true;
    }

    template < typename E >
    bool ArrayList<E>::removeAll(const Collection<E> &c)
    {
        UniquePointer<int[]> elemIndexes(new int[c.size()]);
        uint_t f(0);

        for (value_t elem : c)
        {
            int index(this->indexOf(c));
            if (index != -1)
            {
                elemIndexes[f] = index;
                f++;
            }
        }

        if (f > 0 && this->_F_size - f > 0)
        {
            ptr_t newArray = allocator::alloc(this->_F_size - f);
            if (newArray)
            {
                for (size_t i(0), j(0); i < this->_F_size; i++)
                {
                    if (elemIndexes[f] != -1 && (size_t) elemIndexes[f] == i)
                    {
                        f++;
                    }
                    else
                    {
                        newArray[j] = this->_F_array[i];
                        j++;
                    }
                }

                deleter::free(this->_F_array);
                this->_F_array = newArray;
                this->_F_size -= f;
            }
            else return false;
        }
        else if (this->_F_size - f == 0)
        {
            this->clear();
        }

        return true;
    }

    template < typename E >
    bool ArrayList<E>::removeIf(Predicate<const_ref_t> &filter)
    {
        UniquePointer<size_t[]> elemIndexes(new size_t[this->size()]);
        uint_t f(0);

        for (size_t i(0); i < this->_F_size; i++)
        {
            if (filter(this->_F_array[i]))
            {
                elemIndexes[f] = i;
                f++;
            }
        }

        if (f > 0 && this->_F_size - f > 0)
        {
            ptr_t newArray = allocator::alloc(this->_F_size - f);
            if (newArray)
            {
                for (size_t i(0), j(0), k(0); i < this->_F_size; i++)
                {
                    if (k < f && elemIndexes[k] == i)
                    {
                        k++;
                    }
                    else
                    {
                        newArray[j] = this->_F_array[i];
                        j++;
                    }
                }

                deleter::free(this->_F_array);
                this->_F_array = newArray;
                this->_F_size -= f;
            }
            else return false;
        }
        else if (this->_F_size - f == 0)
        {
            this->clear();
        }

        return true;
    }

    template < typename E >
    bool Vector<E>::growVector()
    {
        ptr_t newVector = allocator::alloc(_F_capacity+_F_capacityIncrement);
        if (newVector)
        {
            traits_type::fill(this->_F_array, newVector, this->_F_size);
            deleter::free(this->_F_array);

            _F_capacity += _F_capacityIncrement;
            this->_F_array = newVector;
        }
        else
        {
            return false;
        }
    }

    template < typename E >
    Vector<E>::Vector(uint_t capacityIncrement): AbstractList<E>(capacityIncrement),
        _F_capacityIncrement(capacityIncrement == 0 ? 1 : capacityIncrement)
    { /* ... */ }

    template < typename E >
    Vector<E>::Vector(const Vector<E> &obj): AbstractList<E>()
    {
        ptr_t newVector = allocator::alloc(obj.capacity());
        if (newVector)
        {
            traits_type::fill(obj._F_array, newVector, obj.size());
            this->_F_array = newVector;
            this->_F_size  = obj.size();
            _F_capacity    = obj._F_capacity;
            _F_capacityIncrement = obj._F_capacityIncrement;
        }
    }

    template < typename E >
    bool Vector<E>::add(value_t elem)
    {
        if (_F_capacity <= this->_F_size)
        {
            if (!growVector())
            {
                return false;
            }
        }

        this->_F_array[this->_F_size] = elem;
        this->_F_size++;
        return true;
    }

    template < typename E >
    bool Vector<E>::addAll(const Collection<E> &c)
    {
        while (this->_F_size + c.size() >= _F_capacity)
        {
            if(!growVector())
            {
                return false;
            }
        }

        for (const_t elem : c)
        {
            this->_F_array[this->_F_size] = elem;
            this->_F_size++;
        }
        return true;
    }

    template < typename E >
    uint_t Vector<E>::capacity() const
    {
        return _F_capacity;
    }

    template < typename E >
    void Vector<E>::clear()
    {
        AbstractList<E>::clear();
        _F_capacity = 0;
    }

    template < typename E >
    void Vector<E>::clearUnused()
    {
        if (_F_capacity > this->_F_size)
        {
            ptr_t clearedVector = allocator::alloc(this->_F_size);
            if (clearedVector)
            {
                traits_type::fill(this->_F_array, clearedVector, this->_F_size);
                deleter::free(this->_F_array);
                this->_F_array = clearedVector;
                _F_capacity = this->_F_size;
            }
        }
    }

    template < typename E >
    bool Vector<E>::remove(value_t elem)
    {
        UniquePointer<uint_t[]> indexes(new uint_t[this->size()]);
        uint_t nbIndexes(0);
        for (uint_t i(0); i < this->_F_size; i++)
        {
            if (this->_F_array[i] == elem)
            {
                indexes[nbIndexes] = i;
                nbIndexes++;
            }
        }

        if (nbIndexes > 0)
        {
            for (uint_t i(0), j(0), k(0); i < this->_F_size; i++)
            {
                if (k < nbIndexes && i != indexes[k])
                {
                    this->_F_array[j] = this->_F_array[i];
                }
                else if (i == indexes[k])
                {
                    k++;
                }
            }

            this->_F_size -= nbIndexes;
        }

        return true;
    }

    template < typename E >
    bool Vector<E>::remove(uint_t index)
    {
        if (index < this->_F_size)
        {
            for (uint_t i(0), j(0); i < this->_F_size; i++)
            {
                if (i != index)
                {
                    if (i != j) this->_F_size[j] = this->_F_size[i];
                    j++;
                }
            }

            this->_F_size--;
        }
        return true;
    }

    template < typename E >
    bool Vector<E>::removeAll(const Collection<E> &c)
    {
        bool status(true);

        for (auto e : c)
        {
            status = status && this->remove(e);
        }

        return status;
    }

    template < typename E >
    bool Vector<E>::removeIf(Predicate<const_ref_t> &filter)
    {
        UniquePointer<size_t[]> elemIndexes(new size_t[this->size()]);
        uint_t f(0);

        for (size_t i(0); i < this->_F_size; i++)
        {
            if (filter(this->_F_array[i]))
            {
                elemIndexes[f] = i;
                f++;
            }
        }

        if (f > 0 && this->_F_size - f > 0)
        {
            for (size_t i(0), j(0), k(0); i < this->_F_size; i++)
            {
                if (k < f && elemIndexes[k] == i)
                {
                    k++;
                }
                else
                {
                    this->_F_array[j] = this->_F_array[i];
                    j++;
                }
            }

            this->_F_size -= f;
        }
        else if (this->_F_size - f == 0)
        {
            this->clear();
        }

        return true;
    }

    template < typename E >
    void Vector<E>::setCapacityIncrement(uint_t increment)
    {
        increment = increment == 0 ? 1 : increment;
        _F_capacityIncrement = increment;
    }

    template < typename E >
    uint_t Vector<E>::getCapacityIncrement() const
    {
        return _F_capacityIncrement;
    }

    template < typename E >
    Iterator<E> Set<E>::iterator()
    {
        if (needUpdate())
        {
            _F_toArray = this->toArray();
        }

        return Iterator<E>(_F_toArray.pointer(), (&_F_toArray.pointer()[this->size()])-1);
    }

    template < typename E >
    ConstIterator<E> Set<E>::const_iterator() const
    {
        if (needUpdate())
        {
            _F_toArray = this->toArray();
        }

        return ConstIterator<E>(_F_toArray.pointer(), (&_F_toArray.pointer()[this->size()])-1);
    }

    template < typename E >
    void SortedSet<E>::recursive_assign(Node *current, const Node  * const node)
    {
        if (node->left)
        {
            current->left    = new Node();
            current->element = node->element;
            recursive_assign(current->left, node->left);
        }

        if (node->right)
        {
            current->right   = new Node();
            current->element = node->element;
            recursive_assign(current->right, node->right);
        }
    }

    template < typename E >
    SortedSet<E>::SortedSet(SortMethod<const E&, const E&> sortMethod):
        _F_tree(new Node()),
        _F_size(0u),
        _F_sortMethod(sortMethod)
    {
        /* ... */
    }

    template < typename E >
    SortedSet<E>::SortedSet(const SortedSet<E> &cpy):
        _F_tree(new Node()),
        _F_size(cpy.size()),
        _F_sortMethod(cpy._F_sortMethod)
    {
        void (*browse)(Node*, const Node* const) = [&] (Node* dest, const Node* const src)
        {
            if (src->left)
            {
                dest->left    = new Node();
                dest->element = src->element;
                browse(dest->left, src->left);
            }

            if (src->right)
            {
                dest->right   = new Node();
                dest->element = src->element;
                browse(dest->right, src->right);
            }
        };
        
        _F_tree->element = cpy._F_tree->element;
        browse(_F_tree, cpy._F_tree);
    }

    template < typename E >
    SortedSet<E>::~SortedSet<E>()
    {
        delete _F_tree;
    }

    template < typename E >
    bool SortedSet<E>::add(value_t elem)
    {
        Node* (*browse)(Node*) = [&, this](Node* node)
        {
            int sort(this->_F_sortMethod(elem, node->element));
            if (sort < 0)
            {
                if (node->left)
                {
                    return browse(node->left);
                }
                else
                {
                    node->left = new Node();
                    return node->left;
                }
            }
            else if (sort > 0)
            {
                if (node->right)
                {
                    return browse(node->right);
                }
                else
                {
                    node->right = new Node();
                    return node->right;
                }
            }
            else return nullptr;
        };

        Node* emplacement = (this->_F_size == 0 ? _F_tree : browse(_F_tree));
        if (emplacement)
        {
            emplacement->element = elem;
            this->_F_size++;
        }

        return true;
    }

    template < typename E >
    bool SortedSet<E>::addAll(const Collection<E> &c)
    {
        for (auto e : c)
        {
            add(e);
        }

        return true;
    }

    template < typename E >
    void SortedSet<E>::clear()
    {
        delete _F_tree;

        _F_tree = new Node();
    }

    template < typename E >
    bool SortedSet<E>::contains(value_t elem) const
    {
        bool (*browse)(const Node* const) = [&,this] (const Node* const node)
        {
            if (!node) return false;

            int comparison(this->_F_sortMethod(elem, node->element));
            switch (comparison)
            {
                case -1:
                    return browse(node->left);
                case 0:
                    return true;
                case 1:
                    return browse(node->right);
                default:
                    return false;
            }
        };
        
        return browse(_F_tree);
    }

    template < typename E >
    bool SortedSet<E>::containsAll(const Collection<E> &c) const
    {
        for (auto e : c)
        {
            if (!contains(e))
                return false;
        }

        return true;
    }

    template < typename E >
    bool SortedSet<E>::isEmpty() const
    {
        return this->_F_size == 0;
    }

    template < typename E >
    bool SortedSet<E>::remove(value_t elem)
    {
        return removeIf([=](const_ref_t e) -> bool {return elem == e;});
    }

    template < typename E >
    bool SortedSet<E>::removeAll(const Collection<E> &c)
    {
        for (auto e : c)
        {
            remove(e);
        }

        return true;
    }

    template < typename E >
    bool SortedSet<E>::removeIf(Predicate<const_ref_t> &filter)
    {
        // TODO: SortedSet<E>::removeIf
        return false;
    }

    template < typename E >
    bool SortedSet<E>::retainAll(const Collection<E> &c)
    {
        // TODO: SortedSet<E>::retainAll
        return false;
    }

    template < typename E >
    size_t SortedSet<E>::size() const
    {
        return _F_size;
    }

    template < typename E >
    UniquePointer<E[]> SortedSet<E>::toArray() const
    {
        // TODO: SortedSet<E>::toArray
        return nullptr;
    }

    template < typename E >
    HashSet<E>::HashSet(uint_t initialCapacity): HashSet(initialCapacity, .75f)
    { /* ... */ }

    template < typename E >
    HashSet<E>::HashSet(uint_t initialCapacity, float loadFactor):
        _F_set(new Bucket[initialCapacity]), _F_capacity(initialCapacity), _F_size(0u), _F_loadFactor(loadFactor)
    {
        /* ... */
    }

    template < typename E >
    HashSet<E>::HashSet(const Collection<E> &collection): HashSet(collection.size()/.75f, .75f)
    {
        for (auto e : collection)
        {
            add(e);
        }
    }

    template < typename E >
    HashSet<E>::~HashSet()
    {
        if (_F_set)
        {
            delete[] _F_set;
        }
    }

    template < typename E >
    bool HashSet<E>::setElement(value_t elem, bool replace)
    {
        hash_t elemHash(traits_type::hash_code(elem));
        uint_t index = elemHash%_F_capacity;

        bool (*browse)(int) = [&, this](int off) -> bool {
            if (off > _F_padding) return false;

            uint_t hashIndex((index+off)%_F_capacity);

            if (_F_set[hashIndex])
            {
                _F_set[hashIndex] = elem;
                _F_size++;
            }
            else if (_F_set[hashIndex] == elem)
            {
                if (replace) _F_set[hashIndex] = elem;
            }
            else
            {
                return browse(off+1);
            }
            return true;
        };

        return browse(0);
    }

    template < typename E >
    void HashSet<E>::setPadding(uint_t padding)
    {
        if (_F_padding < padding)
        {
            _F_padding = padding;
        }
    }

    template < typename E >
    void HashSet<E>::grow(uint_t addCapacity)
    {
        uint_t newCapacity(_F_capacity+addCapacity);
        Bucket* buckets = new Bucket[newCapacity];

        _F_padding = 0;

        for (uint_t i(0); i < _F_capacity; i++)
        {
            if (!_F_set[i])
            {
                hash_t hashIndex(_F_set[i].hashCode()%newCapacity);

                uint_t (*assign)(uint_t) = [&,hashIndex,this] (uint_t off) -> uint_t {
                    if (buckets[(hashIndex+off)%newCapacity])
                    {
                        buckets[(hashIndex+off)%newCapacity] = _F_set[i];
                        return off;
                    }
                    else
                    {
                        return assign(off+1);
                    }
                };

                setPadding(assign(0));
            }
        }

        delete[] _F_set;
        _F_capacity = newCapacity;
        _F_set = buckets;
    }

    template < typename E >
    bool HashSet<E>::addAll(const Collection<E> &c)
    {
        bool status(true);
        for (auto e : c)
        {
            status = add(e) && status;
        }
        return status;
    }

    template < typename E >
    void HashSet<E>::clear()
    {
        for (uint_t i(0); i < _F_capacity; i++)
        {
            _F_set[i].clear();
        }

        _F_size = 0;
    }

    template < typename E >
    bool HashSet<E>::contains(value_t elem) const
    {
        hash_t hash_code(traits_type::hash_code(elem));
        uint_t index(hash_code%_F_capacity);

        bool (*browse)(uint_t) = [&,index,this](uint_t off) {
            if (off > _F_padding)
            {
                return false;
            }
            if (_F_set[(index+off)%_F_capacity] == elem)
            {
                return true;
            }
            else
            {
                return browse(off+1);
            }
        };

        return browse(0u);
    }

    template < typename E >
    bool HashSet<E>::containsAll(const Collection<E> &c) const
    {
        for (auto e : c)
        {
            if (!contains(e))
                return false;
        }

        return true;
    }

    template < typename E >
    bool HashSet<E>::isEmpty() const
    {
        return _F_size == 0;
    }

    template < typename E >
    bool HashSet<E>::remove(value_t elem)
    {
        hash_t hash_code(traits_type::hash_code(elem));
        uint_t hashIndex(hash_code%_F_capacity);

        for (uint_t off(0); off <= _F_padding; off++)
        {
            uint_t index((hashIndex+off)%_F_capacity);

            if (_F_set[index] == elem)
            {
                _F_set[index].clear();
                _F_size--;
            }
        }

        return true;
    }

    template < typename E >
    bool HashSet<E>::removeAll(const Collection<E> &c)
    {
        for (auto e : c)
        {
            remove(e);
        }

        return true;
    }

    template < typename E >
    bool HashSet<E>::removeIf(Predicate<const_ref_t> &filter)
    {
        for (uint_t i(0); i < _F_capacity; i++)
        {
            if (_F_set[i] && filter(_F_set[i].element))
            {
                _F_set[i].clear();
                _F_size--;
            }
        }

        return true;
    }

    template < typename E >
    bool HashSet<E>::retainAll(const Collection<E> &c)
    {
        // TODO: HashSet<E>::retainAll
        return false;
    }

    template < typename E >
    size_t HashSet<E>::size() const
    {
        return _F_size;
    }

    template < typename E >
    UniquePointer<E[]> HashSet<E>::toArray() const
    {
        ptr_t elements = traits_type::alloc(size());
        if (elements)
        {
            for (uint_t i(0), j(0); i < _F_capacity && j < _F_size; i++)
            {
                if (_F_set[i])
                {
                    elements[j] = _F_set[i].element;
                    j++;
                }
            }
        }

        return UniquePointer<E[]>(elements);
    }

    template < typename E >
    ChainedList<E>::ChainedList(): _F_first(nullptr), _F_size(0u)
    {
        /* ... */
    }

    template < typename E >
    ChainedList<E>::ChainedList(const Collection<E> &collection): _F_first(nullptr), _F_size(0u)
    {
        Chain ** current(_F_first);
        Chain * prev(nullptr);
        for (const_t elem : collection)
        {
            *current = new Chain(elem, prev);
            prev     = *current;
            *current = &(*current)->next;
            _F_size++;
        }
    }

    template < typename E >
    ChainedList<E>::~ChainedList()
    {
        Chain* current, *next = _F_first;
        while (next)
        {
            current = next;
            next = next->next;
            delete current;
        }
    }

    template < typename E >
    bool ChainedList<E>::add(value_t elem)
    {
        if (_F_first == nullptr)
        {
            _F_first = new Chain(elem);
            _F_size++;
        }
        else
        {
            Chain* chain = _F_first;
            while (chain->next != nullptr)
            {
                chain = chain->next;
            }

            chain->next = new Chain(elem, chain);
            _F_size++;
        }

        return true;
    }

    template < typename E >
    bool ChainedList<E>::addAll(const Collection<E> &c)
    {
        return false;
    }

    template < typename E >
    void ChainedList<E>::clear()
    {
        delete _F_first;
        _F_size = 0u;
    }

    template < typename E >
    bool ChainedList<E>::contains(value_t elem)
    {
        Chain* chain = _F_first;
        while (chain)
        {
            if (chain->elem == elem)
                return true;
            else
                chain = chain->next;
        }

        return false;
    }

    template < typename E >
    bool ChainedList<E>::containsAll(const Collection<E> &c)
    {
        for (auto e : c)
        {
            if (contains(e))
                return true;
        }

        return false;
    }

    template < typename E >
    bool ChainedList<E>::isEmpty() const
    {
        return _F_size == 0u;
    }

    template < typename E >
    bool ChainedList<E>::remove(value_t elem)
    {
        return removeIf([=](const_ref_t value) { value == elem; });
    }

    template < typename E >
    bool ChainedList<E>::removeAll(const Collection<E> &c)
    {
        bool status(true);

        for (auto e : c)
        {
            status = remove(e) && status;
        }

        return status;
    }

    template < typename E >
    bool ChainedList<E>::removeIf(Predicate<const_ref_t> &filter)
    {
        return false;
    }

    template < typename E >
    bool ChainedList<E>::retainAll(const Collection<E> &c)
    {
        return false;
    }

    template < typename E >
    size_t ChainedList<E>::size() const
    {
        return _F_size;
    }

    template < typename E >
    UniquePointer<E[]> ChainedList<E>::toArray() const
    {
        return nullptr;
    }

    template < typename K, typename V >
    HashMap<K,V>::HashMap(): _F_nodes()
    {
        /* ... */
    }

    template < typename K, typename V >
    HashMap<K,V>::HashMap(const HashMap<K,V>& map): _F_nodes(map._F_nodes)
    {
        /* ... */
    }

    template < typename K, typename V >
    Set<K> HashMap<K, V>::keySet() const
    {
        HashSet<K> keys;

        for (const HashNode node : _F_nodes)
        {
            keys.add(static_cast<key_const_t>(node.key));
        }

        return keys;
    }

    template < typename K, typename V >
    List<V> HashMap<K,V>::values() const
    {
        ArrayList<K> values;

        for (const HashNode node : _F_nodes)
        {
            values.add(static_cast<value_const_t>(node.value));
        }

        return values;
    }

    template < typename K, typename V >
    bool HashMap<K,V>::addAll(const Map<K, V> &map)
    {
        bool status(true);
        for (auto key : map.keySet())
        {
            status = this->set(key, *map.get(key)) && status;
        }

        return status;
    }

    template < typename K, typename V >
    void HashMap<K,V>::clear()
    {
        _F_nodes.clear();
    }

    template < typename K, typename V >
    bool HashMap<K,V>::contains(key_t elem)
    {
        HashNode node;
        node.key = elem;
        return _F_nodes.contains(node);
    }

    template < typename K, typename V >
    bool HashMap<K, V>::containsAll(const Collection<K> &c)
    {
        for (auto key : c)
        {
            if (!contains(key))
                return false;
        }
        return true;
    }

    template < typename K, typename V >
    bool HashMap<K, V>::isEmpty() const
    {
        return _F_nodes.isEmpty();
    }

    template < typename K, typename V >
    bool HashMap<K, V>::remove(key_t elem)
    {
        HashNode node;
        node.key = elem;
        return _F_nodes.remove(node);
    }

    template < typename K, typename V >
    bool HashMap<K, V>::removeAll(const Set<K> &c)
    {
        bool status(true);
        for (auto key : c.keySet())
        {
            status = remove(key) && status;
        }

        return status;
    }

    template < typename K, typename V >
    bool HashMap<K, V>::retainAll(const Set<K> &c)
    {
        // TODO: HashMap<K,V>::retainAll
        return false;
    }

    template < typename K, typename V >
    bool HashMap<K, V>::set(key_t key, value_t value)
    {
        return _F_nodes.setElement((HashNode){key, value});
    }

    template < typename K, typename V >
    typename HashMap<K,V>::value_ptr_t HashMap<K, V>::get(key_t key) const
    {
        if (size()>0)
        {
            hash_t keyHash(key_traits::hash_code(key));
            uint_t index(keyHash%_F_nodes._F_capacity);
            for (uint_t offset(0); offset < _F_nodes._F_padding; offset++)
            {
                if (_F_nodes._F_set[index + offset].hashCode() == keyHash)
                {
                    return &(_F_nodes._F_set[index + offset].element->value);
                }
            }
        }
        return nullptr;
    }

    template < typename K, typename V >
    size_t HashMap<K, V>::size() const
    {
        return _F_nodes.size();
    }
}

#endif //CPP_CONTAINER_HPP
