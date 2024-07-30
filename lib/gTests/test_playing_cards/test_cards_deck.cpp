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
#include "gtest/gtest.h"

#include "playing_cards/cards_deck.h"
#include "playing_cards/playing_cards.h"


//===========================================================================
TEST(TestSuitePlayingCards, TestCardsDeck) {

    using DefaultCardT = pltr::cards::PlayingCardT<>;
    using DefaultDeckT = pltr::cards::CardsDeck<DefaultCardT>;

    // creates a empty test deck of cards and accessors
    DefaultDeckT empty_deck(15);

    EXPECT_EQ(0, empty_deck.get_current_cards_count());
    EXPECT_EQ(15, empty_deck.get_max_cards_count());
    EXPECT_EQ(0, empty_deck.deck().size());
    EXPECT_EQ(15, empty_deck.deck().capacity());

    // tests constructor with vector initialization and accessors
    DefaultDeckT::CardsList init_vect{
        DefaultCardT(1),
        DefaultCardT(2),
        DefaultCardT(3)
    };

    DefaultDeckT deck3(init_vect);

    EXPECT_EQ(3, deck3.get_current_cards_count());
    EXPECT_EQ(3, deck3.get_max_cards_count());
    EXPECT_EQ(3, deck3.deck().size());
    EXPECT_EQ(3, deck3.deck().capacity());

    EXPECT_EQ(1, deck3[0].ident);
    EXPECT_EQ(2, deck3[1].ident);
    EXPECT_EQ(3, deck3[2].ident);

    // tests constructor with initalization list
    DefaultDeckT deck33({ DefaultCardT(1), DefaultCardT(2), DefaultCardT(3) });

    EXPECT_EQ(3, deck33.get_current_cards_count());
    EXPECT_EQ(3, deck33.get_max_cards_count());
    EXPECT_EQ(3, deck33.deck().size());
    EXPECT_EQ(3, deck33.deck().capacity());

    EXPECT_EQ(1, deck33[0].ident);
    EXPECT_EQ(2, deck33[1].ident);
    EXPECT_EQ(3, deck33[2].ident);

    // tests constructor with variable count args and accessors...
    constexpr int CARDS_MAX_COUNT{ 5 };
    DefaultDeckT deck4(CARDS_MAX_COUNT, DefaultCardT(1), DefaultCardT(2), DefaultCardT(3), DefaultCardT(4));

    EXPECT_EQ(4, deck4.get_current_cards_count());
    EXPECT_EQ(CARDS_MAX_COUNT, deck4.get_max_cards_count());
    EXPECT_EQ(4, deck4.deck().size());
    EXPECT_EQ(CARDS_MAX_COUNT, deck4.deck().capacity());

    // ...and tests operator []
    EXPECT_EQ(1, deck4[0].ident);
    EXPECT_EQ(2, deck4[1].ident);
    EXPECT_EQ(3, deck4[2].ident);
    EXPECT_EQ(4, deck4[3].ident);

    // tests appending one card within max allocated space
    deck4.append_card(DefaultCardT(5));

    EXPECT_EQ(5, deck4.get_current_cards_count());
    EXPECT_EQ(CARDS_MAX_COUNT, deck4.get_max_cards_count());
    EXPECT_EQ(5, deck4.deck().size());
    EXPECT_EQ(CARDS_MAX_COUNT, deck4.deck().capacity());

    EXPECT_EQ(1, deck4[0].ident);
    EXPECT_EQ(2, deck4[1].ident);
    EXPECT_EQ(3, deck4[2].ident);
    EXPECT_EQ(4, deck4[3].ident);
    EXPECT_EQ(5, deck4[4].ident);

    // tests appending one card above max allocated space
    deck4.append_card(DefaultCardT(6));

    EXPECT_EQ(6, deck4.get_current_cards_count());
    EXPECT_EQ(6, deck4.get_max_cards_count());
    EXPECT_EQ(6, deck4.deck().size());
    EXPECT_EQ(6, deck4.get_max_cards_count());
    EXPECT_LE(deck4.get_max_cards_count(), deck4.deck().capacity());  // notice: set to 7, not to 6 - might be STL implementation dependant...

    EXPECT_EQ(1, deck4[0].ident);
    EXPECT_EQ(2, deck4[1].ident);
    EXPECT_EQ(3, deck4[2].ident);
    EXPECT_EQ(4, deck4[3].ident);
    EXPECT_EQ(5, deck4[4].ident);
    EXPECT_EQ(6, deck4[5].ident);

    // tests appending n cards until the max allowed count of cards
    DefaultDeckT deck3bis(CARDS_MAX_COUNT, DefaultCardT(1), DefaultCardT(2), DefaultCardT(3));

    deck3bis.append_cards({ DefaultCardT(4), DefaultCardT(5) });

    EXPECT_EQ(5, deck3bis.get_current_cards_count());
    EXPECT_EQ(CARDS_MAX_COUNT, deck3bis.get_max_cards_count());
    EXPECT_EQ(5, deck3bis.deck().size());
    EXPECT_EQ(CARDS_MAX_COUNT, deck3bis.deck().capacity());

    EXPECT_EQ(1, deck3bis[0].ident);
    EXPECT_EQ(2, deck3bis[1].ident);
    EXPECT_EQ(3, deck3bis[2].ident);
    EXPECT_EQ(4, deck3bis[3].ident);
    EXPECT_EQ(5, deck3bis[4].ident);

    // tests appending n cards above the max allowed count of cards
    deck3bis = DefaultDeckT(CARDS_MAX_COUNT, DefaultCardT(1), DefaultCardT(2), DefaultCardT(3));
    deck3bis.append_cards({ DefaultCardT(14), DefaultCardT(15), DefaultCardT(16) });

    EXPECT_EQ(6, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(6, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    EXPECT_EQ(1, deck3bis[0].ident);
    EXPECT_EQ(2, deck3bis[1].ident);
    EXPECT_EQ(3, deck3bis[2].ident);
    EXPECT_EQ(14, deck3bis[3].ident);
    EXPECT_EQ(15, deck3bis[4].ident);
    EXPECT_EQ(16, deck3bis[5].ident);

    // tests drawing top card
    DefaultCardT card{ deck3bis.draw_card() };

    EXPECT_EQ(1, card.ident);

    EXPECT_EQ(5, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(5, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    EXPECT_EQ(2, deck3bis[0].ident);
    EXPECT_EQ(3, deck3bis[1].ident);
    EXPECT_EQ(14, deck3bis[2].ident);
    EXPECT_EQ(15, deck3bis[3].ident);
    EXPECT_EQ(16, deck3bis[4].ident);

    // tests drawing n top cards
    DefaultDeckT::CardsList drawn_cards{ deck3bis.draw_n_cards(2) };

    EXPECT_EQ(2, drawn_cards[0].ident);
    EXPECT_EQ(3, drawn_cards[1].ident);

    EXPECT_EQ(3, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(3, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    EXPECT_EQ(14, deck3bis[0].ident);
    EXPECT_EQ(15, deck3bis[1].ident);
    EXPECT_EQ(16, deck3bis[2].ident);

    // tests drawing the n-th card
    card = deck3bis.draw_nth_card(1);

    EXPECT_EQ(15, card.ident);
    EXPECT_EQ(2, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(2, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(14, deck3bis[0].ident);
    EXPECT_EQ(16, deck3bis[1].ident);

    deck3bis.append_cards({ DefaultCardT(1), DefaultCardT(2), DefaultCardT(3) });

    card = deck3bis.draw_nth_card(6);
    EXPECT_EQ(3, card.ident);
    EXPECT_EQ(4, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(4, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    card = deck3bis.draw_nth_card(3);
    EXPECT_EQ(2, card.ident);
    EXPECT_EQ(3, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(3, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    card = deck3bis.draw_nth_card(0);
    EXPECT_EQ(14, card.ident);
    EXPECT_EQ(2, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(2, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    card = deck3bis.draw_nth_card(0);
    EXPECT_EQ(16, card.ident);
    EXPECT_EQ(1, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(1, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    card = deck3bis.draw_nth_card(0);
    EXPECT_EQ(1, card.ident);
    EXPECT_EQ(0, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(0, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    // tests random drawing of cards
    deck3bis.append_cards({ DefaultCardT(1), DefaultCardT(2), DefaultCardT(3) });

    card = deck3bis.draw_rand_card();
    EXPECT_EQ(2, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(2, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    for (int i = 0; i < 2; ++i)
        EXPECT_NE(card.ident, deck3bis[i].ident);

    card = deck3bis.draw_rand_card();
    EXPECT_EQ(1, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(1, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_NE(card.ident, deck3bis[0].ident);

    card = deck3bis.draw_rand_card();
    EXPECT_EQ(0, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(0, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    // tests inserting no card
    deck3bis.insert_cards();

    EXPECT_EQ(0, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(0, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());

    // tests inserting one card
    deck3bis.insert_card(DefaultCardT(21));
    EXPECT_EQ(1, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(1, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(21, deck3bis[0].ident);

    deck3bis.insert_card(DefaultCardT(22));
    EXPECT_EQ(2, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(2, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(22, deck3bis[0].ident);
    EXPECT_EQ(21, deck3bis[1].ident);

    // tests inserting a variable length list of cards
    deck3bis.insert_cards(DefaultCardT(23), DefaultCardT(24), DefaultCardT(25), DefaultCardT(26));
    EXPECT_EQ(6, deck3bis.get_current_cards_count());
    EXPECT_EQ(6, deck3bis.get_max_cards_count());
    EXPECT_EQ(6, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(23, deck3bis[0].ident);
    EXPECT_EQ(24, deck3bis[1].ident);
    EXPECT_EQ(25, deck3bis[2].ident);
    EXPECT_EQ(26, deck3bis[3].ident);
    EXPECT_EQ(22, deck3bis[4].ident);
    EXPECT_EQ(21, deck3bis[5].ident);

    // tests inserting an initializing list of cards
    deck3bis.insert_cards({ DefaultCardT(31), DefaultCardT(32), DefaultCardT(33) });
    EXPECT_EQ(9, deck3bis.get_current_cards_count());
    EXPECT_EQ(9, deck3bis.get_max_cards_count());
    EXPECT_EQ(9, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(33, deck3bis[0].ident);
    EXPECT_EQ(32, deck3bis[1].ident);
    EXPECT_EQ(31, deck3bis[2].ident);
    EXPECT_EQ(23, deck3bis[3].ident);
    EXPECT_EQ(24, deck3bis[4].ident);
    EXPECT_EQ(25, deck3bis[5].ident);
    EXPECT_EQ(26, deck3bis[6].ident);
    EXPECT_EQ(22, deck3bis[7].ident);
    EXPECT_EQ(21, deck3bis[8].ident);

    //tests inserting a card at n-th position
    deck3bis.insert_nth_card(0, DefaultCardT(40));
    EXPECT_EQ(10, deck3bis.get_current_cards_count());
    EXPECT_EQ(10, deck3bis.get_max_cards_count());
    EXPECT_EQ(10, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(40, deck3bis[0].ident);
    EXPECT_EQ(33, deck3bis[1].ident);
    EXPECT_EQ(32, deck3bis[2].ident);
    EXPECT_EQ(31, deck3bis[3].ident);
    EXPECT_EQ(23, deck3bis[4].ident);
    EXPECT_EQ(24, deck3bis[5].ident);
    EXPECT_EQ(25, deck3bis[6].ident);
    EXPECT_EQ(26, deck3bis[7].ident);
    EXPECT_EQ(22, deck3bis[8].ident);
    EXPECT_EQ(21, deck3bis[9].ident);

    deck3bis.insert_nth_card(29, DefaultCardT(49));
    EXPECT_EQ(11, deck3bis.get_current_cards_count());
    EXPECT_EQ(11, deck3bis.get_max_cards_count());
    EXPECT_EQ(11, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(40, deck3bis[0].ident);
    EXPECT_EQ(33, deck3bis[1].ident);
    EXPECT_EQ(32, deck3bis[2].ident);
    EXPECT_EQ(31, deck3bis[3].ident);
    EXPECT_EQ(23, deck3bis[4].ident);
    EXPECT_EQ(24, deck3bis[5].ident);
    EXPECT_EQ(25, deck3bis[6].ident);
    EXPECT_EQ(26, deck3bis[7].ident);
    EXPECT_EQ(22, deck3bis[8].ident);
    EXPECT_EQ(21, deck3bis[9].ident);
    EXPECT_EQ(49, deck3bis[10].ident);

    deck3bis.insert_nth_card(1, DefaultCardT(41));
    EXPECT_EQ(12, deck3bis.get_current_cards_count());
    EXPECT_EQ(12, deck3bis.get_max_cards_count());
    EXPECT_EQ(12, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(40, deck3bis[0].ident);
    EXPECT_EQ(41, deck3bis[1].ident);
    EXPECT_EQ(33, deck3bis[2].ident);
    EXPECT_EQ(32, deck3bis[3].ident);
    EXPECT_EQ(31, deck3bis[4].ident);
    EXPECT_EQ(23, deck3bis[5].ident);
    EXPECT_EQ(24, deck3bis[6].ident);
    EXPECT_EQ(25, deck3bis[7].ident);
    EXPECT_EQ(26, deck3bis[8].ident);
    EXPECT_EQ(22, deck3bis[9].ident);
    EXPECT_EQ(21, deck3bis[10].ident);
    EXPECT_EQ(49, deck3bis[11].ident);

    // tests insertion of cards at n-th position
    deck3bis.insert_nth_cards(0, { DefaultCardT(51), DefaultCardT(52) });
    EXPECT_EQ(14, deck3bis.get_current_cards_count());
    EXPECT_EQ(14, deck3bis.get_max_cards_count());
    EXPECT_EQ(14, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(51, deck3bis[0].ident);
    EXPECT_EQ(52, deck3bis[1].ident);
    EXPECT_EQ(40, deck3bis[2].ident);
    EXPECT_EQ(41, deck3bis[3].ident);
    EXPECT_EQ(33, deck3bis[4].ident);
    EXPECT_EQ(32, deck3bis[5].ident);
    EXPECT_EQ(31, deck3bis[6].ident);
    EXPECT_EQ(23, deck3bis[7].ident);
    EXPECT_EQ(24, deck3bis[8].ident);
    EXPECT_EQ(25, deck3bis[9].ident);
    EXPECT_EQ(26, deck3bis[10].ident);
    EXPECT_EQ(22, deck3bis[11].ident);
    EXPECT_EQ(21, deck3bis[12].ident);
    EXPECT_EQ(49, deck3bis[13].ident);

    deck3bis.insert_nth_cards(14, { DefaultCardT(58), DefaultCardT(59) });
    EXPECT_EQ(16, deck3bis.get_current_cards_count());
    EXPECT_EQ(16, deck3bis.get_max_cards_count());
    EXPECT_EQ(16, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(51, deck3bis[0].ident);
    EXPECT_EQ(52, deck3bis[1].ident);
    EXPECT_EQ(40, deck3bis[2].ident);
    EXPECT_EQ(41, deck3bis[3].ident);
    EXPECT_EQ(33, deck3bis[4].ident);
    EXPECT_EQ(32, deck3bis[5].ident);
    EXPECT_EQ(31, deck3bis[6].ident);
    EXPECT_EQ(23, deck3bis[7].ident);
    EXPECT_EQ(24, deck3bis[8].ident);
    EXPECT_EQ(25, deck3bis[9].ident);
    EXPECT_EQ(26, deck3bis[10].ident);
    EXPECT_EQ(22, deck3bis[11].ident);
    EXPECT_EQ(21, deck3bis[12].ident);
    EXPECT_EQ(49, deck3bis[13].ident);
    EXPECT_EQ(58, deck3bis[14].ident);
    EXPECT_EQ(59, deck3bis[15].ident);

    deck3bis.insert_nth_cards(5, { DefaultCardT(55), DefaultCardT(56), DefaultCardT(57) });
    EXPECT_EQ(19, deck3bis.get_current_cards_count());
    EXPECT_EQ(19, deck3bis.get_max_cards_count());
    EXPECT_EQ(19, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(51, deck3bis[0].ident);
    EXPECT_EQ(52, deck3bis[1].ident);
    EXPECT_EQ(40, deck3bis[2].ident);
    EXPECT_EQ(41, deck3bis[3].ident);
    EXPECT_EQ(33, deck3bis[4].ident);
    EXPECT_EQ(55, deck3bis[5].ident);
    EXPECT_EQ(56, deck3bis[6].ident);
    EXPECT_EQ(57, deck3bis[7].ident);
    EXPECT_EQ(32, deck3bis[8].ident);
    EXPECT_EQ(31, deck3bis[9].ident);
    EXPECT_EQ(23, deck3bis[10].ident);
    EXPECT_EQ(24, deck3bis[11].ident);
    EXPECT_EQ(25, deck3bis[12].ident);
    EXPECT_EQ(26, deck3bis[13].ident);
    EXPECT_EQ(22, deck3bis[14].ident);
    EXPECT_EQ(21, deck3bis[15].ident);
    EXPECT_EQ(49, deck3bis[16].ident);
    EXPECT_EQ(58, deck3bis[17].ident);
    EXPECT_EQ(59, deck3bis[18].ident);

    deck3bis.insert_nth_cards(0, DefaultCardT(61), DefaultCardT(62));
    EXPECT_EQ(21, deck3bis.get_current_cards_count());
    EXPECT_EQ(21, deck3bis.get_max_cards_count());
    EXPECT_EQ(21, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(61, deck3bis[0].ident);
    EXPECT_EQ(62, deck3bis[1].ident);
    EXPECT_EQ(51, deck3bis[2].ident);
    EXPECT_EQ(52, deck3bis[3].ident);
    EXPECT_EQ(40, deck3bis[4].ident);
    EXPECT_EQ(41, deck3bis[5].ident);
    EXPECT_EQ(33, deck3bis[6].ident);
    EXPECT_EQ(55, deck3bis[7].ident);
    EXPECT_EQ(56, deck3bis[8].ident);
    EXPECT_EQ(57, deck3bis[9].ident);
    EXPECT_EQ(32, deck3bis[10].ident);
    EXPECT_EQ(31, deck3bis[11].ident);
    EXPECT_EQ(23, deck3bis[12].ident);
    EXPECT_EQ(24, deck3bis[13].ident);
    EXPECT_EQ(25, deck3bis[14].ident);
    EXPECT_EQ(26, deck3bis[15].ident);
    EXPECT_EQ(22, deck3bis[16].ident);
    EXPECT_EQ(21, deck3bis[17].ident);
    EXPECT_EQ(49, deck3bis[18].ident);
    EXPECT_EQ(58, deck3bis[19].ident);
    EXPECT_EQ(59, deck3bis[20].ident);

    deck3bis.insert_nth_cards(2, DefaultCardT(63), DefaultCardT(64), DefaultCardT(65));
    EXPECT_EQ(24, deck3bis.get_current_cards_count());
    EXPECT_EQ(24, deck3bis.get_max_cards_count());
    EXPECT_EQ(24, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(61, deck3bis[0].ident);
    EXPECT_EQ(62, deck3bis[1].ident);
    EXPECT_EQ(63, deck3bis[2].ident);
    EXPECT_EQ(64, deck3bis[3].ident);
    EXPECT_EQ(65, deck3bis[4].ident);
    EXPECT_EQ(51, deck3bis[5].ident);
    EXPECT_EQ(52, deck3bis[6].ident);
    EXPECT_EQ(40, deck3bis[7].ident);
    EXPECT_EQ(41, deck3bis[8].ident);
    EXPECT_EQ(33, deck3bis[9].ident);
    EXPECT_EQ(55, deck3bis[10].ident);
    EXPECT_EQ(56, deck3bis[11].ident);
    EXPECT_EQ(57, deck3bis[12].ident);
    EXPECT_EQ(32, deck3bis[13].ident);
    EXPECT_EQ(31, deck3bis[14].ident);
    EXPECT_EQ(23, deck3bis[15].ident);
    EXPECT_EQ(24, deck3bis[16].ident);
    EXPECT_EQ(25, deck3bis[17].ident);
    EXPECT_EQ(26, deck3bis[18].ident);
    EXPECT_EQ(22, deck3bis[19].ident);
    EXPECT_EQ(21, deck3bis[20].ident);
    EXPECT_EQ(49, deck3bis[21].ident);
    EXPECT_EQ(58, deck3bis[22].ident);
    EXPECT_EQ(59, deck3bis[23].ident);

    deck3bis.insert_nth_cards(24, DefaultCardT(67), DefaultCardT(68), DefaultCardT(69));
    EXPECT_EQ(27, deck3bis.get_current_cards_count());
    EXPECT_EQ(27, deck3bis.get_max_cards_count());
    EXPECT_EQ(27, deck3bis.deck().size());
    EXPECT_LE(deck3bis.get_max_cards_count(), deck3bis.deck().capacity());
    EXPECT_EQ(61, deck3bis[0].ident);
    EXPECT_EQ(62, deck3bis[1].ident);
    EXPECT_EQ(63, deck3bis[2].ident);
    EXPECT_EQ(64, deck3bis[3].ident);
    EXPECT_EQ(65, deck3bis[4].ident);
    EXPECT_EQ(51, deck3bis[5].ident);
    EXPECT_EQ(52, deck3bis[6].ident);
    EXPECT_EQ(40, deck3bis[7].ident);
    EXPECT_EQ(41, deck3bis[8].ident);
    EXPECT_EQ(33, deck3bis[9].ident);
    EXPECT_EQ(55, deck3bis[10].ident);
    EXPECT_EQ(56, deck3bis[11].ident);
    EXPECT_EQ(57, deck3bis[12].ident);
    EXPECT_EQ(32, deck3bis[13].ident);
    EXPECT_EQ(31, deck3bis[14].ident);
    EXPECT_EQ(23, deck3bis[15].ident);
    EXPECT_EQ(24, deck3bis[16].ident);
    EXPECT_EQ(25, deck3bis[17].ident);
    EXPECT_EQ(26, deck3bis[18].ident);
    EXPECT_EQ(22, deck3bis[19].ident);
    EXPECT_EQ(21, deck3bis[20].ident);
    EXPECT_EQ(49, deck3bis[21].ident);
    EXPECT_EQ(58, deck3bis[22].ident);
    EXPECT_EQ(59, deck3bis[23].ident);
    EXPECT_EQ(67, deck3bis[24].ident);
    EXPECT_EQ(68, deck3bis[25].ident);
    EXPECT_EQ(69, deck3bis[26].ident);

    // tests the searching of cards in deck
    constexpr DefaultDeckT::IndexType NOT_FOUND{ DefaultDeckT::IndexType(-1) };
    for (int i=0; i < 6; ++i)
        EXPECT_EQ(i, deck4.get_index(DefaultCardT(i + 1)));
    EXPECT_EQ(NOT_FOUND, deck4.get_index(DefaultCardT(-1)));
    EXPECT_EQ(NOT_FOUND, deck4.get_index(DefaultCardT(7)));
    EXPECT_EQ(NOT_FOUND, deck4.get_index(DefaultCardT(8)));

    for (int i = 0; i < 6; ++i)
        EXPECT_TRUE(deck4.contains(DefaultCardT(i + 1)));

    EXPECT_TRUE(deck4.contains_all({DefaultCardT(1), DefaultCardT(3), DefaultCardT(6)}));
    EXPECT_TRUE(deck4.contains_all({ DefaultCardT(1), DefaultCardT(2), DefaultCardT(3),
                                     DefaultCardT(4), DefaultCardT(5), DefaultCardT(6)  }));
    EXPECT_FALSE(deck4.contains_all({ DefaultCardT(1), DefaultCardT(3), DefaultCardT(7) }));

    EXPECT_TRUE(deck4.contains_all(DefaultCardT(1), DefaultCardT(3), DefaultCardT(6)));
    EXPECT_TRUE(deck4.contains_all(DefaultCardT(1), DefaultCardT(2), DefaultCardT(3),
                                   DefaultCardT(4), DefaultCardT(5), DefaultCardT(6)));
    EXPECT_FALSE(deck4.contains_all(DefaultCardT(1), DefaultCardT(3), DefaultCardT(7)));

    EXPECT_TRUE(deck4.contains_any({ DefaultCardT(1), DefaultCardT(3), DefaultCardT(6) }));
    EXPECT_TRUE(deck4.contains_any({ DefaultCardT(1), DefaultCardT(2), DefaultCardT(3),
                                     DefaultCardT(4), DefaultCardT(5), DefaultCardT(6) }));
    EXPECT_TRUE(deck4.contains_any({ DefaultCardT(1), DefaultCardT(3), DefaultCardT(7) }));
    EXPECT_FALSE(deck4.contains_any({ DefaultCardT(-1), DefaultCardT(7), DefaultCardT(8) }));

    EXPECT_TRUE(deck4.contains_any(DefaultCardT(1), DefaultCardT(3), DefaultCardT(6)));
    EXPECT_TRUE(deck4.contains_any(DefaultCardT(1), DefaultCardT(2), DefaultCardT(3),
        DefaultCardT(4), DefaultCardT(5), DefaultCardT(6)));
    EXPECT_TRUE(deck4.contains_any(DefaultCardT(1), DefaultCardT(3), DefaultCardT(7)));
    EXPECT_FALSE(deck4.contains_any(DefaultCardT(-1), DefaultCardT(7), DefaultCardT(8)));


    for (int i = 0; i < 6; ++i) {
        EXPECT_TRUE(deck4.contains_any(DefaultCardT(i + 1), DefaultCardT(7)));
        EXPECT_FALSE(deck4.contains_all(DefaultCardT(7), DefaultCardT(i + 1)));
    }

    // tests the insertion of a card at random position
    DefaultCardT card11(11);
    deck4.insert_rand_card(card11);

    EXPECT_EQ(7, deck4.get_current_cards_count());
    EXPECT_EQ(7, deck4.get_max_cards_count());
    EXPECT_EQ(7, deck4.deck().size());
    EXPECT_EQ(7, deck4.get_max_cards_count());
    EXPECT_LE(deck4.get_max_cards_count(), deck4.deck().capacity());  // notice: set to 7, not to 6 - might be STL implementation dependant...

    const DefaultDeckT::IndexType card11_index{ deck4.get_index(card11) };

    for (int i = 0; i < 7; ++i) {
        if (i < int(card11_index))
            EXPECT_EQ(i + 1, deck4[i].ident);
        else if (i > int(card11_index))
            EXPECT_EQ(i, deck4[i].ident);
        else
            EXPECT_EQ(card11.ident, deck4[i].ident);
    }

    // tests the emptyness of decks
    EXPECT_TRUE(empty_deck.is_empty());
    EXPECT_FALSE(deck4.is_empty());
    EXPECT_FALSE(deck3.is_empty());
    EXPECT_FALSE(deck33.is_empty());
    EXPECT_FALSE(deck3bis.is_empty());

    // tests the fullness of decks
    EXPECT_FALSE(empty_deck.is_full());
    EXPECT_TRUE(deck4.is_full());
    EXPECT_TRUE(deck3.is_full());
    EXPECT_TRUE(deck33.is_full());
    EXPECT_TRUE(deck3bis.is_full());

    deck4.draw_card();
    EXPECT_FALSE(deck4.is_empty());
    EXPECT_FALSE(deck4.is_full());

    DefaultDeckT::CardsList hand{ deck4.draw_n_cards(25) };
    EXPECT_EQ(6, hand.size());
    EXPECT_EQ(0, deck4.get_current_cards_count());
    EXPECT_EQ(7, deck4.get_max_cards_count());
    EXPECT_EQ(0, deck4.deck().size());
    EXPECT_LE(deck4.get_max_cards_count(), deck4.deck().capacity());
    EXPECT_TRUE(deck4.is_empty());
    EXPECT_FALSE(deck4.is_full());

    // tests the refilling of decks
    deck4.refill_deck({ DefaultCardT(41), DefaultCardT(42), DefaultCardT(43), DefaultCardT(44), DefaultCardT(45) });

    EXPECT_EQ(5, deck4.get_current_cards_count());
    EXPECT_EQ(5, deck4.get_max_cards_count());
    EXPECT_EQ(5, deck4.deck().size());
    EXPECT_EQ(5, deck4.deck().capacity());

    EXPECT_EQ(41, deck4[0].ident);
    EXPECT_EQ(42, deck4[1].ident);
    EXPECT_EQ(43, deck4[2].ident);
    EXPECT_EQ(44, deck4[3].ident);
    EXPECT_EQ(45, deck4[4].ident);

    deck4.refill_deck(DefaultCardT(1), DefaultCardT(2), DefaultCardT(3), DefaultCardT(4), DefaultCardT(5), DefaultCardT(6), DefaultCardT(7));

    EXPECT_EQ(7, deck4.get_current_cards_count());
    EXPECT_EQ(7, deck4.get_max_cards_count());
    EXPECT_EQ(7, deck4.deck().size());
    EXPECT_LE(deck4.get_max_cards_count(), deck4.deck().capacity());

    EXPECT_EQ(1, deck4[0].ident);
    EXPECT_EQ(2, deck4[1].ident);
    EXPECT_EQ(3, deck4[2].ident);
    EXPECT_EQ(4, deck4[3].ident);
    EXPECT_EQ(5, deck4[4].ident);
    EXPECT_EQ(6, deck4[5].ident);
    EXPECT_EQ(7, deck4[6].ident);

    // tests the drawing of bottom cards
    card = deck4.pop_bottom_card();

    EXPECT_EQ(7, card.ident);

    EXPECT_EQ(6, deck4.get_current_cards_count());
    EXPECT_EQ(7, deck4.get_max_cards_count());
    EXPECT_EQ(6, deck4.deck().size());
    EXPECT_LE(deck4.get_max_cards_count(), deck4.deck().capacity());

    EXPECT_EQ(1, deck4[0].ident);
    EXPECT_EQ(2, deck4[1].ident);
    EXPECT_EQ(3, deck4[2].ident);
    EXPECT_EQ(4, deck4[3].ident);
    EXPECT_EQ(5, deck4[4].ident);
    EXPECT_EQ(6, deck4[5].ident);

    hand = deck4.pop_bottom_n_cards(2);

    EXPECT_EQ(5, hand[0].ident);
    EXPECT_EQ(6, hand[1].ident);

    EXPECT_EQ(4, deck4.get_current_cards_count());
    EXPECT_EQ(7, deck4.get_max_cards_count());
    EXPECT_EQ(4, deck4.deck().size());
    EXPECT_LE(deck4.get_max_cards_count(), deck4.deck().capacity());

    EXPECT_EQ(1, deck4[0].ident);
    EXPECT_EQ(2, deck4[1].ident);
    EXPECT_EQ(3, deck4[2].ident);
    EXPECT_EQ(4, deck4[3].ident);

    // tests the shuffling of decks
    deck4.append_card(DefaultCardT(5));

    for (int i=0; i < 100; ++i)  // just to have a chance of not missing out-of-bounds exceptions
        deck4.shuffle();
    for (int i = 1; i < 6; ++i)
        EXPECT_TRUE(deck4.contains(DefaultCardT(i)));

    deck4.refill_deck(DefaultCardT(1), DefaultCardT(2), DefaultCardT(3), DefaultCardT(4), DefaultCardT(5), DefaultCardT(6), DefaultCardT(7));
    for (int i = 0; i < 100; ++i)  // just to have a chance of not missing out-of-bounds exceptions
        deck4.shuffle(1, 5);
    EXPECT_EQ(1, deck4[0].ident);
    EXPECT_EQ(7, deck4[6].ident);
    for (int i = 2; i < 7; ++i)
        EXPECT_TRUE(deck4.contains(DefaultCardT(i)));

    // notice: next methods have been already tested via the former tests of their insert_card() related callers
    // - clear()
    // - pop_indexed_card(const IndexType index);
    // - pop_rand_card()
    // - pop_up_card()

}
