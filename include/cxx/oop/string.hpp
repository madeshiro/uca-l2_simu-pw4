#ifndef CPP_STRING_HPP
#define CPP_STRING_HPP
#include "cxx/oop/object.h"
#include "defines.h"
#include "cxx/oop/type_traits.hpp"

namespace UCA_L2INFO_PW4
{
    template < typename _CharT, typename _Traits >
    class __String__ : public Object
    {
        typedef _Traits traits_type;

        typedef typename traits_type::value_t   char_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     str_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_str_t;

        typedef __String__<_CharT, _Traits> string_t;
    protected:
        str_t   _F_charseq;
        uint_t  _F_length;
    public:
        __String__();
        __String__(char_t c);
        __String__(const_str_t str);
        __String__(const string_t& str);

        virtual ~__String__();

        /* GETTER */
        uint_t length() const;
        const_str_t getCharSequence() const;


        /* CONVERTER */
        virtual char     * toUTF8() const;
        virtual char16_t * toUTF16() const;
        virtual char32_t * toUTF32() const;

        int         toInteger() const;
        long_t      toLong() const;
        double      toDouble() const;
        llong_t     toLLong() const;
        ldouble_t   toLDouble() const;

        virtual operator int() const;
        virtual operator long_t() const;
        virtual operator double() const;
        virtual operator llong_t() const;
        virtual operator ldouble_t() const;

        virtual operator str_t() const;
        virtual operator const_str_t() const;

        /* OPERATOR */

        /* OBJECT */
        virtual hash_t hashCode() override;
        virtual String toString() override;
    };

    using String    = __String__<char>;
    using WString   = __String__<wchar_t>;
}

#include "../../../src/cxx/oop/string.c++"
#endif //CPP_STRING_HPP
