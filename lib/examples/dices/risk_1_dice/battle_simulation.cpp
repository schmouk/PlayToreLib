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
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <tuple>

#include "pltr/core/random.h"
#include "pltr/dices/standard_dice.h"

#include "battle_simulation.h"


//===========================================================================
//---------------------------------------------------------------------------
void BattleSimulation::print_result() noexcept
{
    // reminder: prints final results

    std::cout << std::endl << "--> Final result: ";
    if (this->_total_attacker_armies > 0) {
        std::cout << "Attacker wins with "
            << this->_total_attacker_armies
            << " left arm"
            << (this->_total_attacker_armies > 1 ? "ies" : "y");
    }
    else {
        std::cout << "Defender wins with "
            << this->_total_defender_armies
            << " left arm"
            << (this->_total_defender_armies > 1 ? "ies" : "y");
    }

    std::cout << std::endl << std::endl;

}

//---------------------------------------------------------------------------
void BattleSimulation::solve() noexcept
{
    // reminder: solves the simulated battle

    // local data
    Dice6 the_dice{ 6, 1, 1 };  // notice: only one instance of dice, later copied as many times as needed in red and blue lists

    std::vector<int> red_dices{};
    std::vector<int> blue_dices{};

    int round_involved_attacker_armies{ 0 };
    int round_involved_defender_armies{ 0 };
    int round{ 0 };

    // Simulates the battle round after round
    while (!this->_ends()) {
        // next round
        ++round;
        std::cout << std::endl << "-- Battle round #" << round << ':' << std::endl;

        std::cout << "Attacker: "
            << this->_total_attacker_armies
            << " arm"
            << (this->_total_attacker_armies > 1 ? "ies" : "y") << std::endl;

        std::cout << "Defender: "
            << this->_total_defender_armies
            << " arm"
            << (this->_total_defender_armies > 1 ? "ies" : "y") << std::endl;

        // evaluates counts of involved armies
        round_involved_attacker_armies = std::min(3, this->_total_attacker_armies);
        round_involved_defender_armies = std::min(3, this->_total_defender_armies);

        // initializes lists of red and blue dices accordingly
        red_dices.resize(round_involved_attacker_armies, 0);
        blue_dices.resize(round_involved_defender_armies, 0);

        // rolls all of them
        for (auto& dice_value : red_dices)
            dice_value = the_dice.roll();
        for (auto& dice_value : blue_dices)
            dice_value = the_dice.roll();

        // sorts lists of dices in descending order
        auto cmp_fn = [](const int left, const int right) { return left > right; };
        std::ranges::sort(red_dices, cmp_fn);
        std::ranges::sort(blue_dices, cmp_fn);

        // prints their values
        std::cout << "  Attacker dices:";
        for (int dice_value : red_dices)
            std::cout << ' ' << dice_value;
        std::cout << std::endl;

        std::cout << "  Defender dices:";
        for (int dice_value : blue_dices)
            std::cout << ' ' << dice_value;
        std::cout << std::endl;

        // compares red and blue dices one-to-one
        int red_wins{ 0 };
        int blue_wins{ 0 };
        std::cout << "          winner:";
        for (std::tuple<int&, int&> cmp_elem : std::views::zip(red_dices, blue_dices)) {
            const int red_value{ std::get<0>(cmp_elem) };
            const int blue_value{ std::get<1>(cmp_elem) };

            if (red_value > blue_value) {
                ++red_wins;
                std::cout << " A";
            }
            else {
                ++blue_wins;
                std::cout << " D";
            }
        }
        std::cout << std::endl;

        std::cout << "Attacker looses " << blue_wins << " arm" << (blue_wins > 1 ? "ies" : "y") << std::endl;
        std::cout << "Defender looses " << red_wins << " arm" << (red_wins > 1 ? "ies" : "y") << std::endl;

        this->_total_attacker_armies -= blue_wins;
        this->_total_defender_armies -= red_wins;

        //-- end of round: asks for hitting "Enter key"
        std::cout << "(hit Enter-key to get next round)";
        char key;
        while (std::cin.peek() != '\n')
            std::cin >> key;
        std::cin.ignore(1);
    }

}

//---------------------------------------------------------------------------
void BattleSimulation::start() noexcept
{
    // reminder: starts a new battle

    // At starting time, the defender owns from 1 to 10 armies
    this->_total_defender_armies = pltr::core::Random<>::urand(1, 10);

    // At starting time, the attacker owns from 1.25 to 3.0 times the defender armies count
    this->_total_attacker_armies = int(this->_total_defender_armies * pltr::core::Random<>::urand(1.25f, 3.0f));
    
    std::cout << "Attacker: "
        << this->_total_attacker_armies
        << " arm"
        << (this->_total_attacker_armies > 1 ? "ies" : "y");

    std::cout << ", Defender: "
        << this->_total_defender_armies
        << " arm"
        << (this->_total_defender_armies > 1 ? "ies" : "y");

    std::cout << std::endl << std::endl;


}

//---------------------------------------------------------------------------
const bool BattleSimulation::_ends() const noexcept
{
    // reminder: returns true if this simulation is completed

    return this->_total_attacker_armies == 0 || this->_total_defender_armies == 0;
}

//---------------------------------------------------------------------------
void BattleSimulation::_next_round() noexcept
{
    // reminder: simulates next round


}
