#include "cxx/oop/exception.h"

namespace UCA_L2INFO_PW4
{
    Exception::Exception(std::string msg): msg(msg)
    {

    }

    IndexOutOfBoundException::IndexOutOfBoundException(std::string msg)
        : Exception(msg)
    {
        /* ... */
    }
}
