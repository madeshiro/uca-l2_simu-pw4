/*
 * UCA-L2 simulation "practical work #4" : a realistic simulation of rabbit population growth
 * Copyright (C) 2022 -- Rin Baudelet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef CPP_UI_H
#define CPP_UI_H
#include "application.h"

namespace UCA_L2INFO_PW4
{
    class WebGUI final : public UserInterface
    {
    public:
        WebGUI() = default;

        virtual bool displayProgression(int, int, Simulation&) override;
        virtual void requestInit() override;
        virtual void connectExperiment(Experiment& exp) override;
        virtual bool isGraphical() override;
    };

    class ConsoleUI final : public UserInterface
    {
    private delegates:
        ClassDelegate<ConsoleUI, int, int, Simulation&> display_progression;

    public:
        ConsoleUI();

        virtual bool displayProgression(int, int, Simulation&) override;
        virtual void requestInit() override;
        virtual void connectExperiment(Experiment& exp) override;
        virtual bool isGraphical() override;
    };
}

#endif //TP4_UI_H
