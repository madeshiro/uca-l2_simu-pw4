#include "cxx/json/jsonvalue.h"
#include "cxx/oop/object"

namespace UCA_L2INFO_PW4
{
    using namespace json;

    JsonValue::JsonValue(): _F_type(Null)
    {
        _F_value.str = nullptr;
    }

    JsonValue::JsonValue(short value): _F_type(Integer)
    {
        _F_value.ll = value;
    }

    JsonValue::JsonValue(int value): _F_type(Integer)
    {
        _F_value.ll = value;
    }

    JsonValue::JsonValue(long value): _F_type(Integer)
    {
        _F_value.ll = value;
    }

    JsonValue::JsonValue(llong_t value): _F_type(Integer)
    {
        _F_value.ll = value;
    }

    JsonValue::JsonValue(float value): _F_type(Float)
    {
        _F_value.llf = value;
    }

    JsonValue::JsonValue(double value): _F_type(Float)
    {
        _F_value.llf = value;
    }

    JsonValue::JsonValue(ldouble_t value): _F_type(Float)
    {
        _F_value.llf = value;
    }

    JsonValue::~JsonValue()
    {
        if (_F_type == String && _F_value.str != nullptr)
        {
            delete[] _F_value.str;
        }
    }

    template<>
    int JsonValue::getValue()
    {
        if (_F_type == Integer)
        {
            return (int) _F_value.ll;
        }
        else throw JsonInvalidType("Value isn't an Integer", uThrow);
    }
    
    template<>
    long JsonValue::getValue()
    {
        if (_F_type == Integer)
        {
            return (long) _F_value.ll;
        }
        else throw JsonInvalidType();
    }

    template<>
    llong_t JsonValue::getValue()
    {
        if (_F_type == Integer)
        {
            return _F_value.ll;
        }
        else throw JsonInvalidType();
    }

    JsonValue::Type JsonValue::getType() const
    {
        return _F_type;
    }

    String JsonValue::toString() const
    {
        switch (_F_type)
        {
            case Integer:
                return String::ToString((long)_F_value.ll);
            case Float:
                return String::ToString((double)_F_value.llf);
            case String:
                return String::ToString(_F_value.str);
            case Boolean:
                return String::ToString(_F_value.b);
            case Null:
                return "null";
            default:
                return "";
        }
    }
}