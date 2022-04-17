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
