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

    bool WebGUI::displayProgression(int, int, Simulation &)
    {
        return false;
    }

    ConsoleUI::ConsoleUI():
        display_progression(*this, &ConsoleUI::displayProgression, 0x2)
    {
        Application::app->out->println("ConsoleUI Initialize !");
    }

    bool ConsoleUI::displayProgression(int cnt, int exp_total, Simulation & sim)
    {
        Logger* out(Application::app->out);
        out->format("Simulation {0}/{1} done !\n");

        return true;
    }

    void ConsoleUI::requestInit()
    {
        /* Nothing to do here for now */
    }

    void ConsoleUI::connectExperiment(Experiment &exp)
    {
        exp.on_simulation_end.connect(&display_progression);
    }

    bool ConsoleUI::isGraphical()
    {
        return false;
    }
}