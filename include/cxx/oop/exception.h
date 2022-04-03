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
