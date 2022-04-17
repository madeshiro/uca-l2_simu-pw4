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
