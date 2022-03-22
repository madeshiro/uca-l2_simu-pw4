#ifndef CPP_POINTER_HPP
#define CPP_POINTER_HPP
#include "defines.h"
#include "alloc.hpp"
#include "object.h"

namespace UCA_L2INFO_PW4
{
    template < typename T, typename _Deleter = Delete<T> >
    class Pointer : public Object
    {
    public:
        typedef _Deleter deleter;
        typedef typename deleter::value_t   value_t;
        typedef typename deleter::ref_t     ref_t;
        typedef typename deleter::rvalue_t  rvalue_t;
        typedef typename deleter::ptr_t     ptr_t;

        typedef typename deleter::const_t     const_t;
        typedef typename deleter::const_ptr_t const_ptr_t;
        typedef typename deleter::const_ref_t const_ref_t;

        typedef Pointer<T, _Deleter> pointer_t;
    protected:
        ptr_t _F_ptr;
        Pointer(ptr_t ptr);
        virtual ~Pointer() = 0;
    public:
        virtual ptr_t pointer() const;

        inline virtual ref_t operator *();
        inline virtual ptr_t operator ->();
        inline virtual ref_t operator [](size_t __index);

        virtual Pointer<T, _Deleter>& operator =(ptr_t ptr) = 0;

        virtual bool operator ==(const_ptr_t ptr) const;
        virtual bool operator <=(const_ptr_t ptr) const;
        virtual bool operator >=(const_ptr_t ptr) const;
        virtual bool operator >(const_ptr_t ptr) const;
        virtual bool operator <(const_ptr_t ptr) const;

        inline virtual operator bool() const;
        inline virtual operator ptr_t() const;

        hash_t hashCode() const override;
    };

    template < typename T, typename _Deleter = Delete<T> >
    class UniquePointer : public Pointer<T, _Deleter>
    {
    public:
        typedef typename Pointer<T, _Deleter>::value_t   value_t;
        typedef typename Pointer<T, _Deleter>::ref_t     ref_t;
        typedef typename Pointer<T, _Deleter>::rvalue_t  rvalue_t;
        typedef typename Pointer<T, _Deleter>::ptr_t     ptr_t;

        typedef typename Pointer<T, _Deleter>::const_t     const_t;
        typedef typename Pointer<T, _Deleter>::const_ptr_t const_ptr_t;
        typedef typename Pointer<T, _Deleter>::const_ref_t const_ref_t;

        typedef typename Pointer<T, _Deleter>::deleter deleter;
        typedef UniquePointer<T, _Deleter>             pointer_t;

        UniquePointer(ptr_t ptr = nullptr);
        UniquePointer(pointer_t& ptr);
        virtual ~UniquePointer() override;

        virtual void reset(ptr_t ptr);
        virtual ptr_t release();
        virtual void swap(UniquePointer<T, _Deleter> &sp);

        virtual UniquePointer<T, _Deleter>& operator =(ptr_t ptr) override;
        UniquePointer<T, _Deleter>& operator =(UniquePointer<T, _Deleter>& up);
    };


    template < typename T, typename _Deleter = Delete<T> >
    class SharedPointer : public Pointer<T, _Deleter>
    {
        template < typename _T, typename Deleter_ >
        friend class WeakPointer;
    public:
        typedef typename Pointer<T, _Deleter>::value_t   value_t;
        typedef typename Pointer<T, _Deleter>::ref_t     ref_t;
        typedef typename Pointer<T, _Deleter>::rvalue_t  rvalue_t;
        typedef typename Pointer<T, _Deleter>::ptr_t     ptr_t;

        typedef typename Pointer<T, _Deleter>::const_t     const_t;
        typedef typename Pointer<T, _Deleter>::const_ptr_t const_ptr_t;
        typedef typename Pointer<T, _Deleter>::const_ref_t const_ref_t;

        typedef typename Pointer<T, _Deleter>::deleter deleter;
        typedef SharedPointer<T, _Deleter>             pointer_t;
    protected:
        uint_t *_F_useCount;
    public:
        SharedPointer(ptr_t ptr = nullptr);
        SharedPointer(const pointer_t & cpy);
        virtual ~SharedPointer() override;

        virtual void reset(ptr_t ptr);
        virtual void swap(SharedPointer<T, _Deleter> &sp);
        virtual uint_t use_count() const final;

        virtual SharedPointer<T, _Deleter>& operator =(ptr_t ptr) override;
        virtual SharedPointer<T, _Deleter>& operator =(const UniquePointer<T, _Deleter>& ptr);
        virtual SharedPointer<T, _Deleter>& operator =(const SharedPointer<T, _Deleter>& ptr);
    };

    template < typename T, typename _Deleter = Delete<T> >
    class WeakPointer : public Pointer<T, _Deleter>
    {
    public:
        typedef typename Pointer<T, _Deleter>::value_t   value_t;
        typedef typename Pointer<T, _Deleter>::ref_t     ref_t;
        typedef typename Pointer<T, _Deleter>::rvalue_t  rvalue_t;
        typedef typename Pointer<T, _Deleter>::ptr_t     ptr_t;

        typedef typename Pointer<T, _Deleter>::const_t     const_t;
        typedef typename Pointer<T, _Deleter>::const_ptr_t const_ptr_t;
        typedef typename Pointer<T, _Deleter>::const_ref_t const_ref_t;

        typedef typename Pointer<T, _Deleter>::deleter deleter;
        typedef WeakPointer<T, _Deleter>             pointer_t;
    protected:
        uint_t* _F_useCount;
    public:
        WeakPointer(ptr_t ptr = nullptr);
        WeakPointer(const pointer_t & cpy);
        WeakPointer(const SharedPointer<T, _Deleter>& sp);
        virtual ~WeakPointer() override;

        virtual void reset(ptr_t ptr);
        virtual void reset(const WeakPointer<T, _Deleter>& wp);
        virtual void reset(const SharedPointer<T, _Deleter>& sp);
        virtual void swap(WeakPointer<T, _Deleter> &sp);
        virtual uint_t use_count() const final;

        virtual WeakPointer<T, _Deleter>& operator =(ptr_t ptr) override;
        virtual WeakPointer<T, _Deleter>& operator =(const WeakPointer<T, _Deleter>& wp);
        virtual WeakPointer<T, _Deleter>& operator =(const SharedPointer<T, _Deleter>& sp);
    };

    template<typename T, typename _Deleter>
    Pointer<T, _Deleter>::Pointer(ptr_t ptr): _F_ptr(ptr)
    {/* ... */}

    template<typename T, typename _Deleter>
    typename Pointer<T, _Deleter>::ptr_t Pointer<T, _Deleter>::pointer() const
    {
        return _F_ptr;
    }

    template<typename T, typename _Deleter>
    inline typename Pointer<T, _Deleter>::ref_t Pointer<T, _Deleter>::operator*()
    {
        return *_F_ptr;
    }

    template<typename T, typename _Deleter>
    inline typename Pointer<T, _Deleter>::ptr_t Pointer<T, _Deleter>::operator->()
    {
        return _F_ptr;
    }

    template<typename T, typename _Deleter>
    inline typename Pointer<T, _Deleter>::ref_t Pointer<T, _Deleter>::operator[](size_t __index)
    {
        return _F_ptr[__index];
    }

    template<typename T, typename _Deleter>
    bool Pointer<T, _Deleter>::operator==(const_ptr_t ptr) const
    {
        return _F_ptr == ptr;
    }

    template<typename T, typename _Deleter>
    bool Pointer<T, _Deleter>::operator<=(const_ptr_t ptr) const
    {
        return _F_ptr <= ptr;
    }

    template<typename T, typename _Deleter>
    bool Pointer<T, _Deleter>::operator>=(const_ptr_t ptr) const
    {
        return _F_ptr >= ptr;
    }

    template<typename T, typename _Deleter>
    bool Pointer<T, _Deleter>::operator >(const_ptr_t ptr) const
    {
        return _F_ptr > ptr;
    }

    template<typename T, typename _Deleter>
    bool Pointer<T, _Deleter>::operator <(const_ptr_t ptr) const
    {
        return _F_ptr < ptr;
    }

    template<typename T, typename _Deleter>
    inline Pointer<T, _Deleter>::operator bool() const
    {
        return _F_ptr != nullptr;
    }

    template<typename T, typename _Deleter>
    inline Pointer<T, _Deleter>::operator ptr_t() const
    {
        return _F_ptr;
    }

    template<typename T, typename _Deleter>
    hash_t Pointer<T, _Deleter>::hashCode() const
    {
        return _F_ptr;
    }

    template<typename T, typename _Deleter>
    UniquePointer<T, _Deleter>::UniquePointer(ptr_t ptr): Pointer<T, _Deleter>(ptr)
    {
        /* ... */
    }

    template<typename T, typename _Deleter>
    UniquePointer<T, _Deleter>::UniquePointer(pointer_t& ptr): Pointer<T, _Deleter>(ptr.release())
    {
        /* ... */
    }

    template<typename T, typename _Deleter>
    UniquePointer<T, _Deleter>::~UniquePointer()
    {
        if (this->_F_ptr)
        {
            deleter::free(this->_F_ptr);
        }
    }

    template<typename T, typename _Deleter>
    void UniquePointer<T, _Deleter>::reset(ptr_t ptr)
    {
        if (this->_F_ptr)
        {
            deleter::free(this->_F_ptr);
        }

        this->_F_ptr = ptr;
    }

    template<typename T, typename _Deleter>
    typename UniquePointer<T, _Deleter>::ptr_t UniquePointer<T, _Deleter>::release()
    {
        ptr_t ptr = this->_F_ptr;
        this->_F_ptr = nullptr;
        return ptr;
    }

    template<typename T, typename _Deleter>
    void UniquePointer<T, _Deleter>::swap(UniquePointer<T, _Deleter> &sp)
    {
        ptr_t __ptr = this->_F_ptr;
        this->_F_ptr = sp._F_ptr;
        sp._F_ptr = __ptr;
    }

    template<typename T, typename _Deleter>
    UniquePointer<T, _Deleter>& UniquePointer<T, _Deleter>::operator =(ptr_t ptr)
    {
        reset(ptr);
        return *this;
    }

    template<typename T, typename _Deleter>
    UniquePointer<T, _Deleter>& UniquePointer<T, _Deleter>::operator =(UniquePointer<T, _Deleter>& up)
    {
        reset(up.release());
        return *this;
    }

    template<typename T, typename _Deleter>
    SharedPointer<T, _Deleter>::SharedPointer(ptr_t ptr):
        Pointer<T, _Deleter>(ptr), _F_useCount(ptr ? new uint_t(1u) : nullptr)
    {
        /* ... */
    }

    template<typename T, typename _Deleter>
    SharedPointer<T, _Deleter>::SharedPointer(const pointer_t& cpy):
        Pointer<T, _Deleter>(cpy._F_ptr), _F_useCount(cpy._F_useCount)
    {
        (*_F_useCount)++;
    }

    template<typename T, typename _Deleter>
    SharedPointer<T, _Deleter>::~SharedPointer()
    {
        (*_F_useCount)--;
        if (*_F_useCount == 0)
        {
            delete _F_useCount;
            deleter::free(_F_useCount);
        }
    }

    template<typename T, typename _Deleter>
    void SharedPointer<T, _Deleter>::reset(ptr_t ptr)
    {
        if (this->_F_ptr != ptr && this->_F_ptr)
        {
            (*_F_useCount)--;
            if (*_F_useCount == 0)
            {
                deleter::free(this->_F_ptr);
                delete _F_useCount;
            }
        }

        this->_F_ptr = ptr;
        if (ptr)
        {
            _F_useCount = new uint_t(1u);
        }
    }

    template<typename T, typename _Deleter>
    void SharedPointer<T, _Deleter>::swap(SharedPointer<T, _Deleter> &sp)
    {
        ptr_t   __ptr = sp.pointer();
        uint_t* __uc  = sp._F_useCount;

        sp._F_ptr      = this->_F_ptr;
        sp._F_useCount = _F_useCount;
        this->_F_ptr        = __ptr;
        this->_F_useCount   = __uc;
    }

    template<typename T, typename _Deleter>
    uint_t SharedPointer<T, _Deleter>::use_count() const
    {
        return *_F_useCount;
    }

    template<typename T, typename _Deleter>
    SharedPointer<T, _Deleter>& SharedPointer<T, _Deleter>::operator =(ptr_t ptr)
    {
        reset(ptr);
        return *this;
    }

    template<typename T, typename _Deleter>
    SharedPointer<T, _Deleter>& SharedPointer<T, _Deleter>::operator=(const SharedPointer<T, _Deleter> &ptr)
    {
        if (this->_F_ptr != ptr && this->_F_ptr)
        {
            (*_F_useCount)--;
            if (*_F_useCount == 0)
            {
                deleter::free(this->_F_ptr);
                delete _F_useCount;
            }
        }

        this->_F_ptr = ptr.pointer();
        this->_F_useCount = ptr._F_useCount;
        if (this->_F_ptr)
        {
            (*_F_useCount)++;
        }

        return *this;
    }

    template<typename T, typename _Deleter>
    SharedPointer<T, _Deleter>& SharedPointer<T, _Deleter>::operator=(const UniquePointer<T, _Deleter> &ptr)
    {
        reset(ptr.release());
        return *this;
    }

    template<typename T, typename _Deleter>
    WeakPointer<T, _Deleter>::WeakPointer(ptr_t ptr): Pointer<T, _Deleter>(ptr), _F_useCount(nullptr)
    { /* ... */ }

    template<typename T, typename _Deleter>
    WeakPointer<T, _Deleter>::WeakPointer(const pointer_t& cpy):
        Pointer<T, _Deleter>(cpy._F_ptr), _F_useCount(cpy._F_useCount)
    { /* ... */ }

    template<typename T, typename _Deleter>
    WeakPointer<T, _Deleter>::WeakPointer(const SharedPointer<T, _Deleter>& sp):
        Pointer<T, _Deleter>(sp._F_ptr), _F_useCount(sp._F_useCount)
    { /* ... */ }

    template<typename T, typename _Deleter>
    WeakPointer<T, _Deleter>::~WeakPointer()
    {
        /* do nothing */
    }

    template<typename T, typename _Deleter>
    void WeakPointer<T, _Deleter>::reset(ptr_t ptr)
    {
        _F_useCount = nullptr;
        this->_F_ptr = ptr;
    }

    template<typename T, typename _Deleter>
    void WeakPointer<T, _Deleter>::reset(const WeakPointer<T, _Deleter> &wp)
    {
        _F_useCount = wp._F_useCount;
        this->_F_ptr = wp._F_ptr;
    }

    template<typename T, typename _Deleter>
    void WeakPointer<T, _Deleter>::reset(const SharedPointer<T, _Deleter> &sp)
    {
        _F_useCount = sp._F_useCount;
        this->_F_ptr = sp._F_ptr;
    }

    template<typename T, typename _Deleter>
    void WeakPointer<T, _Deleter>::swap(WeakPointer<T, _Deleter> &sp)
    {
        uint_t * tmp_usecount = sp._F_useCount;
        ptr_t    tmp_ptr      = sp._F_ptr;
        sp._F_useCount = _F_useCount;
        sp._F_ptr      = this->_F_ptr;
        this->_F_useCount = tmp_usecount;
        this->_F_ptr      = tmp_ptr;
    }

    template<typename T, typename _Deleter>
    uint_t WeakPointer<T, _Deleter>::use_count() const
    {
        if (_F_useCount)
            return *_F_useCount;
        else
            return 1u;
    }

    template<typename T, typename _Deleter>
    WeakPointer<T, _Deleter>& WeakPointer<T, _Deleter>::operator=(ptr_t ptr)
    {
        reset(ptr);
        return *this;
    }

    template<typename T, typename _Deleter>
    WeakPointer<T, _Deleter>& WeakPointer<T, _Deleter>::operator=(const WeakPointer<T, _Deleter>& wp)
    {
        reset(wp);
        return *this;
    }

    template<typename T, typename _Deleter>
    WeakPointer<T, _Deleter>& WeakPointer<T, _Deleter>::operator=(const SharedPointer<T, _Deleter> &sp)
    {
        reset(sp);
        return *this;
    }
}

#endif //CPP_POINTER_HPP
