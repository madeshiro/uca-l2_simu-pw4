#include "cxx/oop/exception.h"
#include "cxx/application.h"

namespace UCA_L2INFO_PW4
{
    StackTrace::StackTrace(String file, String function, int line):
        _F_file(file), _F_function(function), _F_line(line)
    {
        /* ... */
    }

    StackTrace::StackTrace(const StackTrace& stack):
        _F_file(stack._F_file), _F_function(stack._F_function), _F_line(stack._F_line)
    {
        /* ... */
    }

    String StackTrace::getFile() const
    {
        return _F_file;
    }

    String StackTrace::getMethod() const
    {
        return _F_function;
    }

    int StackTrace::getLine() const
    {
        return _F_line;
    }

    String StackTrace::toString() const
    {
        return String("{0}:{1} in method {2}").format(_F_file, _F_line, _F_function);
    }

    StackTrace& StackTrace::operator=(const StackTrace &trace)
    {
        _F_file     = trace._F_file;
        _F_function = trace._F_function;
        _F_line     = trace._F_line;
        return *this;
    }

    StackTrace::~StackTrace()
    {

    }

    StackTrace::StackTrace(): _F_file(), _F_function(), _F_line(0)
    {

    }

    Exception::Exception(): _F_msg("An exception occured"), _F_stacks()
    { /* ... */ }

    Exception::Exception(String msg): _F_msg(msg), _F_stacks()
    { /* ... */ }

    Exception::Exception(String msg, String file, String function, int line):
        _F_msg(msg), _F_stacks()
    {
        _F_stacks.add(StackTrace(file, function, line));
    }

    Exception::Exception(const Exception & ex):
        _F_msg(ex._F_msg), _F_stacks(ex._F_stacks)
    { /* ... */ }

    Exception::~Exception()
    {
    }

    String Exception::getName() const
    {
        return "Exception";
    }

    String Exception::getMessage() const
    {
        return _F_msg;
    }

    void Exception::printStackTrace() const
    {
        Application::app->err->format("{0}: {1}\n", this->getName(), this->getMessage());
        if (!_F_stacks.isEmpty())
        {
            for (StackTrace trace: _F_stacks)
            {
                Application::app->err->format("\tat {0} ({1}:{2}\n",
                                              trace.getMethod(),
                                              trace.getFile(),
                                              trace.getLine());
            }
        }
    }

    void Exception::addStacktrace(StackTrace trace)
    {
        _F_stacks.add(trace);
    }

    ArrayList<StackTrace> Exception::getTraces() const
    {
        return _F_stacks;
    }

    Exception& Exception::operator=(const Exception &ex)
    {
        _F_msg = ex._F_msg;
        _F_stacks = ex._F_stacks;

        return *this;
    }

    IndexOutOfBoundException::IndexOutOfBoundException(): Exception()
    {/*...*/}

    IndexOutOfBoundException::IndexOutOfBoundException(String msg): Exception(msg)
    {/*...*/}

    IndexOutOfBoundException::IndexOutOfBoundException(String msg, String file, String function, int line):
            Exception(msg, file, function, line)
    {/*...*/}

    IndexOutOfBoundException::IndexOutOfBoundException(const IndexOutOfBoundException &ex): Exception(ex)
    {/*...*/}

    String IndexOutOfBoundException::getName() const
    {
        return "IndexOutOfBoundException";
    }

    // template<>
    // void Delete<StackTrace[], Traits<StackTrace>>::free(ptr_t ptr)
    // {
    //     delete ptr;
    // }
}
