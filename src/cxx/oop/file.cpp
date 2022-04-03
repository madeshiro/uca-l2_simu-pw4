#include "cxx/oop/file.h"
#include <filesystem>

namespace UCA_L2INFO_PW4
{
    File::File(String name): _F_fname(name)
    {}

    File::File(const File &obj): _F_fname(obj._F_fname)
    {}

    bool File::createNewFile()
    {
        FILE* f = fopen(_F_fname.getCharSequence(), "w+");
        if (f)
        {
            fclose(f);
            return true;
        }
        else
        {
            return false;
        }
    }

    bool File::mkdir()
    {
        return std::filesystem::create_directories(_F_fname.getCharSequence());
    }

    bool File::exists() const
    {
        FILE* f = fopen(_F_fname.getCharSequence(), "r");
        if (f)
        {
            fclose(f);
            return true;
        }
        else
        {
            return false;
        }
    }

    String File::getName() const
    {
        return _F_fname;
    }

    hash_t File::hashCode() const
    {
        return _F_fname.hashCode();
    }

    bool File::trunc()
    {
        FILE* truncate = fopen(_F_fname.getCharSequence(), "w+");
        if (truncate)
        {
            fclose(truncate);
            return true;
        }
        else
        {
            return false;
        }
    }

    FileInputStream::FileInputStream(FILE *handler, String channel): _F_file(channel), _F_handler(handler)
    { /* ... */ }

    FileInputStream::FileInputStream(File file): _F_file(file),
        _F_handler(fopen(file.getName().getCharSequence(), "r"))
    { /* ... */ }

    FileInputStream::FileInputStream(const FileInputStream &obj):
        _F_file(obj._F_file), _F_handler(obj._F_handler)
    { /* ... */ }

    char FileInputStream::read()
    {
        char c = -1;
        fread(&c, sizeof(char), 1, _F_handler);
        return c;
    }

    int FileInputStream::read(char *buf, size_t size)
    {
        return (int) fread(buf, sizeof(char), size, _F_handler);
    }

    void FileInputStream::close()
    {
        fclose(_F_handler);
    }

    int FileInputStream::seek(ulong_t off, ulong_t whence)
    {
        return fseek(_F_handler, off, whence);
    }

    File FileInputStream::getFile() const
    {
        return _F_file;
    }

    FileInputStream::operator FILE*()
    {
        return _F_handler;
    }

    FileOutputStream::FileOutputStream(FILE *handler, String channel):
        _F_file(channel), _F_handler(handler)
    {
        /* ... */
    }

    FileOutputStream::FileOutputStream(File file):
        _F_file(file), _F_handler(fopen(file.getName().getCharSequence(), "a"))
    {
        /* ... */
    }

    FileOutputStream::FileOutputStream(const FileOutputStream &obj):
        _F_file(obj._F_file), _F_handler(obj._F_handler)
    {
        /* ... */
    }

    int FileOutputStream::write(const char *buf, size_t size)
    {
        return (int) fwrite(buf, sizeof(char), size, _F_handler);
    }

    int FileOutputStream::flush()
    {
        return fflush(_F_handler);
    }

    void FileOutputStream::close()
    {
        fclose(_F_handler);
    }

    int FileOutputStream::seek(ulong_t off, ulong_t whence)
    {
        return fseek(_F_handler, off, whence);
    }

    File FileOutputStream::getFile() const
    {
        return _F_file;
    }

    FileOutputStream::operator FILE*()
    {
        return _F_handler;
    }
}