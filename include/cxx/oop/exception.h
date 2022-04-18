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

#define stacktrace(X) catch(X & ex) { \
    ex.addStacktrace(UCA_L2INFO_PW4::StackTrace(__FILE__, __PRETTY_FUNCTION__, __LINE__)); \
    throw(ex); \
    }
#define uThrow __FILE__, __PRETTY_FUNCTION__, __LINE__

namespace UCA_L2INFO_PW4
{
    class StackTrace : public Object
    {
        String _F_file, _F_function;
        int _F_line;
    public:
        StackTrace();
        StackTrace(String file, String function, int line);
        StackTrace(const StackTrace&);
        virtual ~StackTrace() override;

        String getFile() const;
        String getMethod() const;
        int    getLine() const;

        virtual String toString() const override;
        virtual StackTrace& operator=(const StackTrace& trace);
    };

    class Exception : public Object
    {
    protected:
        String _F_msg;

        ArrayList<StackTrace> _F_stacks;
    public:
        Exception();
        Exception(String msg);
        Exception(String msg, String file, String function, int line);
        Exception(const Exception&);
        virtual ~Exception();

        virtual String getName() const;
        virtual String getMessage() const;
        virtual void printStackTrace() const;

        void addStacktrace(StackTrace trace);
        ArrayList<StackTrace> getTraces() const;

        virtual Exception& operator =(const Exception& ex);
    };

    class IndexOutOfBoundException : public Exception
    {
    public:
        IndexOutOfBoundException();
        IndexOutOfBoundException(String msg);
        IndexOutOfBoundException(String msg, String file, String function, int line);
        IndexOutOfBoundException(const IndexOutOfBoundException&);

        virtual String getName() const override;
    };

    /*

    class AllocationException : public Exception
    {

    };

    class InvalidFormatException : public Exception
    {

    };

    class NumberFormatException : public InvalidFormatException
    {

    };

    */
}

#endif //CPP_EXCEPTION_H
