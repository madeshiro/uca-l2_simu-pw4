#ifndef CPP_POINTER_HPP
#define CPP_POINTER_HPP
#include "alloc.hpp"
#include "../../defines.h"

namespace UCA_L2INFO_PW4
{
    template < typename T, typename _Deleter = Delete<T> >
    class Pointer
    {
    protected:
        typedef _Deleter deleter;
        typedef typename deleter::value_t   value_t;
        typedef typename deleter::ref_t     ref_t;
        typedef typename deleter::rvalue_t  rvalue_t;
        typedef typename deleter::ptr_t     ptr_t;

        typedef typename deleter::const_t     const_t;
        typedef typename deleter::const_ptr_t const_ptr_t;
        typedef typename deleter::const_ref_t const_ref_t;

        typedef Pointer<T, _Deleter> pointer_t;

        ptr_t origin, value;
        Pointer(ptr_t ptr): origin(ptr), value(ptr) {/*...*/}
        virtual ~Pointer() { /* do nothing */ }
    public:
        virtual ptr_t pointer() { return value; }

        virtual ref_t operator *();
        virtual ptr_t operator ->();
        virtual ref_t operator [](size_t __index);

        virtual pointer_t & operator ++();
        virtual pointer_t & operator --();

        virtual pointer_t operator +(size_t) const;
        virtual pointer_t operator -(size_t) const;

        virtual pointer_t & operator +=(size_t);
        virtual pointer_t & operator -=(size_t);

        virtual operator bool() const;
        virtual operator ptr_t() const;
    };

    template < typename T, typename _Deleter = Delete<T> >
    class SharedPointer : Pointer<T, _Deleter>
    {
    protected:
        typedef _Deleter deleter;

        typedef typename Pointer<T, _Deleter>::value_t   value_t;
        typedef typename Pointer<T, _Deleter>::ref_t     ref_t;
        typedef typename Pointer<T, _Deleter>::rvalue_t  rvalue_t;
        typedef typename Pointer<T, _Deleter>::ptr_t     ptr_t;

        typedef typename Pointer<T, _Deleter>::const_t     const_t;
        typedef typename Pointer<T, _Deleter>::const_ptr_t const_ptr_t;
        typedef typename Pointer<T, _Deleter>::const_ref_t const_ref_t;

        typedef SharedPointer<T, _Deleter> pointer_t;

        uint_t _F_useCount;
    public:
        SharedPointer(ptr_t ptr);
        SharedPointer(const pointer_t & cpy);
        virtual ~SharedPointer() override;

        virtual uint_t use_count() const final;
    };
}


#endif //CPP_POINTER_HPP
