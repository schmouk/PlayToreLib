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
/*
* Risk is a strategy board game from editor Hasbro.
* We propose here an implementation of the battles resolution algorithm
* of this game as an example of use of package `pltr/dice` of library
* PlayTore.
*
* Rules of battles resolution:
* Two opponents are involved in battles, the attacker and the defender.
* The attacker attacks with as many armies as she gets (minus one) in a
* territory she owns.  The defender defends with as many armies she owns
* in the attacked territory. Battles are solved per iterative rounds. At
* each round the attacker may attack with at most three of her armies, 
* at her will and if she gets three or more available armies for this
* attack, and the defender defends with at most three owned armies also
* unless there are less than three army left in the attacked territory.
* 
* The attacker rolls as many 6-faces standard dices (the red ones) as 
* she gets involved armies in the current battle round, and at most
* three of them. The defender rolls then as any 6-faces standard dices
* (the blue ones) as she gets involved armies in the current battle 
* round, and at most three of them.
* 
* Red dices are then ordered in their descending values, as are the blue
* ones also. Values are then compared one-to-one, the highest red value 
* with the highest blue value, the next red value with the next blue
* value if enough dices have been rolled, and the lowest values then if
* three dices have been rolled by each opponent.
* Whe a red and a blue dice values are compared, the bigger wins and the
* opponent player looses one army in its owned territory. Deuces are in
* favor of the defender.
* 
* The battle ends when the attacker decides to stop her attack or when an
* opponent has lost all of her available armies. 
* 
* For this example, we use the next hypothesis. Their purpose is just to
* set starting and ending conditions for the code of this example.
* 
* - At starting time, the defender owns from 1 to 10 armies, a number 
*   that is selected at random with a uniform distribution function;
* - At starting time, the attacker owns from 1.25 to 3.0 times the 
*   defender armies count, a factor selected at random with uniform 
*   distribution;
* - At ach battle round, the attacker attacks with as much armies as 
*   she can and with at most 3 armies;
* - At each battle round, the defender defends with as much armies as
*   she can and with at most 3 armies.
* - The battle ends when an opponent gets no more available army for 
*   attacking or for defending.
*
* Notice: this code uses c++20 standard and some of  its  new  concepts.
* We hope this will be of interest to you, and that it will help you get
* more informed on these concepts.
*/

//===========================================================================
#include <iostream>

#include "battle_simulation.h"


//===========================================================================
int main()
{
    std::cout << "RISK battle simulation" << std::endl << std::endl;

    BattleSimulation the_battle;

    // starts a new battle
    the_battle.start();

    // runs through successive rounds
    the_battle.solve();

    // prints results
    the_battle.print_result();

    // bye bye!
    std::cout << std::endl << "Bye bye!" << std::endl << std::endl;

    // end of application
    return 0;
}
