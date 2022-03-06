#ifndef CPP_PACKET_H
#define CPP_PACKET_H
#include "cxx/oop/sock.h"
#include "cxx/json/json.h"

namespace UCA_L2INFO_PW4
{
    namespace serv
    {
        class Packet
        {
        protected:
            Packet() = default;
        public:
            enum Direction
            {
                IN,
                OUT
            };

            struct Header
            {
                int     packet_id;
                uint_t  size;
            };

            virtual Header getHeader() = 0;
            virtual String getContent() = 0;
        };

        namespace in
        {

        }

        namespace out
        {

        }
    }
}


#endif //CPP_PACKET_H
