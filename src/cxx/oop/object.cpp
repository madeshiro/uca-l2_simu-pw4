#include "cxx/oop/object.h"
#include "cxx/oop/string.hpp"

namespace UCA_L2INFO_PW4
{
    template class __String__<char>;
    template class __String__<wchar_t>;

    hash_t Object::hashCode()
    {
        return 0;
    }
}