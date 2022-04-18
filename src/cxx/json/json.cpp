#include "cxx/json/json.h"

namespace UCA_L2INFO_PW4
{
    namespace json
    {
        JsonInvalidType::JsonInvalidType(): Exception()
        {/*...*/}

        JsonInvalidType::JsonInvalidType(String msg): Exception(msg)
        {/*...*/}

        JsonInvalidType::JsonInvalidType(String msg, String file, String function, int line):
            Exception(msg, file, function, line)
        {/*...*/}

        JsonInvalidType::JsonInvalidType(const JsonInvalidType &ex): Exception(ex)
        {/*...*/}

        String JsonInvalidType::getName() const
        {
            return "JsonInvalidType";
        }
    }
}