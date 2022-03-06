#ifndef CPP_APPLICATION_H
#define CPP_APPLICATION_H
#include "defines.h"
#include "cxx/oop/container.hpp"
#include "cxx/oop/exception.h"
#include "cxx/oop/stream.h"
#include <string>

namespace UCA_L2INFO_PW4
{
    class AppsArgs
    {
        int argc;
        char * argv[];
    public:
        struct ArgsNode
        {
            String label;
            ArrayList<String> args;

            template <typename T>
            T arg(int index) throw(IndexOutOfBoundException)
            {/*...*/}

            template<>
            String arg(int index) throw(IndexOutOfBoundException)
            {
                return args[index];
            }

            template<>
            uint_t arg(int index) throw(IndexOutOfBoundException)
            {

            }
        };

        AppsArgs(int argc, char* argv[]);
        virtual ~AppsArgs() final;

        bool isValid() const;

        bool optionEnable(const String option) const;
    };

    class Application final
    {
        AppsArgs appsArgs;
    public:
        const Logger      * const out;
        const Logger      * const err;
        const InputStream * const in;


        Application(int argc, char* argv[]);
        virtual ~Application() noexcept final;

        double* draw(ulong_t amount) noexcept;

        bool isMaster() const;
        bool isSlave() const;
        bool isGuiEnable() const;
    };
}

#endif //CPP_APPLICATION_H
