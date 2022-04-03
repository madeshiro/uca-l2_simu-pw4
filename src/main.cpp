#include "cxx/application.h"

using UCA_L2INFO_PW4::Application;

int main(int argc, char* argv[])
{
    Application app(argc, argv);
    return app.exec();
}