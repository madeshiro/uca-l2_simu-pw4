#include "cxx/simulation/simulation.h"
#include "cxx/application.h"

using UCA_L2INFO_PW4::Application;

int main(int argc, char* argv[])
{
    Application app(argc, argv);
    if (app.isMaster())
    {

    }
    else if (app.isSlave())
    return 0;
}