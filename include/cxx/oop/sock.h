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
#ifndef CPP_SOCK_H
#define CPP_SOCK_H
#include "stream.h"

namespace UCA_L2INFO_PW4
{
    /* TODO Socket (version 1.0 release)
    class Socket;
    class SockOutputStream : public OutputStream
    {
        friend class Socket;
        Socket* _F_parent;
    protected:
        SockOutputStream(Socket* parent);
    public:

        void close() override;
    };

    class SockInputStream : public InputStream
    {
        friend class Socket;
        Socket* _F_parent;
    protected:
        SockInputStream(Socket* parent);
    public:

        void close() override;
    };

    class Socket
    {
        SockOutputStream*   _F_out;
        SockInputStream*    _F_in;
    public:
        static void sock_start_service();
        static void sock_stop_service();

        SockOutputStream& getOutputStream();
        SockInputStream& getInputStream();


        void close();
    };

    */
}


#endif // CPP_SOCK_H
