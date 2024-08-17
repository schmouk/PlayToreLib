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

//#include "pltr/playing_cards/standard_cards.h"
//#include "pltr/playing_cards/unique_standard_cards_decks.h"

#include "decks.h"
#include "player.h"


//===========================================================================
class Gameplay
{
public:
    //-----   Constructors / Destructor   -----//
    Gameplay() noexcept = default;                  //!< the default empty constructor

    Gameplay(const Gameplay&) = delete;             //!< no copy constructor
    Gameplay(Gameplay&&) = delete;                  //!< no move constructor

    virtual ~Gameplay() noexcept = default;         //!< default destructor


    //-----   Accessors / Mutators   -----//
    [[nodiscard]]
    inline const int players_count() const noexcept //!< returns the number of players in game
    {
        return int(_players_list.size());
    }


    //-----   Operations   -----//
    void print_ranks() noexcept;                    //!< prints players' ranks

    void start_new_game() noexcept;                 //!< starts a new game

    void play() noexcept;                           //!< runs the whole game


private:
    //-----   Attributes   -----//
    static constexpr int _MAX_ROUNDS{ 100 };        //!< the max number of rounds to be played

    std::vector<Player> _players_list{              //!< the list of players, here with forced initialization to be of length 4
        Player("North"),
        Player("East"),
        Player("South"),
        Player("West")
    };

    BatailleDeck _game_deck{};                      //!< the deck of cards that is used to initiate the whole game
    BatailleDeck _round_deck{};                     //!< the played card during current round
    BatailleDeck _hidden_deck{};                    //!< the hidden cards when some Bataille occurs
    int          _round{ 0 };                       //!< the current round number
    bool         _players_cant_play{ false };       //!< true when involved players can't complete a round while Bataille-ing


    //-----   Operations   -----//
    const bool _ends() const noexcept;              //!< returns true if this game is completed

    void _next_round() noexcept;                    //! plays next round

};

