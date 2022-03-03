#include "../../../include/cxx/oop/type_traits.hpp"

namespace UCA_L2INFO_PW4
{
    Traits<char>::size_t Traits<char>::len(Traits<char>::const_ptr_t str)
    {
        size_t len = 0;
        while(str[len] != '\0') len++;
        return len;
    }
}