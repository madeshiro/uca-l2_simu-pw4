//
// Created by madeshiro on 09/03/2022.
//

#ifndef CPP_BINARY_H
#define CPP_BINARY_H

namespace UCA_L2INFO_PW4
{
    class BinaryStream
    {
    public:
        BinaryStream() = default;
    };

    class Binaries
    {
    public:
        Binaries() = default;

        virtual BinaryStream exportBinary() const = 0;
        virtual Binaries&  loadBinary(BinaryStream stream) = 0;
    };
}

#endif //CPP_BINARY_H
