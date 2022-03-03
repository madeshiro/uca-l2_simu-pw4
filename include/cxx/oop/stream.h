#ifndef CPP_STREAM_H
#define CPP_STREAM_H
#include "object.h"

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

    class FileOutputStream : public OutputStream
    {
    protected:
        FILE* out;
    public:
        FileOutputStream(FILE*);
        virtual ~FileOutputStream();

        virtual int write(const char* buf, size_t size) override;

        virtual void flush() override;
        virtual void close() override;
        virtual int  seek(ulong_t pos, ulong_t whence) override;
    };

    class InputStream : public Object
    {
    public:
        virtual char  read() = 0;
        virtual char* read(char* __out buf, size_t size) = 0;

        virtual void close() = 0;
        virtual int  seek(ulong_t pos, ulong_t whence) = 0;
    };

    class FileInputStream : public InputStream
    {
    protected:
        FILE* in;
    public:
        FileInputStream(FILE*);
        virtual ~FileInputStream();

        virtual char  read() override;
        virtual char* read(char* __out buf, size_t size) override;

        virtual void close() override;
        virtual int  seek(ulong_t pos, ulong_t whence) override;
    };
}

#endif //CPP_STREAM_H
