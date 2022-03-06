#ifndef CPP_FILE_H
#define CPP_FILE_H
#include "stream.h"
#include <stdio.h>

namespace UCA_L2INFO_PW4
{
    class File : public Object
    {
        String  _F_fname;
    public:
        File(String name);
        File(const File& obj);
        virtual ~File();

        bool createNewFile();
        bool mkdir();

        bool exists() const;

        String getName() const;

        hash_t hashCode() override;
    };

    class FileInputStream : public InputStream
    {
        friend class Application;
        FileInputStream(FILE* handler = stdin, String channel = "stdin");
    protected:
        File _F_file;
        FILE* _F_handler;
    public:
        FileInputStream(File file);
        FileInputStream(const FileInputStream& obj);
        virtual ~FileInputStream();

        virtual char  read() override;
        virtual char* read(char* __out buf, size_t size) override;

        virtual void close() override;
        virtual int  seek(ulong_t pos, ulong_t whence) override;

        virtual File getFile() const final;
    };

    class FileOutputStream : public OutputStream
    {
        friend class Application;
        FileOutputStream(FILE* handler = stdout, String channel = "stdout");
    protected:
        File out;
        FILE* _F_handler;
    public:
        FileOutputStream(File file);
        FileOutputStream(const FileOutputStream& obj);
        virtual ~FileOutputStream();

        virtual int write(const char* buf, size_t size) override;

        virtual void flush() override;
        virtual void close() override;
        virtual int  seek(ulong_t pos, ulong_t whence) override;

        virtual File getFile() const final;
    };
}

#endif //CPP_FILE_H
