#include "cxx/application.h"
#include "mt19937ar.h"
#include "cxx/oop/sock.h"
#include "cxx/oop/file.h"

namespace UCA_L2INFO_PW4
{
    Application::Application(int argc, char **argv):
        appsArgs(argc, argv),
        out(new Logger(new FileOutputStream(stdout, "stdout"))),
        err(new Logger(new FileOutputStream(stderr, "stderr"))),
        in(new FileInputStream(stdin, "stdin"))
    {
        if (appsArgs.isValid())
        {
            if (master)
            {
                init_by_array((unsigned long[4]) {0x123, 0x234, 0x345, 0x456}, 4);
            }

            Socket::sock_start_service();
        }
        else
        {
            out->severe().println("Invalid arguments ! try `projectsi_pw4 --help` for help");
        }
    }

    Application::~Application() noexcept
    {
        Socket::sock_stop_service();
    }

    bool Application::isMaster() const
    {
        return appsArgs.optionEnable("master");
    }

    bool Application::isSlave() const
    {
        return appsArgs.optionEnable("slave");
    }

    bool Application::isGuiEnable() const
    {
        return appsArgs.optionEnable("gui");
    }
}