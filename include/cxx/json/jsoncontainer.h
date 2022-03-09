#ifndef CPP_JSONCONTAINER_H
#define CPP_JSONCONTAINER_H
#include "jsonvalue.h"
#include "../oop/container.hpp"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        class JsonMap : public HashMap<String, JsonValue>, JsonObject
        {
        public:

            virtual String toString();
        };

        class JsonArray : public ArrayList<JsonValue>, JsonObject
        {

        };
    }
}

#endif //CPP_JSONCONTAINER_H
