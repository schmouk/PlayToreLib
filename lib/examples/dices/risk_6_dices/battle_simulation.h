#pragma once
/*
    GNU GENERAL PUBLIC LICENSE
    Version 3, 29 June 2007

    This is part of library PlayToreLib, a c++ generic library for coding games applications.

    Copyright (C) 2024 Philippe Schmouker, ph.schmouker (at) gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


//===========================================================================
#include <vector>

#include "pltr/dices/standard_dice.h"


//===========================================================================
class BattleSimulation
{
public:
    //-----   Constructors / Destructor   -----//
    BattleSimulation() noexcept = default;                  //!< the default empty constructor

    BattleSimulation(const BattleSimulation&) = delete;     //!< no copy constructor
    BattleSimulation(BattleSimulation&&) = delete;          //!< no move constructor

    virtual ~BattleSimulation() noexcept = default;         //!< default destructor


    //-----   Operations   -----//
    void print_result() noexcept;                           //!< prints final result

    void solve() noexcept;                                  //!< solves the simulated battle

    void start() noexcept;                                  //!< starts a new battle


private:
    //-----   Types   -----//
    using Dice6 = pltr::dices::StandardDice<int>;


    //-----   Attributes   -----//
    int _total_attacker_armies{ 0 };
    int _total_defender_armies{ 0 };


    //-----   Operations   -----//
    [[nodiscard]]
    const bool _ends() const noexcept;  //!< returns true if this simulation is completed

    void _next_round() noexcept;        //!< simulates next round

};
