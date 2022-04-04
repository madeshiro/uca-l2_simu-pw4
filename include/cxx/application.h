#ifndef CPP_APPLICATION_H
#define CPP_APPLICATION_H
#include "defines.h"
#include "cxx/oop/container.hpp"
#include "cxx/oop/exception.h"
#include "cxx/oop/stream.h"
#include "mt19937ar.h"
#include "cxx/simulation/experiment.h"

namespace UCA_L2INFO_PW4
{
    class AppsArgs final
    {
        friend class Application;
        friend class UserInterface;

        int argc;
        char ** argv;

        HashMap<String, bool> options;
        HashMap<String, String> arguments;
    public:
        struct ArgsNode
        {
            String label;
            ArrayList<String> args;
        };

        AppsArgs(int argc, char* argv[]);
        virtual ~AppsArgs() final;

        bool isValid() const;

        bool optionEnable(const String option) const;
        bool hasParameters(const String param) const;

        template <typename T>
        T getArgument(const String param) const;
    };

    class UserInterface
    {
    public:
        virtual ~UserInterface() = default;

        virtual void requestInit() = 0;
        virtual void connectExperiment(Experiment& exp) = 0;
        virtual bool isGraphical() = 0;
        virtual bool displayProgression(int, int, Simulation&) = 0;
    };

    class Application final
    {
        AppsArgs appsArgs;
        Experiment *experiment;
    public:
        static Application* app;

        Logger      * const out;
        Logger      * const err;
        InputStream * const in;

        UserInterface * interface;

        Application(int argc, char* argv[], bool _main = true);
        virtual ~Application() noexcept final;

        bool isGuiEnable() const;
        void setGuiEnable(bool enable);

        const char* version() const;
        AppsArgs& args();
        int exec();

        bool openGui();
        UserInterface* ui();
    };
}

#endif //CPP_APPLICATION_H
