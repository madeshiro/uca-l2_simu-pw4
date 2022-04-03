#include "cxx/ui.h"

namespace UCA_L2INFO_PW4
{
    void WebGUI::requestInit()
    {

    }

    void WebGUI::connectExperiment(Experiment &exp [[gnu::unused]])
    {

    }

    bool WebGUI::isGraphical()
    {
        return true;
    }

    void ConsoleUI::requestInit()
    {

    }

    void ConsoleUI::connectExperiment(Experiment &exp [[gnu::unused]])
    {

    }

    bool ConsoleUI::isGraphical()
    {
        return false;
    }
}