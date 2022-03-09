#ifndef CPP_STRING_HPP
#define CPP_STRING_HPP
#include "defines.h"
#include "cxx/oop/object.h"
#include "cxx/oop/alloc.hpp"

namespace UCA_L2INFO_PW4
{
    template < typename _CharT, typename _Traits = Traits<_CharT>, typename _Alloc = Alloc<_CharT> >
    class CharSequence : public Object
    {
    protected:
        typedef _Traits                         traits_type;
        typedef typename traits_type::value_t   char_t;
        typedef typename traits_type::ptr_t     str_t;

        typedef CharSequence<_CharT, _Traits, _Alloc> charsequence_t;
    public:
        virtual char_t charAt(uint_t index) const = 0;
        virtual uint_t length() const = 0;
        virtual str_t  subSequence(uint_t offset, uint_t len) const = 0;
    };

    template < typename _CharT, typename _Traits, typename _Alloc>
    class __String__ : public CharSequence<_CharT, _Traits, _Alloc>
    {
        typedef _Traits                     traits_type;
        typedef _Alloc                      allocator;
        typedef Delete<_CharT[], _Traits>   deleter;

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

        void __delete();
    public:
        __String__();
        __String__(char_t c);
        __String__(const_str_t str);
        __String__(const_str_t str, uint_t size);
        __String__(const string_t& str);

        virtual ~__String__();

        template < typename ...T >
        string_t concat(T... args) const;

        template < typename T >
        string_t add(T arg) const;

        string_t& append(char_t c);
        string_t& append(const_str_t str);
        string_t& append(const string_t& str);

        string_t& remove(char_t c);
        string_t& remove(const_str_t str);
        string_t& remove(const string_t& str);

        string_t& removeOnce(char_t c);
        string_t& removeOnce(const_str_t str);
        string_t& removeOnce(const string_t& str);

        string_t replace(char_t __old, char_t __new) const;
        string_t replace(const_str_t __old, const_str_t __new) const;
        string_t replace(const string_t& __old, const string_t& __new) const;

        string_t replaceFirst(char_t __old, char_t __new) const;
        string_t replaceFirst(const_str_t __old, const_str_t __new) const;
        string_t replaceFirst(const string_t& __old, const string_t& __new) const;

        /* GETTER */
        uint_t length() const override;
        char_t charAt(uint_t index) const override;
        const_str_t getCharSequence() const;

        str_t subSequence(uint_t offset, uint_t len) const override;

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


        string_t & operator =(char_t c);
        string_t & operator =(const_str_t str);
        string_t & operator =(const string_t & str);

        /* OBJECT */
        virtual hash_t hashCode() override;
        virtual String toString() override;


        static string_t toString(char);
        static string_t toString(int);
        static string_t toString(long);
        static string_t toString(float);
        static string_t toString(double);
        static string_t toString(const_str_t);
        static string_t toString(const Object&);

        static string_t toHexString(unsigned long);
        static string_t toScientificString(double);
    };

    template < typename _CharT, typename _Traits = Traits<_CharT>, typename _Alloc = Alloc<_CharT> >
    class __StringBuilder__
    {
    public:
    };

    using String    = __String__<char>;
    using WString   = __String__<wchar_t>;

    using StringBuilder  = __StringBuilder__<char>;
    using WStringBuilder = __StringBuilder__<wchar_t>;

#ifndef OOP_IMPL_TEMPLATE_STRING
    extern template class __String__<char>;
    extern template class __String__<wchar_t>;
    extern template class __StringBuilder__<char>;
    extern template class __StringBuilder__<wchar_t>;
#endif //OOP_IMPL_TEMPLATE_STRING
}

#include "../../../src/cxx/oop/string.c++"
#endif //CPP_STRING_HPP
