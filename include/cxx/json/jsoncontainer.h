#ifndef CPP_JSONCONTAINER_H
#define CPP_JSONCONTAINER_H
#include "jsonvalue.h"
#include "../oop/container.hpp"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        class JsonMap : public HashMap<String, JsonObject*>, JsonObject
        {
        public:

            virtual String toString() const override;
        };

        class JsonArray : public ArrayList<JsonObject*>, JsonObject
        {

        };
    }
}

#endif //CPP_JSONCONTAINER_H
