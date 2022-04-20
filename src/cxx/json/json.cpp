#include "cxx/json/json.h"
#include "cxx/json/jsoncontainer.h"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        Json::JsonPath::JsonPath(int index): _F_isString(false)
        {
            _F_identifier.index = index;
        }

        Json::JsonPath::JsonPath(String str): _F_isString(true)
        {
            _F_identifier.str = new String(str);
        }

        Json::JsonPath::JsonPath(const JsonPath &path):
                _F_isString(path._F_isString)
        {
            if (_F_isString)
            {
                _F_identifier.str = new String(*path._F_identifier.str);
            }
            else
            {
                _F_identifier.index = path._F_identifier.index;
            }
        }

        Json::JsonPath::~JsonPath()
        {
            if (_F_isString)
            {
                delete _F_identifier.str;
            }
        }

        bool Json::JsonPath::isString() const
        {
            return _F_isString;
        }

        String Json::JsonPath::getName() const
        {
            return *_F_identifier.str;
        }

        int Json::JsonPath::getIndex() const
        {
            return _F_identifier.index;
        }

        Json::JsonPath::operator String() const
        {
            return getName();
        }

        Json::JsonPath::operator int() const
        {
            return getIndex();
        }

        Json::JsonPath& Json::JsonPath::operator=(const JsonPath &path)
        {
            _F_isString = path._F_isString;
            if (_F_isString)
            {
                _F_identifier.str = new String(*path._F_identifier.str);
            }
            else
            {
                _F_identifier.index = path._F_identifier.index;
            }
            return *this;
        }

        Json::Json(bool objAsRoot)
        {
            if (objAsRoot)
            {
                root = new JsonMap();
            }
            else
            {
                root = new JsonArray();
            }
        }

        Json::Json(const JsonObject &root) noexcept(false)
        {
            if (root.isMap())
            {
                this->root = new JsonMap((const JsonMap&) root);
            }
            else if (root.isArray())
            {
                this->root = new JsonArray((const JsonArray&) root);
            }
            else
            {
                throw JsonInvalidType("Not expected a value as Json root", uThrow);
            }
        }

        Json::Json(const Json &json)
        {
            if (json.root->isMap())
            {
                root = new JsonMap((const JsonMap&) json.root);
            }
            else
            {
                root = new JsonArray((const JsonArray&) json.root);
            }
        }

        Json::~Json()
        {
            if (root)
            {
                delete root;
            }
        }

        size_t Json::write(OutputStream &stream, int charset [[gnu::unused]]) const
        {
            String jsonString(root->stringify(true));
            return stream.write(jsonString.getCharSequence(), jsonString.length());
        }

        bool Json::read(InputStream &stream, int charset [[gnu::unused]])
        {
            JsonObject* parse = JsonParser::parse(&stream);
            if (parse)
            {
                if (root)
                {
                    delete root;
                }

                root = parse;
                return true;
            }
            else return false;
        }

        bool Json::read(String json, int charset [[gnu::unused]])
        {
            JsonObject* parse = JsonParser::parse(&json);
            if (parse)
            {
                if (root)
                {
                    delete root;
                }

                root = parse;
                return true;
            } else return false;
        }

        String Json::TransformCtrlChars(const String &str)
        {
            String transform(str);
            for (char ctrlChar : ctrlChars)
            {
                const char* replacing;
                switch (ctrlChar)
                {
                    case '\n':
                        replacing = "\\n";
                        break;
                    case '\t':
                        replacing = "\\t";
                        break;
                    case '\r':
                        replacing = "\\r";
                        break;
                    case '\"':
                        replacing = "\\\"";
                        break;
                    case '\\':
                        replacing = "\\\\";
                        break;
                    default:
                        replacing = "";
                        break;
                }

                transform = transform.replace(String(ctrlChar), String(replacing));
            }

            return transform;
        }

        bool Json::put(const JsonObject &obj, const ArrayList<JsonPath>& path)
        {
            union { JsonMap* map; JsonArray* list; JsonObject* obj; } container;

            container.obj = root;
            for (size_t i(0); i < path.size()-1; i++)
            {
                if (container.obj->isMap())
                {
                    if (!container.map->contains(path[i]))
                    {
                        if (path[i+1].isString())
                            container.map->set(path[i], new JsonMap);
                        else
                            container.map->set(path[i], new JsonArray);
                    }

                    container.obj = *container.map->get(path[i]);
                }
                else
                {
                    if ((size_t) path[i] == container.list->size())
                    {
                        if (path[i+1].isString())
                            container.list->add(new JsonMap);
                        else
                            container.list->add(new JsonArray);
                    }
                    else if ((size_t) path[i] > container.list->size())
                    {
                        return false;
                    }

                    container.obj = container.list->get(path[i]);
                }
            }

            JsonPath emplacement(path.get(path.size()-1));
            if (emplacement.isString())
            {
                if (!container.obj->isMap()) return false;
                container.map->set(emplacement, obj.clone());
            }
            else
            {
                if (!container.obj->isArray()) return false;
                if ((size_t) emplacement < container.list->size())
                {
                    container.list->set(obj.clone(), emplacement);
                }
                else if ((size_t) emplacement == container.list->size())
                {
                    container.list->add(obj.clone());
                }
                else return false;
            }

            return true;
        }

        String Json::toString() const
        {
            return root->stringify(false);
        }

        template <>
        JsonMap* Json::getRoot()
        {
            if (root->isMap())
            {
                return dynamic_cast<JsonMap *>(root);
            } else return nullptr;
        }

        template <>
        JsonArray* Json::getRoot()
        {
            if (root->isArray())
            {
                return dynamic_cast<JsonArray *>(root);
            } else return nullptr;
        }

        JsonParser::JsonParser(const String *str): _F_stringStream(true)
        {
            _F_stream.jsonStr = str;
        }

        JsonParser::JsonParser(InputStream *stream): _F_stringStream(false)
        {
            _F_stream.jsonStream = stream;
        }

        JsonObject* JsonParser::parse()
        {
            if (_F_stringStream)
            {
                return nullptr;
            }
            else
            {
                return new JsonArray();
            }
        }

        JsonObject* JsonParser::parse(const String *str)
        {
            return JsonParser(str).parse();
        }

        JsonObject* JsonParser::parse(InputStream *stream)
        {
            return JsonParser(stream).parse();
        }


        JsonInvalidType::JsonInvalidType(): Exception()
        {/*...*/}

        JsonInvalidType::JsonInvalidType(String msg): Exception(msg)
        {/*...*/}

        JsonInvalidType::JsonInvalidType(String msg, String file, String function, int line):
            Exception(msg, file, function, line)
        {/*...*/}

        JsonInvalidType::JsonInvalidType(const JsonInvalidType &ex): Exception(ex)
        {/*...*/}

        String JsonInvalidType::getName() const
        {
            return "JsonInvalidType";
        }
    }
}