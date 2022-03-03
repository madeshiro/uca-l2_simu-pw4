#ifndef CPP_SIMOBJECT_H
#define CPP_SIMOBJECT_H
#include "defines.h"
#include <string>
#include "type_traits.hpp"

namespace UCA_L2INFO_PW4
{
    template <typename _CharT, typename _Traits = Traits<_CharT>>
    class __String__;

    using String    = __String__<char>;
    using WString   = __String__<wchar_t>;

    class Object
    {
    public:
        Object()            = default;
        virtual ~Object()   = default;

        virtual bool equals(Object &&obj);
        virtual bool equals(Object & obj);
        virtual bool equals(Object * obj);

        virtual bool operator ==(Object &&obj);
        virtual bool operator ==(Object & obj);
        virtual bool operator ==(Object * obj);

        virtual String toString();
        virtual hash_t hashCode();
        virtual Object copy();
    };
}

#endif //CPP_SIMOBJECT_H
