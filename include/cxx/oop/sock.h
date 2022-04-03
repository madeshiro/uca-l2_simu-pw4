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
