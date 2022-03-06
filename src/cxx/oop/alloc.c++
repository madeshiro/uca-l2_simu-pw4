namespace UCA_L2INFO_PW4
{
    template<typename T, typename _Traits>
    void Delete<T, _Traits>::free(ptr_t ptr)
    {
        delete ptr;
    }

    template<typename T, typename _Traits>
    void Delete<T[], _Traits>::free(ptr_t ptr)
    {
        delete[] ptr;
    }
}
