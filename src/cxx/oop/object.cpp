#define OOP_IMPL_TEMPLATE_STRING
#include "cxx/oop/object.h"
#include "cxx/oop/string.hpp"

namespace UCA_L2INFO_PW4
{
    template class __String__<char>;
    template class __String__<wchar_t>;
    template class __StringBuilder__<char>;
    template class __StringBuilder__<wchar_t>;

    bool Object::equals(const Object &&obj) const
    {
        return hashCode() == obj.hashCode();
    }

    bool Object::equals(const Object &obj) const
    {
        return hashCode() == obj.hashCode();
    }

    bool Object::equals(const Object *obj) const
    {
        return obj == this;
    }

    bool Object::operator==(const Object &&obj) const
    {
        return equals(obj);
    }

    bool Object::operator==(const Object &obj) const
    {
        return equals(obj);
    }

    bool Object::operator==(const Object *obj) const
    {
        return equals(obj);
    }

    String Object::toString() const
    {
        return String::toHexString(hashCode());
    }

    hash_t Object::hashCode() const
    {
        return (hash_t) this;
    }

    Object* Object::clone() const
    {
        return Traits<Object>::copy(this, sizeof(Object));
    }
}