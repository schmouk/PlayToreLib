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
#include <string>

#include "decks.h"


//===========================================================================
/* \brief the class of players. */
struct Player
{
    //-----   Attributes   -----//
    std::string  name{};                                        //!< the name of this player
    BatailleDeck own_deck{};                                    //!< the pack of cards this player currently owns
    BatailleDeck round_played_cards{};                          //!< the pack of cards this player has played during current round
    BatailleDeck hidden_played_cards{};                         //!< the pack of cards played hidden by this player during Bataille processing
    int          resigned_round{ 0 };                           //!< the round index when this player lost all cards
    bool         already_left{ false };                         //!< true if player left game during a Bataille processing
    bool         resigned{ false };                             //!< true if player left the game (at round number 'resigned_round')

    //----- Constructors / Destructor   -----//
    Player() noexcept = default;                                //!< default empty constructor

    inline Player(const std::string& name_) noexcept            //!< initialization constructor
        : name(name_)
    {
        // ensures that player's decks are empty at beginning of game
        clear_decks();
    }

    Player(const Player&) noexcept = default;                   //!< default copy constructor
    Player(Player&&) noexcept = default;                        //!< default move constructor

    virtual inline ~Player() noexcept = default;                //!< default desctructor


    //----- Operators   -----//
    Player& operator= (const Player&) noexcept = default;       //!< default copy assignment operator
    Player& operator= (Player&&) noexcept = default;            //!< default move assignment operator

    [[nodiscard]]
    inline const bool operator< (const Player& other) const noexcept  //!< less-than comparison operator
    {
        return this->get_owned_cards_count() < other.get_owned_cards_count() ||
            (this->get_owned_cards_count() == other.get_owned_cards_count() && this->resigned_round < other.resigned_round);
    }

    [[nodiscard]]
    inline const bool operator== (const Player& other) const noexcept //!< equal-to comparison operator
    {
        return this->get_owned_cards_count() == other.get_owned_cards_count() && this->resigned_round == other.resigned_round;
    }


    //-----   Operations   -----//
    inline void clear_decks() noexcept                          //!< empties the content of all decks
    {
        own_deck.clear();
        clear_round_decks();
    }

    inline void clear_round_decks() noexcept                    //!< empties the content of all decks played in rounds
    {
        round_played_cards.clear();
        hidden_played_cards.clear();
    }


    [[nodiscard]]
    inline const int get_owned_cards_count() const noexcept     //!< returns the count of cards that are owned by this player
    {
        return this->own_deck.get_current_cards_count();
    }


    [[nodiscard]]
    inline const bool owns_cards() const noexcept               //!< true if this player owns some cards
    {
        return get_owned_cards_count() > 0;
    }


    inline BatailleCards& draw_top_card()                       //!< draws the card at top of owned deck. Throws exception if player owns no card.
    {
        this->round_played_cards.insert_card(own_deck.pop_up_card());
        return this->round_played_cards[0];
    }

};
