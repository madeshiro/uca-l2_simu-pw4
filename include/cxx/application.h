#ifndef CPP_APPLICATION_H
#define CPP_APPLICATION_H
#include "defines.h"
#include "cxx/oop/container.hpp"
#include "cxx/oop/exception.h"
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
            std::string arg(int index) throw(IndexOutOfBoundException)
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
    };

    class Logger final
    {
        OutputStream* stream;
        String prefix;
    public:
        Logger(OutputStream* stream);
        virtual ~Logger() final;

        void setPrefix(const String prefix);
        String& getPrefix();

        void print(String str);
        void println(String str);

        template <typename ...T>
        void format(const char* format, T...);

        char* read(char* buf, uint_t _Size);
        String readLine();
    };

    class Application final
    {
        bool master;
        bool gui_enable;
    public:
        Logger      const * const out;
        Logger      const * const err;
        InputStream const * const in;


        Application(int argc, char* argv[]);
        virtual ~Application() noexcept final;

        double* draw(ulong_t amount) noexcept;

        bool isMaster() const;
        bool isGuiEnable() const;
    };
}

#endif //CPP_APPLICATION_H
