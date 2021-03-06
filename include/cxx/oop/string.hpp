/*
 * UCA-L2 simulation "practical work #4" : a realistic simulation of rabbit population growth
 * Copyright (C) 2022 -- Rin Baudelet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef CPP_STRING_HPP
#define CPP_STRING_HPP
#include "defines.h"
#include "cxx/oop/object.h"
#include "cxx/oop/alloc.hpp"
#include "cxx/oop/container.hpp"

namespace UCA_L2INFO_PW4
{
    template < typename _CharT, typename _Traits = Traits<_CharT>, typename _Alloc = Alloc<_CharT> >
    class CharSequence : public Iterable<_CharT, _Traits>
    {
    protected:
        typedef _Traits traits_type;
        typedef _Alloc                      allocator;
        typedef Delete<_CharT[], _Traits>   deleter;

        typedef typename traits_type::value_t   char_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     str_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_str_t;
    public:
        virtual char_t charAt(uint_t index) const = 0;
        virtual uint_t length() const = 0;
        virtual str_t  subSequence(uint_t offset, uint_t len) const = 0;
    };

    template <typename _CharT, typename _Traits, typename _Alloc>
    struct Traits< __String__<_CharT, _Traits, _Alloc> >
    {
        typedef __String__<_CharT, _Traits, _Alloc>   value_t;
        typedef __String__<_CharT, _Traits, _Alloc>&  ref_t;
        typedef __String__<_CharT, _Traits, _Alloc>&& rvalue_t;
        typedef __String__<_CharT, _Traits, _Alloc>*  ptr_t;

        typedef const __String__<_CharT, _Traits, _Alloc>     const_t;
        typedef const __String__<_CharT, _Traits, _Alloc>*    const_ptr_t;
        typedef const __String__<_CharT, _Traits, _Alloc>&    const_ref_t;

        typedef ulong_t     size_t;

        static hash_t hash_code(const_ref_t obj);
        static ptr_t  copy(const_ptr_t ptr, size_t __size);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
    };

    template <typename _CharT, typename _Traits, typename _Alloc>
    struct Alloc< __String__<_CharT, _Traits, _Alloc> >
    {
        typedef Traits< __String__<_CharT, _Traits, _Alloc> > traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static ptr_t alloc();
        static ptr_t alloc(size_t nmemb);
        static ptr_t calloc(size_t nmemb);

        static size_t sizeOf();
    };

    template <typename _CharT, typename _Traits, typename _Alloc>
    struct Alloc< __String__<_CharT, _Traits, _Alloc>[] >
    {
        typedef Traits< __String__<_CharT, _Traits, _Alloc> > traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static ptr_t alloc(size_t nmemb);
        static ptr_t calloc(size_t nmemb);

        static size_t sizeOf();
    };

    template <typename _CharT, typename _Traits, typename _Alloc>
    struct Delete< __String__<_CharT, _Traits, _Alloc> >
    {
        typedef Traits< __String__<_CharT, _Traits, _Alloc> > traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static void free(ptr_t ptr);
    };


    template <typename _CharT, typename _Traits, typename _Alloc>
    struct Delete< __String__<_CharT, _Traits, _Alloc>[] >
    {
        typedef Traits< __String__<_CharT, _Traits, _Alloc>[] > traits_type;

        typedef typename traits_type::value_t   value_t;
        typedef typename traits_type::ref_t     ref_t;
        typedef typename traits_type::ptr_t     ptr_t;
        typedef typename traits_type::rvalue_t  rvalue_t;

        typedef typename traits_type::const_t       const_t;
        typedef typename traits_type::const_ref_t   const_ref_t;
        typedef typename traits_type::const_ptr_t   const_ptr_t;

        typedef typename traits_type::size_t        size_t;

        static void free(ptr_t ptr);
    };

    template < typename _CharT, typename _Traits, typename _Alloc>
    class __String__ : public CharSequence<_CharT, _Traits, _Alloc>,
                              Comparable< __String__<_CharT, _Traits, _Alloc> >
    {
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::traits_type traits_type;
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::allocator   allocator;
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::deleter     deleter;

        typedef typename CharSequence<_CharT, _Traits, _Alloc>::char_t   char_t;
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::ref_t     ref_t;
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::ptr_t     str_t;
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::rvalue_t  rvalue_t;

        typedef typename CharSequence<_CharT, _Traits, _Alloc>::const_t       const_t;
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::const_ref_t   const_ref_t;
        typedef typename CharSequence<_CharT, _Traits, _Alloc>::const_ptr_t   const_str_t;

        typedef __String__<_CharT, _Traits> string_t;
    protected:
        str_t   _F_charseq;
        uint_t  _F_length;
        uint_t  _F_capacity;

        void __delete();
        bool __grow(uint_t capacity);
        void __set(str_t charseq, uint_t len, uint_t capacity);

        __String__(str_t str, uint_t len, uint_t capacity):
            _F_charseq(str), _F_length(len), _F_capacity(capacity) {/*...*/}
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

        template < typename ...T >
        string_t format(T... args) const;

        string_t& append(char_t c);
        string_t& append(const_str_t str);
        string_t& append(const string_t& str);

        uint_t capacity() const;

        char_t charAt(uint_t index) const override;

        int compareTo(const __String__<_CharT, _Traits, _Alloc>& str) const override;

        bool contains(char_t c) const;
        bool contains(const_str_t str) const;
        bool contains(const string_t& str) const;

        bool beginsWith(char_t c) const;
        bool beginsWith(const_str_t str) const;
        bool beginsWith(const string_t& str) const;

        bool isEmpty() const;

        bool endsWith(char_t c) const;
        bool endsWith(const_str_t str) const;
        bool endsWith(const string_t& str) const;

        virtual bool equals(const Object& object) const override;

        int find(char_t c) const;
        int find(const_str_t str) const;
        int find(const string_t& str) const;

        ArrayList<uint_t> findAll(char_t c) const;
        ArrayList<uint_t> findAll(const_str_t str) const;
        ArrayList<uint_t> findAll(const string_t& str) const;

        str_t begin() const override;
        str_t end() const override;

        uint_t length() const override;

        string_t& prepend(char_t c);
        string_t& prepend(const_str_t str);
        string_t& prepend(const string_t& str);

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

        ArrayList<string_t> split(char_t separator) const;
        ArrayList<string_t> split(const_str_t separator) const;
        ArrayList<string_t> split(const string_t& separator) const;

        str_t subSequence(uint_t offset, uint_t len) const override;

        /* GETTER */

        const_str_t getCharSequence() const;

        /* CONVERTER */
        virtual char     * toUTF8() const  {return nullptr;}
        virtual char16_t * toUTF16() const {return nullptr;}
        virtual char32_t * toUTF32() const {return nullptr;}

        virtual string_t toLowerCase() const;
        virtual string_t toUpperCase() const;

        int         toInteger() const;
        long_t      toLong() const;
        double      toDouble() const;

        virtual operator int() const;
        virtual operator long_t() const;
        virtual operator float() const;
        virtual operator double() const;

        virtual operator const_str_t() const;

        /* OPERATOR */

        string_t & operator =(char_t c);
        string_t & operator =(const_str_t str);
        string_t & operator =(const string_t & str);

        string_t   operator +(char_t c) const;
        string_t   operator +(const_str_t str) const;
        string_t   operator +(const string_t & str) const;

        string_t & operator +=(char_t c);
        string_t & operator +=(const_str_t str);
        string_t & operator +=(const string_t & str);

        bool operator ==(const string_t& str) const override;

        char_t operator[](uint_t index) const;

        /* OBJECT */

        virtual hash_t hashCode() const override;
        virtual String toString() const override;

        /* STATIC METHODS */

        static string_t ToString(char_t);
        static string_t ToString(bool);
        static string_t ToString(int);
        static string_t ToString(long);
        static string_t ToString(float);
        static string_t ToString(double);
        static string_t ToString(const_str_t);
        static string_t ToString(const Object&);
        static string_t ToString(const string_t &str);

        static string_t ToString(hash_t);
        static string_t toHexString(ullong_t);
    };

    using String    = __String__<char>;
//     using WString   = __String__<wchar_t>;

#ifndef OOP_IMPL_TEMPLATE_STRING
    extern template class __String__<char>;
    extern template class __String__<wchar_t>;
#endif //OOP_IMPL_TEMPLATE_STRING

    template < typename _CharT, typename _Traits, typename _Alloc >
    __String__<_CharT, _Traits, _Alloc>::__String__():
            _F_charseq(0), _F_length(0), _F_capacity(0)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits, typename _Alloc >
    __String__<_CharT, _Traits, _Alloc>::__String__(char_t c):
            _F_charseq(traits_type::copy(&c, 1u)), _F_length(1), _F_capacity(2)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits, typename _Alloc >
    __String__<_CharT, _Traits, _Alloc>::__String__(const_str_t str):
            _F_charseq(traits_type::copy(str)), _F_length(traits_type::len(str)),
            _F_capacity(_F_length+1)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits, typename _Alloc >
    __String__<_CharT, _Traits, _Alloc>::__String__(const_str_t str, uint_t size):
            _F_charseq(traits_type::copy(str, size)), _F_length(size), _F_capacity(size+1)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits, typename _Alloc >
    __String__<_CharT, _Traits, _Alloc>::__String__(const string_t &str):
            _F_charseq(traits_type::copy(str._F_charseq, str._F_length)),
            _F_length(str._F_length), _F_capacity(str._F_length+1)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits, typename _Alloc >
    __String__<_CharT, _Traits, _Alloc>::~__String__<_CharT, _Traits, _Alloc>()
    {
        __delete();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    void __String__<_CharT, _Traits, _Alloc>::__delete()
    {
        if (_F_charseq)
        {
            deleter::free(_F_charseq);
        }
        _F_length   = 0;
        _F_capacity = 0;
        _F_charseq  = nullptr;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::__grow(uint_t capacity)
    {
        str_t cpy = Alloc<char_t>::alloc(_F_capacity+capacity);
        if (cpy)
        {
            uint_t i;
            for (i = 0; i < _F_length; i++)
                cpy[i] = _F_charseq[i];
            cpy[i] = (char_t) '\0';

            _F_capacity += capacity;
            if (_F_charseq) deleter::free(_F_charseq);
            _F_charseq = cpy;
            return true;
        }
        else return false;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    void __String__<_CharT, _Traits, _Alloc>::__set(str_t charseq, uint_t len, uint_t capacity)
    {
        if (_F_charseq)
        {
            deleter::free(_F_charseq);
        }

        _F_charseq  = charseq;
        _F_length   = len;
        _F_capacity = capacity;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename... T>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::concat(T... args) const
    {
        string_t str(*this), elems[sizeof...(T)] = {ToString(args)...};

        for (string_t elem : elems)
        {
            str.append(elem);
        }

        return str;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename T>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::add(T arg) const
    {
        return string_t(*this).append(string_t::ToString(arg));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename... T>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::format(T ...args) const
    {
        string_t str(*this), elems[sizeof...(T)] = {ToString(args)...};

        for (uint_t i = 0; i < sizeof...(T); i++)
        {
            string_t _f('{');
            _f.append(ToString((int)i));
            _f.append('}');
            str = str.replace(_f, elems[i]);
        }

        return str;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::append(char_t c)
    {
        return this->append(string_t(c));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::append(const_str_t str)
    {
        return this->append(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::append(const string_t& str)
    {
        if (_F_capacity <= length()+str.length())
        {
            if (!__grow(1+((length()+str.length())-_F_capacity)))
            {
                return *this;
            }
        }

        for (uint_t i = 0, j = length(); i < str.length(); i++, j++)
        {
            _F_charseq[j] = str[i];
        }

        _F_length+=str.length();
        _F_charseq[_F_length] = (char_t) '\0';
        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    uint_t __String__<_CharT, _Traits, _Alloc>::capacity() const
    {
        return _F_capacity;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::char_t
    __String__<_CharT, _Traits, _Alloc>::charAt(uint_t index) const
    {
        return _F_charseq[index];
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    int __String__<_CharT, _Traits, _Alloc>::compareTo(const __String__<_CharT, _Traits, _Alloc>&str) const
    {
        string_t __this = toLowerCase();
        string_t __str  = str.toLowerCase();

        uint_t minLen = __str.length() < __this.length() ? __str.length() : __this.length();
        if (__this.equals(__str))
            return 0;

        for (uint_t i = 0; i <minLen; i++)
        {
            if (__this[i] < __str[i])
            {
                return -1;
            }
            else if (__this[i] > __str[i])
            {
                return 1;
            }
        }

        return __this.length() < __str.length() ? -1 : 1;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::contains(char_t c) const
    {
        return find(c) != -1;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::contains(const_str_t str) const
    {
        return find(str) != -1;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::contains(const string_t& str) const
    {
        return find(str) != -1;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::beginsWith(char_t c) const
    {
        return _F_charseq[0] == c;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::beginsWith(const_str_t str) const
    {
        return beginsWith(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::beginsWith(const string_t &str) const
    {
        if (str.length() <= length())
        {
            for (uint_t i = 0; i < str.length(); i++)
            {
                if (str[i] != _F_charseq[i])
                    return false;
            }

            return true;
        }
        else return false;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::isEmpty() const
    {
        return _F_length == 0;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::endsWith(char_t c) const
    {
        return _F_charseq[length()-1] == c;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::endsWith(const_str_t str) const
    {
        return endsWith(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::endsWith(const string_t& str) const
    {
        if (str.length() <= length())
        {
            for (uint_t i = str.length()-1, j = length()-1; i <= 0; i--, j--)
            {
                if (str[i] != _F_charseq[j])
                    return false;
            }
            return true;
        }
        else return false;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::equals(const Object &object) const
    {
        return hashCode() == object.hashCode();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    int __String__<_CharT, _Traits, _Alloc>::find(char_t c) const
    {
        for (uint_t i = 0; i < length(); i++)
        {
            if (_F_charseq[i] == c)
                return i;
        }
        return -1;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    int __String__<_CharT, _Traits, _Alloc>::find(const_str_t str) const
    {
        return find(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    int __String__<_CharT, _Traits, _Alloc>::find(const string_t &str) const
    {
        if (str.length() <= length())
        {
            for (uint_t i = 0; i < length(); i++)
            {
                if (_F_charseq[i] == str[0])
                {
                    if (str.length() > length()-i)
                        break;

                    uint_t j;
                    for (j = 1; j < str.length(); j++)
                    {
                        if (_F_charseq[i+j] != str[j])
                            break;
                    }

                    if (j == str.length())
                        return i;
                }
            }
        }

        return -1;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    ArrayList<uint_t> __String__<_CharT, _Traits, _Alloc>::findAll(char_t c) const
    {
        ArrayList<uint_t> finds;

        for (uint_t i = 0; i < length(); i++)
        {
            if (_F_charseq[i] == c)
            {
                finds.add(i);
            }
        }

        return finds;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    ArrayList<uint_t> __String__<_CharT, _Traits, _Alloc>::findAll(const_str_t str) const
    {
        return findAll(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    ArrayList<uint_t> __String__<_CharT, _Traits, _Alloc>::findAll(const string_t &str) const
    {
        ArrayList<uint_t> finds;

        if (str.length() <= length())
        {
            for (uint_t i = 0; i < length(); i++)
            {
                if (_F_charseq[i] == str[0])
                {
                    if (str.length() > length()-i)
                        break;

                    uint_t j;
                    for (j = 1; j < str.length(); j++)
                    {
                        if (_F_charseq[i+j] != str[j])
                            break;
                    }

                    if (j == str.length())
                    {
                        finds.add(i);
                        i += j;
                    }
                }
            }
        }

        return finds;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::str_t
    __String__<_CharT, _Traits, _Alloc>::begin() const
    {
        return _F_charseq;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::str_t
    __String__<_CharT, _Traits, _Alloc>::end() const
    {
        return &_F_charseq[_F_length];
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    uint_t __String__<_CharT, _Traits, _Alloc>::length() const
    {
        return _F_length;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::prepend(char_t c)
    {
        return this->prepend(string_t(c));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::prepend(const_str_t str)
    {
        return this->prepend(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::prepend(const string_t& str)
    {
        uint_t oldLength = _F_length;
        if (_F_capacity <= length()+str.length())
        {
            if (!__grow(1+(_F_capacity - (length()+str.length()))))
            {
                return *this;
            }
        }

        for (int i = _F_length, j=oldLength-1; j >= 0; i--, j--)
        {
            _F_charseq[i] = _F_charseq[j];
        }
        for (int i = 0; i < (int) str.length(); i++)
        {
            _F_charseq[i] = str[i];
        }

        _F_length+=str.length();
        _F_charseq[_F_length] = (char_t) '\0';

        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t&
    __String__<_CharT, _Traits, _Alloc>::remove(char_t c)
    {
        ArrayList<uint_t> finds = findAll(c);

        if (finds.size() > 0)
        {
            uint_t newLen  = _F_length - finds.size();
            uint_t newCap  = newLen + 1;
            str_t newStr   = allocator::alloc(newCap);
            newStr[newLen] = (char_t) 0;

            for (uint_t i = 0, j = 0; i < _F_length; i++)
            {
                if (!finds.contains(i))
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                }
            }

            __set(newStr, newLen, newCap);
        }

        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t&
    __String__<_CharT, _Traits, _Alloc>::remove(const_str_t str)
    {
        return remove(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t&
    __String__<_CharT, _Traits, _Alloc>::remove(const string_t& str)
    {
        ArrayList<uint_t> finds = findAll(str);

        if (finds.size() > 0)
        {
            uint_t newLen  = _F_length - (str.length()*finds.size());
            uint_t newCap  = newLen + 1;
            str_t newStr   = allocator::alloc(newCap);
            newStr[newLen] = (char_t) 0;

            for (uint_t i = 0, j = 0; i < _F_length; i++)
            {
                if (!finds.contains(i))
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                }
                else
                {
                    i+=str.length();
                }
            }

            __set(newStr, newLen, newCap);
        }

        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::removeOnce(char_t c)
    {
        int position = find(c);

        if (position != -1)
        {
            uint_t newLen   = _F_length - 1;
            uint_t newCap   = _F_capacity - 1;
            str_t newStr    = allocator::alloc(newCap);
            newStr[newLen]  = (char_t) 0;

            for (uint_t i = 0, j = 0; i < _F_length; i++)
            {
                if (i != (uint_t) position)
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                }
            }

            __set(newStr, newLen, newCap);
        }

        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::removeOnce(const_str_t str)
    {
        return removeOnce(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::removeOnce(const string_t& str)
    {
        int position = find(str);

        if (position != -1)
        {
            uint_t newLen   = _F_length - str.length();
            uint_t newCap   = _F_capacity - str.length();
            str_t newStr    = allocator::alloc(newCap);
            newStr[newLen]  = (char_t) 0;

            for (uint_t i = 0, j = 0; i < _F_length; i++)
            {
                if (i != (uint_t) position)
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                } else i+=str.length();
            }

            __set(newStr, newLen, newCap);
        }

        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::replace(char_t __old, char_t __new) const
    {
        string_t str(*this);
        ArrayList<uint_t> finds = findAll(__old);

        for (uint_t i : finds)
        {
            str._F_charseq[i] = __new;
        }

        return str;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::replace(const_str_t __old, const_str_t __new) const
    {
        return replace(string_t(__old), string_t(__new));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::replace(const string_t& __old, const string_t& __new) const
    {
        ArrayList<uint_t> finds = findAll(__old);

        if (finds.size() > 0)
        {
            int diffs       = (int) __new.length() - __old.length();
            uint_t newLen   = (uint_t) ((int) finds.size()*(_F_length + diffs));
            uint_t newCap   = newLen + 1;

            if (newLen == 0) { return string_t(); }
            str_t newStr   = allocator::alloc(newCap);
            newStr[newLen] = (char_t) '\0';

            for (uint_t i = 0, j = 0; i < _F_length; i++)
            {
                if (!finds.contains(i))
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                }
                else
                {
                    for (char_t c : __new)
                    {
                        newStr[j] = c;
                        j++;
                    }
                    i += __old.length()-1;
                }
            }

            return string_t(newStr, newLen, newCap);
        }

        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::replaceFirst(char_t __old, char_t __new) const
    {
        int position = find(__old);
        if (position != -1)
        {
            string_t str(*this);
            str._F_charseq[position] = __new;
            return str;
        }
        else return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::replaceFirst(const_str_t __old, const_str_t __new) const
    {
        return replaceFirst(string_t(__old), string_t(__new));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::replaceFirst(const string_t& __old, const string_t& __new) const
    {
        int position(find(__old));
        if (position != -1)
        {
            int diffs       = (int) __new.length() - __old.length();
            uint_t newLen   = (uint_t) ((int) _F_length + diffs);
            uint_t newCap   = newLen + 1;

            if (newLen == 0) { return string_t(); }
            str_t newStr   = allocator::alloc(newCap);
            newStr[newLen] = (char_t) 0;

            for (uint_t i = 0, j = 0; i < _F_length; i++)
            {
                if ((uint_t) position != i)
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                }
                else
                {
                    for (char_t c : __new)
                    {
                        newStr[j] = c;
                        j++;
                    }
                    i += __old.length();
                }
            }

            string_t str;
            str.__set(newStr, newLen, newCap);
            return str;
        }
        else return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    ArrayList<typename __String__<_CharT, _Traits, _Alloc>::string_t>
    __String__<_CharT, _Traits, _Alloc>::split(char_t separator) const
    {
        ArrayList<uint_t> finds = findAll(separator);
        ArrayList<string_t> splits;
        if (finds.size() > 0)
        {
            uint_t offset = 0;
            for (uint_t i : finds)
            {
                uint_t len = i - offset - 1;
                splits.add(string_t(subSequence(offset, len), len, len+1));
                offset = i+1;
            }
        }
        else
        {
            splits.add(*this);
        }

        return splits;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    ArrayList<typename __String__<_CharT, _Traits, _Alloc>::string_t>
    __String__<_CharT, _Traits, _Alloc>::split(const_str_t separator) const
    {
        uint_t separatorLen = traits_type::len(separator);
        ArrayList<uint_t> finds = findAll(separator);
        ArrayList<string_t> splits;
        if (finds.size() > 0)
        {
            uint_t offset = 0;
            for (uint_t i : finds)
            {
                uint_t len = i - offset - 1;
                splits.add(string_t(subSequence(offset, len), len, len+1));
                offset = i+separatorLen+1;
            }
        }
        else
        {
            splits.add(*this);
        }

        return splits;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    ArrayList<typename __String__<_CharT, _Traits, _Alloc>::string_t>
    __String__<_CharT, _Traits, _Alloc>::split(const string_t& separator) const
    {
        ArrayList<uint_t> finds = findAll(separator);
        ArrayList<string_t> splits;
        if (finds.size() > 0)
        {
            uint_t offset = 0;
            for (uint_t i : finds)
            {
                uint_t len = i - offset - 1;
                splits.add(string_t(subSequence(offset, len), len, len+1));
                offset = i+separator.length()+1;
            }
        }
        else
        {
            splits.add(*this);
        }

        return splits;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::str_t
    __String__<_CharT, _Traits, _Alloc>::subSequence(uint_t offset, uint_t len) const
    {
        if (offset >= length()) return traits_type::copy((const_str_t) "");
        if (offset+len > length()) len = length()-offset;

        str_t sub = allocator::alloc(1+len);
        sub[len]  = (char_t) 0;

        for (uint_t i = 0; i < len; i++)
        {
            sub[i] = _F_charseq[i+offset];
        }

        return sub;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::toLowerCase() const
    {
        char_t lower = (char_t) 'a';
        char_t upper = (char_t) 'A', e_upper = 'Z';
        string_t lowerCase(*this);

        for (uint_t i = 0; i < _F_length; i++)
        {
            char_t &c = lowerCase._F_charseq[i];
            if (c >= upper && c <= e_upper)
            {
                c = lower + (c-upper);
            }
        }

        return lowerCase;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::toUpperCase() const
    {
        char_t upper = (char_t) 'A';
        char_t lower = (char_t) 'a', e_lower = 'z';
        string_t upperCase(*this);

        for (uint_t i = 0; i < _F_length; i++)
        {
            char_t &c = upperCase._F_charseq[i];
            if (c >= lower && c <= e_lower)
            {
                c = upper + (c-lower);
            }
        }

        return upperCase;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::const_str_t
    __String__<_CharT, _Traits, _Alloc>::getCharSequence() const
    {
        return _F_charseq;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    int __String__<_CharT, _Traits, _Alloc>::toInteger() const
    {
        int value(0), offset(0);
        bool negative(false);

        if (_F_length > 0)
        {
            switch (_F_charseq[0])
            {
                case '-':
                    negative = true;
                    [[fallthrough]];
                case '+':
                    offset++;
                    break;
            }

            for (uint_t i = 0, pow = length()-offset-1; i < length(); i++, pow--)
            {
                char_t c(_F_charseq[i]);

                value += (int)((double)((char) c) - '0')*__builtin_pow(10., (double) pow);
            }
        }

        return negative ? -value : value;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    long_t __String__<_CharT, _Traits, _Alloc>::toLong() const
    {
        long_t value(0), offset(0);
        bool negative(false);

        if (_F_length > 0)
        {
            switch (_F_charseq[0])
            {
                case '-':
                    negative = true;
                    [[fallthrough]];
                case '+':
                    offset++;
                    break;
            }

            for (uint_t i = 0, pow = length()-offset-1; i < length(); i++, pow--)
            {
                char_t c(_F_charseq[i]);

                value += (long_t)((double)((char) c) - '0')*__builtin_pow(10., (double) pow);
            }
        }

        return negative ? -value : value;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    double __String__<_CharT, _Traits, _Alloc>::toDouble() const
    {
        double value(0), decimal(0), exponent(-1.0);
        bool negative(false), negativeExp(false);
        int offset(0);

        // expected char order : '-'/'+' -> digit or {optinal:'.' -> 'digit' -> {optional: 'e + digit...'}}
        // check sign
        switch (_F_charseq[0])
        {
            case '-':
                negative = true;
                [[fallthrough]];
            case '+':
                offset++;
                break;
        }

        // parseState's value :
        //  . 0 = digit before dot
        //  . 1 = digit after dot
        //  . 2 = ten pow X (scientific)
        int parseState(0);
        for (uint_t i = offset; i < _F_length; i++)
        {
            char_t ch(_F_charseq[i]);
            switch (parseState)
            {
                case 0: // parse digits before the dot
                    if (ch == (char_t) '.')
                    {
                        parseState++;
                        continue;
                    }
                    value *= 10;
                    value += (double) ch - ((char_t) '0');
                    break;
                case 1: // parse digits after the dot
                    if (ch == (char_t) 'e')
                    {
                        parseState++;
                        exponent = 0;
                        switch (_F_charseq[i+1])
                        {
                            case '-':
                                negativeExp = true;
                                [[fallthrough]];
                            case '+':
                                i++;
                                break;
                        }
                        continue;
                    }
                    decimal += ((double) ch - ((char_t) '0'))*__builtin_pow(10,exponent);
                    exponent--;
                    break;
                case 2: // parse exponent
                    exponent *= 10;
                    exponent += (double) ch - ((char_t) '0');
                    break;
            }
        }

        value = (value + decimal) * __builtin_pow(10, negativeExp ? -exponent : exponent);
        return negative ? -value : value;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    __String__<_CharT, _Traits, _Alloc>::operator int() const
    {
        return toInteger();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    __String__<_CharT, _Traits, _Alloc>::operator long_t() const
    {
        return toLong();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    __String__<_CharT, _Traits, _Alloc>::operator float() const
    {
        return (float) toDouble();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    __String__<_CharT, _Traits, _Alloc>::operator double() const
    {
        return toDouble();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    __String__<_CharT, _Traits, _Alloc>::operator const_str_t() const
    {
        return _F_charseq;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::operator=(char_t c)
    {
        str_t newStr = allocator::alloc(2u);
        newStr[0] = c;
        newStr[1] = (char_t) 0;
        __set(newStr, 1u, 2u);
        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::operator=(const_str_t str)
    {
        uint_t newLen = traits_type::len(str);
        str_t newStr  = traits_type::copy(str, newLen);
        __set(newStr, newLen, newLen+1);
        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t &
    __String__<_CharT, _Traits, _Alloc>::operator=(const string_t &str)
    {
        __set(traits_type::copy(str._F_charseq), str._F_length, str._F_length+1);
        return *this;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::operator+(char_t c) const
    {
        string_t str(*this);
        return str.append(c);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::operator+(const_str_t str) const
    {
        string_t __this(*this);
        return __this.append(str);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::operator+(const string_t& str) const
    {
        string_t __this(*this);
        return __this.append(str);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t&
    __String__<_CharT, _Traits, _Alloc>::operator+=(char_t c)
    {
        return append(c);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t&
    __String__<_CharT, _Traits, _Alloc>::operator+=(const_str_t str)
    {
        return append(str);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t&
    __String__<_CharT, _Traits, _Alloc>::operator+=(const string_t& str)
    {
        return append(str);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    bool __String__<_CharT, _Traits, _Alloc>::operator ==(const string_t& str) const
    {
        return equals(str);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::char_t
    __String__<_CharT, _Traits, _Alloc>::operator[](uint_t index) const
    {
        return _F_charseq[index];
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    hash_t __String__<_CharT, _Traits, _Alloc>::hashCode() const
    {
        hash_t hash(0);
        for (uint_t i = 0; i < _F_length; i++)
        {
            hash += _F_charseq[i]*((hash_t)__builtin_pow(31, _F_length-1-i));
        }
        return hash;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    String __String__<_CharT, _Traits, _Alloc>::toString() const
    {
        // TODO (v1.0 R) return toUTF8() instead
        return String((const char*) _F_charseq);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(char_t c)
    {
        return string_t(c);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(bool b)
    {
        const char *_bstr = (b ? "true" : "false");
        string_t str;
        for (int i(0); _bstr[i] != '\0'; i++)
            str.append((char_t) _bstr[i]);
        return str;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(int i)
    {
        return ToString((long)i);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(long l)
    {
        string_t str;
        bool neg(l<0);

        do
        {
            str.prepend((char_t) '0' + l%10);
            l /= 10;
        } while (l != 0);

        if (neg)
        {
            str.prepend('-');
        }

        return str;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(float f)
    {
        return ToString((double) f);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(double d)
    {
        char* dstr = doublestr(d);
        string_t str;

        for (int i(0); dstr[i] != '\0'; i++)
        {
            str += (char_t) dstr[i];
        }

        return str; // Todo (v1.0 R) my own implementation of ToString(double)
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(const_str_t str)
    {
        return string_t(str);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(const Object& obj)
    {

        String objStr(obj.toString());
        str_t str = allocator::alloc(objStr.length() + 1);
        str[objStr.length()] = (char_t) 0;

        for (uint_t i = 0; i < objStr.length(); i++)
            str[i] = (char_t) objStr[i];

        return string_t(str, objStr.length(), objStr.capacity());

    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(const string_t& obj)
    {
        return string_t (obj);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::ToString(hash_t hash)
    {
        return toHexString(hash);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::toHexString(ullong_t ul)
    {
        int lowchar[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        string_t hex;
        int only0(0);

         do {
             unsigned char bits = 0xf & ul;

             if (bits == 0) only0++;
             else
             {
                 if (only0 > 0)
                 {
                     for (int i = 0; i < only0; i++)
                         hex.prepend((char_t) '0');
                     only0=0;
                 }

                 int ch = lowchar[bits];
                 hex.prepend((char_t) ch);
             }

             ul >>= 4;
         } while (ul != 0);

         if (hex.length() == 0) hex.append((char_t)'0');

         hex.prepend((char_t)'x');
         hex.prepend((char_t)'0');
         return hex;
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    hash_t Traits< __String__<_CharT, _Traits, _Alloc> >::hash_code(const_ref_t obj)
    {
        return obj.hashCode();
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Traits< __String__<_CharT, _Traits, _Alloc> >::ptr_t
    Traits< __String__<_CharT, _Traits, _Alloc> >::copy(const_ptr_t ptr, size_t __size)
    {
        ptr_t cpy = (ptr_t) malloc(sizeof(String)*__size);
        for (size_t i(0); i < __size; i++)
        {
            cpy[i] = ptr[i];
        }
        return cpy;
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Traits< __String__<_CharT, _Traits, _Alloc> >::size_t
    Traits< __String__<_CharT, _Traits, _Alloc> >::fill(const_ptr_t src, ptr_t dest, size_t size)
    {
        size_t i(0);
        for (; i < size; i++)
        {
            dest[i] = src[i];
        }
        return i;
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    struct Traits< __String__<_CharT, _Traits, _Alloc>[] >
    {
        typedef __String__<_CharT, _Traits, _Alloc>   value_t;
        typedef __String__<_CharT, _Traits, _Alloc>&  ref_t;
        typedef __String__<_CharT, _Traits, _Alloc>&& rvalue_t;
        typedef __String__<_CharT, _Traits, _Alloc>*  ptr_t;

        typedef const __String__<_CharT, _Traits, _Alloc>     const_t;
        typedef const __String__<_CharT, _Traits, _Alloc>*    const_ptr_t;
        typedef const __String__<_CharT, _Traits, _Alloc>&    const_ref_t;

        typedef ulong_t     size_t;

        static ptr_t  copy(const_ptr_t ptr, size_t __size);
        static size_t fill(const_ptr_t src, ptr_t dest, size_t size);
    };

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Traits< __String__<_CharT, _Traits, _Alloc>[] >::ptr_t
    Traits< __String__<_CharT, _Traits, _Alloc>[] >::copy(const_ptr_t ptr, size_t __size)
    {
        ptr_t cpy = (ptr_t) malloc(sizeof(String)*__size);
        for (size_t i(0); i < __size; i++)
        {
            cpy[i] = ptr[i];
        }
        return cpy;
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Traits< __String__<_CharT, _Traits, _Alloc>[] >::size_t
    Traits< __String__<_CharT, _Traits, _Alloc>[] >::fill(const_ptr_t src, ptr_t dest, size_t size)
    {
        size_t i(0);
        for (; i < size; i++)
        {
            dest[i] = src[i];
        }
        return i;
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Alloc< __String__<_CharT, _Traits, _Alloc> >::ptr_t Alloc< __String__<_CharT, _Traits, _Alloc> >::alloc()
    {
        return (ptr_t) ::malloc(sizeof(__String__<_CharT, _Traits, _Alloc>));
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Alloc< __String__<_CharT, _Traits, _Alloc> >::ptr_t
    Alloc< __String__<_CharT, _Traits, _Alloc> >::alloc(size_t nmemb)
    {
        return new value_t[nmemb];
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Alloc< __String__<_CharT, _Traits, _Alloc> >::ptr_t
    Alloc< __String__<_CharT, _Traits, _Alloc> >::calloc(size_t nmemb)
    {
        return (ptr_t) ::calloc(nmemb, sizeof(value_t));
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Alloc< __String__<_CharT, _Traits, _Alloc> >::size_t Alloc< __String__<_CharT, _Traits, _Alloc> >::sizeOf()
    {
        return sizeof(value_t);
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Alloc< __String__<_CharT, _Traits, _Alloc>[] >::ptr_t
    Alloc< __String__<_CharT, _Traits, _Alloc>[] >::alloc(size_t nmemb)
    {
        return new value_t[nmemb];
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Alloc< __String__<_CharT, _Traits, _Alloc>[] >::ptr_t
    Alloc< __String__<_CharT, _Traits, _Alloc>[] >::calloc(size_t nmemb)
    {
        return (ptr_t) ::calloc(nmemb, sizeof(value_t));
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    typename Alloc< __String__<_CharT, _Traits, _Alloc>[] >::size_t Alloc< __String__<_CharT, _Traits, _Alloc>[] >::sizeOf()
    {
        return sizeof(value_t);
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    void Delete< __String__<_CharT, _Traits, _Alloc> >::free(ptr_t ptr)
    {
        delete ptr;
    }

    template <typename _CharT, typename _Traits, typename _Alloc>
    void Delete< __String__<_CharT, _Traits, _Alloc>[] >::free(ptr_t ptr)
    {
        delete[] ptr;
    }
}

#endif //CPP_STRING_HPP
