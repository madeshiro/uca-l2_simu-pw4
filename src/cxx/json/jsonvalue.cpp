#include "cxx/json/jsonvalue.h"
#include "cxx/oop/object"

namespace UCA_L2INFO_PW4
{
    using namespace json;

    template<>
    JsonValue::JsonValue(short value)
    {
        _F_value.ll = value;
    }

    template<>
    JsonValue::JsonValue(int value)
    {
        _F_value.ll = value;
    }

    template<>
    JsonValue::JsonValue(long value)
    {
        _F_value.ll = value;
    }

    template<>
    JsonValue::JsonValue(llong_t value)
    {
        _F_value.ll = value;
    }
}