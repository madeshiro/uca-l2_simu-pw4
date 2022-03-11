#ifndef CPP_STRING_HPP
#define CPP_STRING_HPP
#include "defines.h"
#include "cxx/oop/object.h"
#include "cxx/oop/container.hpp"
#include "cxx/oop/alloc.hpp"


namespace UCA_L2INFO_PW4
{
    template < typename _CharT, typename _Traits = Traits<_CharT>, typename _Alloc = Alloc<_CharT> >
    class CharSequence : public Iterable<_CharT, _Traits>
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
    class __String__ : public CharSequence<_CharT, _Traits, _Alloc>,
                              Comparable< __String__<_CharT, _Traits, _Alloc> >
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
        uint_t  _F_capacity;

        void __delete();
        bool __grow(uint_t capacity);
        void __set(str_t charseq, uint_t len, uint_t capacity);

        __String__(const_str_t str, uint_t len, uint_t capacity):
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

        char_t charAt(uint_t index) const override;

        int compareTo(const __String__<_CharT, _Traits, _Alloc>& str) const override;

        bool contains(char_t c) const;
        bool contains(const_str_t str) const;
        bool contains(const string_t& str) const;

        bool beginsWith(char_t c) const;
        bool beginsWith(const_str_t str) const;
        bool beginsWith(const string_t& str) const;

        bool endsWith(char_t c) const;
        bool endsWith(const_str_t str) const;
        bool endsWith(const string_t& str) const;

        virtual bool equals(const Object& object) const override;

        int find(char_t c) const;
        int find(const_str_t str) const;
        int find(const string_t& str) const;

        SortedSet<uint_t> findAll(char_t c) const;
        SortedSet<uint_t> findAll(const_str_t str) const;
        SortedSet<uint_t> findAll(const string_t& str) const;

        Iterator<char_t, traits_type> iterator() const override;

        uint_t length() const override;

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
        llong_t     toLLong() const;
        ldouble_t   toLDouble() const;

        virtual operator int() const;
        virtual operator long_t() const;
        virtual operator double() const;
        virtual operator llong_t() const;
        virtual operator ldouble_t() const;

        virtual operator const_str_t() const;

        /* OPERATOR */

        string_t & operator =(char_t c);
        string_t & operator =(const_str_t str);
        string_t & operator =(const string_t & str);

        string_t   operator +(char_t c);
        string_t   operator +(const_str_t str);
        string_t   operator +(const string_t & str);

        string_t & operator +=(char_t c);
        string_t & operator +=(const_str_t str);
        string_t & operator +=(const string_t & str);

        char_t operator[](uint_t index) const;

        /* OBJECT */

        virtual hash_t hashCode() const override;
        virtual String toString() const override;

        /* STATIC METHODS */

        static string_t toString(char);
        static string_t toString(int);
        static string_t toString(long);
        static string_t toString(float);
        static string_t toString(double);
        static string_t toString(const_str_t);
        static string_t toString(const Object&);

        static string_t toHexString(unsigned long);
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
            _F_length(str._F_length), _F_capacity(str._F_capacity)
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
        _F_length = 0;
        _F_capacity = 0;
        _F_charseq = 0;
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
            cpy[i] = (char_t) 0;

            _F_capacity += capacity;
            deleter::free(_F_charseq);
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
        string_t str(*this), elems[sizeof...(T)] = {toString(args)...};

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
        return string_t(*this).append(string_t::toString(arg));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    template<typename... T>
    typename __String__<_CharT, _Traits, _Alloc>::string_t
    __String__<_CharT, _Traits, _Alloc>::format(T ...args) const
    {
        string_t str(*this), elems[sizeof...(T)] = {toString(args)...};

        for (uint_t i = 0; i < sizeof...(T); i++)
        {
            str = replace(string_t("{") + toString((i+1)) + string_t("}"), elems[i]);
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
        if (_F_capacity >= length()+str.length())
        {
            if (!__grow(1+(_F_capacity - (length()+str.length()))))
            {
                return *this;
            }
        }

        for (uint_t i = 0, j = length(); i < str.length(); i++)
        {
            _F_charseq[j] = str[i];
        }
        return *this;
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
                 str    = str.toLowerCase();

        uint_t minLen = str.length() < __this.length() ? str.length() : __this.length();
        if (__this.equals(str))
            return 0;

        for (uint_t i = 0; i <minLen; i++)
        {
            if (__this[i] < str[i])
            {
                return -1;
            }
            else if (__this[i] > str[i])
            {
                return 1;
            }
        }

        return __this.length() < str.length() ? -1 : 1;
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
        string_t str(object.toString());
        if (str.length() == length())
        {
            for (uint_t i = 0; i < length(); i++)
            {
                if (str[i] != _F_charseq[i])
                    return false;
            }
            return true;
        }
        else return false;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    int __String__<_CharT, _Traits, _Alloc>::find(char_t c) const
    {
        for (int i = 0; i < length(); i++)
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
            for (int i = 0; i < length(); i++)
            {
                if (_F_charseq[i] == str[0])
                {
                    if (str.length() > length()-i)
                        break;

                    int j;
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
    SortedSet<uint_t> __String__<_CharT, _Traits, _Alloc>::findAll(char_t c) const
    {
        SortedSet<uint_t> finds;

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
    SortedSet<uint_t> __String__<_CharT, _Traits, _Alloc>::findAll(const_str_t str) const
    {
        return findAll(string_t(str));
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    SortedSet<uint_t> __String__<_CharT, _Traits, _Alloc>::findAll(const string_t &str) const
    {
        SortedSet<uint_t> finds;

        if (str.length() <= length())
        {
            for (int i = 0; i < length(); i++)
            {
                if (_F_charseq[i] == str[0])
                {
                    if (str.length() > length()-i)
                        break;

                    int j;
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
    Iterator<typename __String__<_CharT, _Traits, _Alloc>::char_t,
             typename __String__<_CharT, _Traits, _Alloc>::traits_type>
    __String__<_CharT, _Traits, _Alloc>::iterator() const
    {
        return Iterator<char_t, traits_type>(_F_charseq, _F_charseq+_F_length);
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    uint_t __String__<_CharT, _Traits, _Alloc>::length() const
    {
        return _F_length;
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    typename __String__<_CharT, _Traits, _Alloc>::string_t&
    __String__<_CharT, _Traits, _Alloc>::remove(char_t c)
    {
        SortedSet<uint_t> finds = findAll(c);

        if (finds.size() > 0)
        {
            uint_t newLen  = _F_length - finds.size();
            uint_t newCap  = newLen + 1;
            str_t newStr   = allocator::alloc(newCap);
            newStr[newLen] = (char_t) 0;

            for (uint_t i = 0, j = 0, k = 0; i < _F_length; i++)
            {
                if (finds.get(k) != i)
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                } else k++;
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
        SortedSet<uint_t> finds = findAll(str);

        if (finds.size() > 0)
        {
            uint_t newLen  = _F_length - (str.length()*finds.size());
            uint_t newCap  = newLen + 1;
            str_t newStr   = allocator::alloc(newCap);
            newStr[newLen] = (char_t) 0;

            for (uint_t i = 0, j = 0, k = 0; i < _F_length; i++)
            {
                if (finds.get(k) != i)
                {
                    newStr[j] = _F_charseq[i];
                    j++;
                }
                else
                {
                    k++;
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
        SortedSet<uint_t> finds = findAll(__old);

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
        SortedSet<uint_t> finds = findAll(__old);

        if (finds.size() > 0)
        {
            int diffs       = (int) __new.length() - __old.length();
            uint_t newLen   = (uint_t) ((int) finds.size()*(_F_length + diffs));
            uint_t newCap   = newLen + 1;

            if (newLen == 0) { return string_t(); }
            str_t newStr   = allocator::alloc(newCap);
            newStr[newLen] = (char_t) 0;

            for (uint_t i = 0, j = 0, k = 0; i < _F_length; i++)
            {
                if (finds[k] != i)
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
                    k++;
                }
            }

            string_t str;
            str.__set(newStr, newLen, newCap);
            return str;
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

            for (uint_t i = 0, j = 0, k = 0; i < _F_length; i++)
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
        SortedSet<uint_t> finds = findAll(separator);
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
        SortedSet<uint_t> finds = findAll(separator);
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
        SortedSet<uint_t> finds = findAll(separator);
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
        if (offset >= length()) return traits_type::copy("");
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
    typename __String__<_CharT, _Traits, _Alloc>::const_str_t
    __String__<_CharT, _Traits, _Alloc>::getCharSequence() const
    {
        return _F_charseq;
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
    __String__<_CharT, _Traits, _Alloc>::operator double() const
    {
        return toDouble();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    __String__<_CharT, _Traits, _Alloc>::operator llong_t() const
    {
        return toLLong();
    }

    template<typename _CharT, typename _Traits, typename _Alloc>
    __String__<_CharT, _Traits, _Alloc>::operator ldouble_t() const
    {
        return toLDouble();
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
}

#endif //CPP_STRING_HPP
