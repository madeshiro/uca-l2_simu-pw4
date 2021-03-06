#include "cxx/application.h"
#include "cxx/oop/sock.h"
#include "cxx/oop/file.h"
#include "cxx/ui.h"

namespace UCA_L2INFO_PW4
{
    Application* Application::app;

    AppsArgs::AppsArgs(int argc, char **argv):
        argc(argc), argv(argv),
        options(), arguments()
    {
        options.set("gui", false);
        options.set("performExperiment", true);
        options.set("initFromFile", false);

        arguments.set("requestMale", String::ToString(100));
        arguments.set("requestFemale", String::ToString(100));
        arguments.set("runDuration", String::ToString(240));
        arguments.set("runReplication", String::ToString(30));
    }

    AppsArgs::~AppsArgs()
    {
        /* nothing */
    }

    bool AppsArgs::optionEnable(const String option) const
    {
        return options.contains(option) && *options.get(option);
    }

    bool AppsArgs::hasParameters(const String param) const
    {
        return arguments.contains(param);
    }

    bool AppsArgs::isValid() const
    {
        return !options.isEmpty();
    }

    template<>
    int AppsArgs::getArgument(const String param) const
    {
        return arguments.get(param)->toInteger();
    }

    template<>
    uint_t AppsArgs::getArgument(const String param) const
    {
        return (uint_t) arguments.get(param)->toInteger();
    }

    template<>
    String AppsArgs::getArgument(const String param) const
    {
        return *arguments.get(param);
    }

    Application::Application(int argc, char **argv, bool _main):
        appsArgs(argc, argv),
        experiment(nullptr),
        out(new Logger(new FileOutputStream(stdout, "stdout"), "Simu")),
        err(new Logger(new FileOutputStream(stderr, "stderr"), "Simu")),
        in(new FileInputStream(stdin, "stdin"))
    {
        if (_main)
            Application::app = this;

        if (appsArgs.isValid())
        {
            // Socket::sock_start_service();

            if (appsArgs.optionEnable("gui"))
            {
                interface = new WebGUI();
            }
            else
            {
                interface = new ConsoleUI();
            }
        }
        else
        {
            out->severe().println("Invalid arguments ! try `projectsi_pw4 --help` for help");
        }
    }

    Application::~Application() noexcept
    {
        // Socket::sock_stop_service();

        delete out;
        delete err;
        delete in;
        delete interface;

        if (experiment) delete experiment;
    }

    bool Application::isGuiEnable() const
    {
        return appsArgs.optionEnable("gui");
    }

    void Application::setGuiEnable(bool enable)
    {
        appsArgs.options.set("gui", enable);
    }

    const char* Application::version() const
    {
        return "1.0 PR (w/o webgui)";
    }

    AppsArgs& Application::args()
    {
        return appsArgs;
    }

    int Application::exec()
    {
        if (args().isValid())
        {
            // if (isGuiEnable())
            // {
            //     if (!openGui())
            //     {
            //         out->warning().println("Unable to start the WebGUI! Working on console.");
            //         setGuiEnable(false);
            //     }
            // }

            if (args().optionEnable("performExperiment"))
            {
                out->format("Rin Baudelet -- N2 INFO -- projectsi_pw4\n"
                            "Start program on version {0}\n"
                            "Ready to perform experiment...\n", version());

                if (args().optionEnable("initFromFile"))
                {
                    /* TODO: init from file -- version 1.0 release */
                }
                else
                {
                    if (!args().hasParameters("requestMale"))
                    {
                        ui()->requestInit();
                    }

                    int runReplication(args().getArgument<int>("runReplication"));
                    int runDuration(args().getArgument<int>("runDuration"));

                    int requestMale(args().getArgument<int>("requestMale"));
                    int requestFemale(args().getArgument<int>("requestFemale"));

                    experiment = new Experiment(runReplication, runDuration, requestMale, requestFemale);
                    ui()->connectExperiment(*experiment);
                    experiment->set_mt_key(new ulong_t[4]{0x123,0x234,0x345,0x456}, 4);

                    if (!ui()->isGraphical())
                    {
                        experiment->run();
                    }
                }
            }
            else if (args().optionEnable("exportFromExperiment"))
            {
                // Nothing to do for now
                // TODO: export data from experiment -- version 1.0 release
            }
        }
        return 0;
    }

    bool Application::openGui()
    {
        return false; // TODO: openGui()
    }

    UserInterface* Application::ui()
    {
        return interface;
    }
}