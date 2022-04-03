#ifndef CPP_JSON_H
#define CPP_JSON_H

#include "cxx/oop/stream.h"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        class Json : public Object
        {
            //JsonContainer root;
        };

        class JsonStringifyable : public Object
        {
        public:
            virtual Json toJson() const {
                return Json(); // Todo: make pure when Json implemented !
            };
        };
    }
}

#endif //CPP_JSON_H
