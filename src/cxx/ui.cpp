#include "cxx/ui.h"

namespace UCA_L2INFO_PW4
{
    int WebGUI::server(void * args [[gnu::unused]])
    {
        return 0;
    }

    WebGUI::WebGUI():
        Thread(new ThreadClassFunction<WebGUI>(this, &WebGUI::server))
    {
        /* ... */
    }

    WebGUI::~WebGUI()
    {
        delete _F_entry;
    }

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
        out->format("Simulation {0}/{1} done !\n", cnt, exp_total);

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