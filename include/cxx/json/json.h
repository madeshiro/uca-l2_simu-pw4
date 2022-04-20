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
#ifndef CPP_JSON_H
#define CPP_JSON_H

#include "cxx/oop/stream.h"
#include "cxx/oop/exception.h"
#include "jsonvalue.h"
#include "jsoncontainer.h"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        class Json final : public Object
        {
            JsonObject* root;

        public:
            class JsonPath : public Object
            {
                union {
                    String *str;
                    int index;
                } _F_identifier;

                bool _F_isString;
            public:
                JsonPath();
                JsonPath(String str);
                JsonPath(int index);
                JsonPath(const JsonPath& path);
                virtual ~JsonPath();

                bool isString() const;

                String getName() const;
                int getIndex() const;

                operator String() const;
                operator int() const;

                virtual JsonPath& operator=(const JsonPath& path);
            };

            constexpr static const char ctrlChars[] = {'\\', '\n', '\t', '\r', '\"'};
            constexpr static const char spacingChars[] = {' ', '\n', '\t', '\r'};

            Json(bool objAsRoot = true);
            Json(const JsonObject& root) noexcept(false);
            Json(const Json& json);
            virtual ~Json() override;

            size_t write(OutputStream& stream, int charset = CHARSET_ASCII) const;
            /**
             *
             * @warning Reading a stream reset current data to replace it by
             * the ones get from the stream
             * @param stream
             * @return True if the stream has been parsed successfuly
             */
            bool read(InputStream& stream, int charset = CHARSET_ASCII);
            /**
             *
             * @param json
             * @return
             */
            bool read(String json, int charset = CHARSET_ASCII);

            /**
             *
             * @param str
             * @return
             */
            static String TransformCtrlChars(const String& str);

            template < typename... Path >
            static ArrayList<JsonPath> BuildJPath(Path... path)
            {
                JsonPath paths[sizeof...(path)] = {JsonPath(path)...};
                ArrayList<JsonPath> list;

                for (size_t i(0); i < sizeof...(path); i++)
                {
                    list.add(paths[i]);
                }

                return list;
            }

            template < typename T >
            T* getRoot();

            template < typename... Path >
            bool put(const JsonObject& obj, Path... path)
            {
                return put(obj, BuildJPath(path...));
            }

            bool put(const JsonObject& obj, const ArrayList<JsonPath>& path);

            template < typename... Path >
            bool remove(Path... path)
            {
                return remove(BuildJPath(path...));
            }

            bool remove(const Collection<JsonPath>& path);

            virtual String toString() const override;
        };

        class JsonParser : public Object
        {
            union Reader
            {
                const String* jsonStr;
                InputStream* jsonStream;
            } _F_stream;

            bool _F_stringStream;
            // Todo JsonValue parseValue();
            // Todo JsonMap   parseMap();
            // Todo JsonArray parseArray();
        public:
            JsonParser(const String* str);
            JsonParser(InputStream* stream);

            JsonObject* parse();

            static JsonObject* parse(const String* str);
            static JsonObject* parse(InputStream* stream);
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

        class JsonInvalidType : public Exception
        {
        public:
            JsonInvalidType();
            JsonInvalidType(String msg);
            JsonInvalidType(String msg, String file, String function, int line);
            JsonInvalidType(const JsonInvalidType&);

            virtual String getName() const override;
        };
    }
}

#endif //CPP_JSON_H
