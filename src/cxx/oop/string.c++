namespace UCA_L2INFO_PW4
{
    template < typename _CharT, typename _Traits >
    __String__<_CharT, _Traits>::__String__():
    _F_charseq(traits_type::copy("\0")), _F_length(0)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits >
    __String__<_CharT, _Traits>::__String__(char_t c):
    _F_charseq(traits_type::copy(&c, 1u)), _F_length(1)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits >
    __String__<_CharT, _Traits>::__String__(const_str_t str):
    _F_charseq(traits_type::copy(str)), _F_length(traits_type::len(str))
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits >
    __String__<_CharT, _Traits>::__String__(const string_t &str):
    _F_charseq(traits_type::copy(str._F_charseq, str._F_length)),
    _F_length(str._F_length)
    {
        /* Nothing to do here */
    }

    template < typename _CharT, typename _Traits >
    __String__<_CharT, _Traits>::~__String__<_CharT, _Traits>()
    {
        if (_F_charseq)
            delete[] _F_charseq;
        _F_length = 0;
        _F_charseq = 0;
    }
}