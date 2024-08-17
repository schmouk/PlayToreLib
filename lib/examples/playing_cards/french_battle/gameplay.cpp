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

#include "gameplay.h"


//===========================================================================
//---------------------------------------------------------------------------
void Gameplay::play() noexcept
{
    // reminder: runs the whole game
    while (!_ends()) {
        _next_round();
    }
}

//---------------------------------------------------------------------------
void Gameplay::print_ranks() noexcept
{
    // reminder: prints players' ranks
    std::cout << std::endl << "Final Rankings:" << std::endl;

    std::ranges::sort(this->_players_list, [](const Player& left, const Player& right) { return left < right; });
    std::ranges::reverse(this->_players_list);

    Player player{ this->_players_list[0] };
    std::cout << "  1. " << player.name << " - " << player.get_owned_cards_count() << " card";
    if (player.get_owned_cards_count() > 1)
        std::cout << 's';
    std::cout << std::endl;

    int prev_rank{ 1 };
    int rank{ 2 };
    Player prev_player{ player };

    for (int i = 1; i < this->_players_list.size(); rank++, ++i) {
        player = this->_players_list[i];

        if (player == prev_player) {
            std::cout << "  " << prev_rank;
        }
        else {
            std::cout << "  " << rank;
            prev_rank = rank;
        }
        std::cout << ". " << player.name << " - " << player.get_owned_cards_count();

        if (player.owns_cards()) {
            std::cout << " card";
            if (player.get_owned_cards_count() > 1)
                std::cout << 's';
        }

        if (player.resigned)
            std::cout << " (" << player.resigned_round << " rounds)";

        std::cout << std::endl;

        prev_player = player;
    }

}

//---------------------------------------------------------------------------
void Gameplay::start_new_game() noexcept
{
    // reminder: intializes a new game

    // empties players' decks
    for (Player& player : this->_players_list)
        player.clear_decks();

    // refills and shuffles the game cards deck
    std::cout << "let's shuffle the deck of cards..." << std::endl;
    this->_game_deck.refill_deck();
    this->_game_deck.shuffle();

    // distributes all cards to players
    std::cout << "distributing cards to players..." << std::endl;
    int player_index{ 0 };
    for (auto& card : this->_game_deck.deck()) {
        this->_players_list[player_index++].own_deck.insert_card(card);

        if (player_index >= players_count())
            player_index = 0;
    }
}

//---------------------------------------------------------------------------
const bool Gameplay::_ends() const noexcept
{
    // reminder: returns true if this game is completed
    if (this->_round == this->_MAX_ROUNDS)
        // all rounfs completed!
        return true;

    if (std::ranges::any_of(this->_players_list,
        [this](const Player& p) {
            return p.get_owned_cards_count() == this->_game_deck.get_max_cards_count();
        })
        )
        // one of the players owns all the original deck cards!
        return true;

    // then, game ends if, during a "Bataille" step, involved players can't play any more cards
    return this->_players_cant_play;

}


//---------------------------------------------------------------------------
void Gameplay::_next_round() noexcept
{
    // reminder: plays next round

    ++this->_round;
    std::cout << std::endl << "-- round #" << this->_round << ':' << std::endl;

    this->_round_deck.clear();
    this->_hidden_deck.clear();


    //-- players draw their top-deck card
    int highest_value{ -1 };
    std::vector<Player*> winners{};
    winners.reserve(4);

    for (Player& player : this->_players_list) {
        if (player.owns_cards()) {
            // empties the list of played cards in round
            player.clear_round_decks();

            // plays top card in owned deck
            const BatailleCards played_card{ player.draw_top_card() };
            this->_round_deck.insert_card(played_card);

            std::cout << player.name << ": " << played_card.text << ",  ";

            // checks highest value of played cards
            if (int(played_card.value) > highest_value) {
                highest_value = int(played_card.value);
                winners.clear();
                winners.push_back(&player);
            }
            else if (int(played_card.value) == highest_value) {
                winners.push_back(&player);
            }
        }
    }
    std::cout << std::endl;


    //-- checks Bataille
    while (winners.size() > 1) {
        // Bataille!
        // only winners keep on playing this round
        std::cout << "Bataille!" << std::endl;
        
        // is there any player that can draw two cards?
        if (std::ranges::any_of(winners, [](const Player* p) { return p->get_owned_cards_count() >= 2; })) {
            int new_highest_value{ -1 };
            std::vector<Player*> new_winners{};
            new_winners.reserve(4);

            // yes, let all players play one more card face down, if they can
            int n{ 1 };
            for (Player* player : winners) {
                if (player->owns_cards()) {
                    const BatailleCards hidden_card{ player->draw_top_card() };
                    this->_hidden_deck.insert_card(hidden_card);
                    player->hidden_played_cards.insert_card(hidden_card);
                    std::cout << player->name << ": xx";
                }
                else {
                    // this player can't play
                    std::cout << player->name << ": leaves";
                    player->already_left = true;
                    player->resigned_round = this->_round;
                }

                if (n < winners.size())
                    std::cout << ",  ";
                n++;

            }
            std::cout << std::endl;

            // then, let players play a second card face up, if they can
            n = 1;
            for (Player* player : winners) {
                if (player->owns_cards()) {
                    const BatailleCards played_card{ player->draw_top_card() };
                    this->_round_deck.insert_card(played_card);

                    std::cout << player->name << ": " << played_card.text;

                    // checks highest value of played cards
                    if (int(played_card.value) > new_highest_value) {
                        new_highest_value = int(played_card.value);
                        new_winners.clear();
                        new_winners.push_back(player);
                    }
                    else if (int(played_card.value) == new_highest_value) {
                        new_winners.push_back(player);
                    }
                }
                else {
                    // this player can't play, she leaves the game
                    if (!player->already_left) {
                        std::cout << player->name << ": leaves";
                        player->already_left = true;
                        player->resigned_round = this->_round;
                    }
                }

                if (n < winners.size())
                    std::cout << ",  ";
                n++;
            }
            std::cout << std::endl;

            // finally, prepares next step of loop
            winners = new_winners;

        }
        else {
            // no player can draw two cards, so is there any player that can draw one more card?
            if (std::ranges::any_of(winners, [](const Player* p) { return p->get_owned_cards_count() >= 1; })) {
                // yes, let all players play one more card face up, if they can
                int new_highest_value{ -1 };
                std::vector<Player*> new_winners{};
                new_winners.reserve(4);

                int n{ 1 };
                for (Player* player : winners) {
                    if (player->owns_cards()) {
                        const BatailleCards played_card{ player->draw_top_card() };
                        this->_round_deck.insert_card(played_card);

                        std::cout << player->name << ": " << played_card.text;

                        // checks highest value of played cards
                        if (int(played_card.value) > new_highest_value) {
                            new_highest_value = int(played_card.value);
                            new_winners.clear();
                            new_winners.push_back(player);
                        }
                        else if (int(played_card.value) == new_highest_value) {
                            new_winners.push_back(player);
                        }
                    }
                    else {
                        // this player can't play, she meaves the game
                        std::cout << player->name << ": leaves";
                        player->already_left = true;
                        player->resigned_round = this->_round;
                    }

                    if (n < this->_players_list.size())
                        std::cout << ",  ";
                    n++;
                }
                std::cout << std::endl;

                // finally, prepare next step of loop
                winners = new_winners;

            }
            else {
                // no player can play any card during this Bataille, so game has completed!
                this->_players_cant_play = true;  // this sets the return value of method _ends() to true also

                // puts back played cards to their original owners
                for (Player& player : this->_players_list)
                    player.own_deck += player.round_played_cards;
            }
        }
    }

    //-- finally, one single round winner
    if (!this->_players_cant_play) {
        // well, finally only one winner in this round

        // if Bataille occured, show played hidden cards
        if (!this->_hidden_deck.is_empty()) {
            std::cout << "> hidden cards played";

            for (Player& player : this->_players_list) {
                if (!player.hidden_played_cards.is_empty()) {
                    std::cout << " - " << player.name << ":";
                    for (const BatailleCards& card : player.hidden_played_cards.deck()) {
                        std::cout << ' ' << card.text;
                    }
                }
            }
            std::cout << std::endl;
        }

        Player* winner{ winners[0] };
        std::cout << "!" << winner->name << " wins!" << std::endl;

        // shuffles the won cards
        this->_round_deck += this->_hidden_deck;
        this->_round_deck.shuffle();

        // and adds them at end of the winner own deck
        winner->own_deck += this->_round_deck;
    }


    //-- if game has not completed, prints each player's status
    if (_ends()) {
        std::cout << "-- Game has completed!" << std::endl;
    }
    else {
        std::cout << std::endl;
        int n{ 1 };
        for (auto& player : this->_players_list) {
            const int cards_count{ player.get_owned_cards_count() };
            std::cout << player.name << ": " << cards_count << " card";
            if (cards_count > 1)
                std::cout << 's';

            if (cards_count == 0) {
                if (!player.resigned) {
                    player.resigned_round = this->_round;
                    player.resigned = true;
                    player.clear_round_decks();
                }
                std::cout << " (" << player.resigned_round << " rounds)";
            }

            if (n < this->_players_list.size())
                std::cout << ",  ";
            n++;
        }
        std::cout << std::endl;

        //-- end of round: asks for hitting "Enter key"
        std::cout << "(hit Enter-key)";
        char key;
        while (std::cin.peek() != '\n')
            std::cin >> key;
        std::cin.ignore(1);
    }

}
