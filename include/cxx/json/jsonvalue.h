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
        protected:
            int _F_indentLevel = 0;

            JsonObject(int indentLvl=0);
        public:
            JsonObject(const JsonObject& obj);

            virtual bool isArray() const = 0;
            virtual bool isMap() const = 0;
            virtual bool isValue() const = 0;

            void setIndentLevel(int);
            int  getIndentLevel() const;

            virtual String stringify(bool doIndentation = true) const = 0;
            virtual JsonObject* clone() const = 0;
        };

        class JsonValue : public JsonObject
        {
            union jvalue_t
            {
                bool b;
                llong_t ll;
                ldouble_t   llf;
                char *  str;

                struct scientific {
                    float value;
                    int exponent;
                } scientific;
            } _F_value;

        public:
            enum Type : int
            {
                Null,
                Boolean,
                Integer,
                Float,
                Scientific,
                String
            };

            JsonValue();
            JsonValue(bool);
            JsonValue(int);
            JsonValue(long);
            JsonValue(short);
            JsonValue(float);
            JsonValue(double);
            JsonValue(llong_t);
            JsonValue(ldouble_t);
            JsonValue(const char*);
            JsonValue(::UCA_L2INFO_PW4::String);

            JsonValue(const JsonValue& jValue);

            virtual ~JsonValue();

            template <typename T>
            T getValue() const;

            Type getType() const;

            virtual bool isArray() const override;
            virtual bool isMap() const override;
            virtual bool isValue() const override;

            virtual ::UCA_L2INFO_PW4::String toString() const override;
            virtual ::UCA_L2INFO_PW4::String stringify(bool doIndentation=true) const override;

            virtual JsonObject* clone() const override;

        private:
            Type _F_type;
        };
    }
}

#endif //CPP_JSONVALUE_H
