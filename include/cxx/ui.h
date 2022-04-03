#ifndef CPP_UI_H
#define CPP_UI_H
#include "application.h"

namespace UCA_L2INFO_PW4
{
    class WebGUI final : public UserInterface
    {
        virtual void requestInit() override;
        virtual void connectExperiment(Experiment& exp) override;
        virtual bool isGraphical() override;
    };

    class ConsoleUI final : public UserInterface
    {
        virtual void requestInit() override;
        virtual void connectExperiment(Experiment& exp) override;
        virtual bool isGraphical() override;
    };
}

#endif //TP4_UI_H
