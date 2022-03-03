#ifndef CPP_JSONVALUE_H
#define CPP_JSONVALUE_H
#include "defines.h"
#include "cxx/oop/object.h"
#include "cxx/oop/container.hpp"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        class JSONObject : public Object
        {
        public:

            virtual bool isArray() = 0;
            virtual bool isMap() = 0;
            virtual bool isValue() = 0;
        };

        class JSONValue : public JSONObject
        {
            union jvalue_t
            {
                char    c;
                short   s;
                int     i;
                long    l;
                llong_t ll;

                float       f;
                double      lf;
                ldouble_t   llf;

                char *  str;
            };

            jvalue_t value;
        public:
            enum Type : int
            {
                Char,
                Short,
                Integer,
                Long,
                LongLong,
                Float,
                Double,
                LongDouble,
                Scientific,
                String
            };

            virtual ~JSONValue();

            template <typename T>
            T getValue()
            {
                return value;
            }
        };

        class JSONMap : public HashMap<std::string, JSONObject &>
        {

        };

        class JSONArray : public ArrayList<JSONObject&>
        {

        };
    }
}

#endif //CPP_JSONVALUE_H
