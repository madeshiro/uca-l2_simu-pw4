#include "../../../include/cxx/oop/pointer.hpp"

namespace UCA_L2INFO_PW4
{
    template < typename T, typename _Deleter >
    SharedPointer<T, _Deleter>::SharedPointer(ptr_t ptr):
        Pointer<T, _Deleter>(ptr),
        _F_useCount(1)
    {

    }
}