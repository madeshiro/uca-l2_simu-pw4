/*
 * UCA-L2 simulation "practical work #4" : a realistic simulation of rabbit population growth
 * Copyright (C) 2022 -- Rin Baudelet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
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
        virtual ~File() override = default;

        bool createNewFile();
        bool mkdir();

        bool exists() const;
        bool trunc();

        String getName() const;

        hash_t hashCode() const override;
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
        virtual ~FileInputStream() = default;

        virtual char read() override;
        virtual int  read(char* buf, size_t size) override;

        virtual void close() override;
        virtual int  seek(ulong_t off, ulong_t whence) override;

        virtual File getFile() const final;

        operator FILE*();
    };

    class FileOutputStream : public OutputStream
    {
        friend class Application;
        FileOutputStream(FILE* handler = stdout, String channel = "stdout");
    protected:
        File _F_file;
        FILE* _F_handler;
    public:
        FileOutputStream(File file);
        FileOutputStream(const FileOutputStream& obj);
        virtual ~FileOutputStream() = default;

        virtual int write(const char* buf, size_t size) override;

        virtual int flush() override;
        virtual void close() override;
        virtual int  seek(ulong_t off, ulong_t whence) override;

        virtual File getFile() const final;

        operator FILE*();
    };
}

#endif //CPP_FILE_H
