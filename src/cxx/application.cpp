#include "cxx/application.h"
#include "mt19937ar.h"

namespace UCA_L2INFO_PW4
{
    Application::Application(int argc, char **argv):
    out(new Logger(new FileOutputStream(stdout))),
    err(new Logger(new FileOutputStream(stderr))),
    in(new FileInputStream(stdin))
    {
        if (master)
        {
            init_by_array((unsigned long[4]){0x123, 0x234, 0x345, 0x456}, 4);
        }
    }

    Application::~Application() noexcept
    {

    }

    bool Application::isMaster() const
    {
        return master;
    }

    bool Application::isGuiEnable() const
    {
        return gui_enable;
    }
}