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

        virtual void flush() = 0;
        virtual void close() = 0;
        virtual int  seek(ulong_t pos, ulong_t whence) = 0;
    };

    class InputStream : public Object
    {
    public:
        virtual char  read() = 0;
        virtual char* read(char* __out buf, size_t size) = 0;

        virtual void close() = 0;
        virtual int  seek(ulong_t pos, ulong_t whence) = 0;
    };

    class Logger final
    {
        OutputStream* stream;
        String prefix;

        bool _F_tmp = false;
    protected:
        Logger(const Logger& log, String lvl);
    public:
        Logger(OutputStream* stream, String prefix = "logger");
        virtual ~Logger() final;

        void setPrefix(const String p);
        String& getPrefix();

        void print(String str);
        void println(String str);

        template <typename ...T>
        void format(const char* format, T...);

        char* read(char* buf, uint_t _Size);
        String readLine();

        Logger info() const;
        Logger warning() const;
        Logger severe() const;
    };

}

#endif //CPP_STREAM_H
