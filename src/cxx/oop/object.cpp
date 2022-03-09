#define OOP_IMPL_TEMPLATE_STRING
#include "cxx/oop/object.h"
#include "cxx/oop/string.hpp"

namespace UCA_L2INFO_PW4
{
    template class __String__<char>;
    template class __String__<wchar_t>;
    template class __StringBuilder__<char>;
    template class __StringBuilder__<wchar_t>;

    hash_t Object::hashCode()
    {
        return (hash_t) this;
    }
}