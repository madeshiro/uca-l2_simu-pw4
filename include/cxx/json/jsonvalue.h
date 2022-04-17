/*
 * UCA-L2 simulation "practical work #4" : a realistic simulation of rabbit population growth
 * Copyright (C) 2022 -- Rin Baudelet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef CPP_JSONVALUE_H
#define CPP_JSONVALUE_H
#include "defines.h"
#include "cxx/oop/object.h"
#include "cxx/oop/container.hpp"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        class JsonObject : public Object
        {
        public:

            virtual bool isArray() = 0;
            virtual bool isMap() = 0;
            virtual bool isValue() = 0;

            virtual String stringify(bool doIndentation = true) = 0;
        };

        class JsonValue : public JsonObject
        {
            union jvalue_t
            {
                llong_t ll;
                ldouble_t   llf;
                char *  str;
            };

            jvalue_t _F_value;
        public:
            enum Type : int
            {
                Integer,
                Float,
                Scientific,
                String
            };

            template < typename T >
            JsonValue(T value);
            JsonValue(double value, bool scientific);

            virtual ~JsonValue();

            template <typename T>
            T getValue()
            {
                return value;
            }

            Type getType() const;
        };
    }
}

#endif //CPP_JSONVALUE_H
