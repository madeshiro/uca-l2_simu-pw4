#ifndef CPP_STREAM_H
#define CPP_STREAM_H
#include "object.h"
#include "string.hpp"

namespace UCA_L2INFO_PW4
{
    class OutputStream : public Object
    {
    public:
        virtual int write(const char* buf, size_t size) = 0;

        virtual int flush() = 0;
        virtual void close() = 0;
        virtual int  seek(ulong_t pos, ulong_t whence) = 0;
    };

    class InputStream : public Object
    {
    public:
        virtual char  read() = 0;
        virtual int   read(char* buf, size_t size) = 0;

        virtual void close() = 0;
        virtual int  seek(ulong_t pos, ulong_t whence) = 0;
    };

    class Logger final
    {
        OutputStream* stream;
        String _F_prefix;

        bool _F_tmp = false;
    protected:
        Logger(const Logger& log, String lvl);
    public:
        Logger(OutputStream* stream, String prefix = "");
        virtual ~Logger() final;

        void setPrefix(const String p);
        String getPrefix() const;

        void print(String str);
        void println(String str);

        template <typename ...T>
        void format(const char* format, T... args)
        {
            print(String(format).format(args...));
        }

        Logger info() const;
        Logger warning() const;
        Logger severe() const;
    };

}

#endif //CPP_STREAM_H
