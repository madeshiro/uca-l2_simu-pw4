#include "cxx/json/jsonvalue.h"
#include "cxx/oop/object"
#include "cxx/json/json.h"

namespace UCA_L2INFO_PW4
{
    using namespace json;

    JsonObject::JsonObject(int indentLvl): _F_indentLevel(indentLvl)
    {}

    JsonObject::JsonObject(const JsonObject &obj): _F_indentLevel(obj._F_indentLevel)
    {}

    void JsonObject::setIndentLevel(int lvl)
    {
        _F_indentLevel = lvl;
    }

    int JsonObject::getIndentLevel() const
    {
        return _F_indentLevel;
    }

    JsonValue::JsonValue(): _F_type(Null)
    {
        _F_value.str = nullptr;
    }

    JsonValue::JsonValue(bool b): _F_type(Boolean)
    {
        _F_value.b = b;
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

    JsonValue::JsonValue(::UCA_L2INFO_PW4::String str): _F_type(String)
    {
        _F_value.str = Traits<char>::copy(str.getCharSequence(), str.length()+1);
    }

    JsonValue::JsonValue(const JsonValue& jValue): JsonObject(jValue), _F_type(jValue.getType())
    {
        if (_F_type == String)
        {
            _F_value.str = Traits<char>::copy(jValue._F_value.str);
        }
        else
        {
            _F_value = jValue._F_value;
        }
    }

    JsonValue::~JsonValue()
    {
        if (_F_type == String && _F_value.str != nullptr)
        {
            delete[] _F_value.str;
        }
    }

    template<>
    int JsonValue::getValue() const
    {
        if (_F_type == Integer)
        {
            return (int) _F_value.ll;
        }
        return 0;
    }

    template<>
    long JsonValue::getValue() const
    {
        if (_F_type == Integer)
        {
            return (long) _F_value.ll;
        }
        return 0;
    }

    template<>
    llong_t JsonValue::getValue() const
    {
        if (_F_type == Integer)
        {
            return _F_value.ll;
        }
        return 0;
    }
    
    template<>
    String JsonValue::getValue() const
    {
        if (_F_type == String)
        {
            return _F_value.str;
        }
        return "";
    }

    template<>
    const char* JsonValue::getValue() const
    {
        if (_F_type == String)
        {
            return _F_value.str;
        }
        return nullptr;
    }

    JsonValue::Type JsonValue::getType() const
    {
        return _F_type;
    }

    bool JsonValue::isArray() const
    {
        return false;
    }

    bool JsonValue::isMap() const
    {
        return false;
    }

    bool JsonValue::isValue() const
    {
        return true;
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
                return ::UCA_L2INFO_PW4::String("\"{0}\"").format(
                        Json::TransformCtrlChars(_F_value.str)
                );
            case Boolean:
                return String::ToString(_F_value.b);
            case Null: default:
                return "null";
        }
    }

    String JsonValue::stringify(bool doIndentation [[gnu::unused]]) const
    {
        return toString();
    }

    JsonObject* JsonValue::clone() const
    {
        return new JsonValue(*this);
    }
}