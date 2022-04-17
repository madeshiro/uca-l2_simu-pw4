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

        public:
            virtual String toString() const override {
                return "";
            }
        };

        class JsonStringifyable : public Object
        {
        public:
            virtual Json toJson() const {
                return Json(); // Todo: make pure when Json implemented !
            };

            virtual String toString() const override {
                return toJson().toString();
            }
        };
    }
}

#endif //CPP_JSON_H
