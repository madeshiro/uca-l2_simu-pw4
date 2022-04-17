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
#ifndef CPP_EXCEPTION_H
#define CPP_EXCEPTION_H
#include "object.h"
#include "string.hpp"

namespace UCA_L2INFO_PW4
{
    class Exception : public Object
    {
    protected:
        String msg;
    public:
        Exception(String msg);
        virtual ~Exception() = default;

        virtual String getName() const;
        virtual String getMessage() const;
        virtual void printStackTrace() const;
    };

    class IndexOutOfBoundException : public Exception
    {
    public:
        IndexOutOfBoundException(String msg);

        virtual String getName() const;
    };

    class AllocationException : public Exception
    {

    };

    class InvalidFormatException : public Exception
    {

    };

    class NumberFormatException : public InvalidFormatException
    {

    };
}

#endif //CPP_EXCEPTION_H
