#include "cxx/json/jsoncontainer.h"
#include "cxx/json/jsonvalue.h"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        JsonMap::JsonMap(const HashMap<String, JsonObject *> &object):
                HashMap<String, JsonObject *>()
        {
            if (dynamic_cast<const JsonObject*>(&object))
            {
                this->setIndentLevel(((const JsonMap&)object).getIndentLevel());
            }

            for (String key : object.keySet())
            {
                JsonObject* value(*object.get(key));
                if (value->isMap())
                {
                    this->set(key, new JsonMap((const JsonMap&) *value));
                }
                else if (value->isArray())
                {
                    this->set(key, new JsonArray((const JsonArray&) *value));
                }
                else
                {
                    this->set(key, new JsonValue((const JsonValue&) *value));
                }
            }
        }

        JsonMap::~JsonMap()
        {
            for (HashNode node : this->_F_nodes)
            {
                if (node.value)
                {
                    delete node.value;
                }
            }
        }

        bool JsonMap::set(key_t key, JsonObject *value)
        {
            value->setIndentLevel(getIndentLevel()+1);
            return HashMap<String, JsonObject*>::set(key, value);
        }

        bool JsonMap::isArray() const
        {
            return false;
        }

        bool JsonMap::isMap() const
        {
            return true;
        }

        bool JsonMap::isValue() const
        {
            return false;
        }

        String JsonMap::toString() const
        {
            return stringify(false);
        }

        String JsonMap::stringify(bool doIndentation) const
        {
            String text(doIndentation ? "{\n" : "{");
            {
                size_t elemCount(0);
                for (String key : keySet())
                {
                    if (doIndentation)
                    {
                        for (int i(0); i < getIndentLevel(); i++)
                            text.append('\t');
                    }
                    text.append(String("\"{0}\": ").format(key));
                    text.append((*get(key))->stringify(doIndentation));
                    if (elemCount + 1 < this->size())
                    {
                        text.append(", ");
                    }
                    if (doIndentation)
                    {
                        text.append('\n');
                    }
                }
            }
            return text.append('}');
        }

        JsonObject* JsonMap::clone() const
        {
            return new JsonMap(*this);
        }

        JsonArray::JsonArray(const Collection<JsonObject *> &list):
            ArrayList<JsonObject *>()
        {
            if (dynamic_cast<const JsonArray*>(&list))
            {
                setIndentLevel(dynamic_cast<const JsonArray*>(&list)->getIndentLevel());
            }

            for (JsonObject* obj : list)
            {
                if (obj->isArray())
                {
                    obj = new JsonArray((const JsonArray&) *obj);
                }
                else if (obj->isMap())
                {
                    obj = new JsonMap((const JsonMap&) *obj);
                }
                else
                {
                    obj = new JsonValue((const JsonValue&) *obj);
                }

                this->add(obj);
            }
        }

        JsonArray::~JsonArray()
        {
            for (JsonObject* obj : *this)
            {
                if (obj) delete obj;
            }
        }

        bool JsonArray::add(JsonObject *obj)
        {
            obj->setIndentLevel(getIndentLevel()+1);
            return ArrayList<JsonObject*>::add(obj);
        }

        bool JsonArray::isArray() const
        {
            return true;
        }

        bool JsonArray::isMap() const
        {
            return false;
        }

        bool JsonArray::isValue() const
        {
            return false;
        }

        String JsonArray::toString() const
        {
            return stringify(false);
        }

        String JsonArray::stringify(bool doIndentation) const
        {
            String text(doIndentation ? "[\n" : "[");
            {
                for (size_t i(0); i < _F_size; i++)
                {
                    if (doIndentation)
                    {
                        for (int indent(0); indent < getIndentLevel(); indent++)
                            text.append('\t');
                    }
                    text.append(get(i)->stringify(doIndentation));
                    if (i + 1 < this->size())
                    {
                        text.append(", ");
                    }
                    if (doIndentation)
                    {
                        text.append('\n');
                    }
                }
            }
            return text.append(']');
        }

        JsonObject* JsonArray::clone() const
        {
            return new JsonArray(*this);
        }
    }
}