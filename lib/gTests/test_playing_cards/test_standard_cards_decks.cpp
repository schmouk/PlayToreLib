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

#include "playing_cards/standard_cards.h"
#include "playing_cards/standard_cards_decks.h"


//===========================================================================
TEST(TestSuitePlayingCards, TestStandardCardsDeck) {

    using CardFr = pltr::cards::StandardCardFr;
    using Deck54 = pltr::cards::CardsDeck54<CardFr>;
    using Deck52 = pltr::cards::CardsDeck52<CardFr>;
    using Deck32 = pltr::cards::CardsDeck32<CardFr>;

    // tests 54-cards decks
    Deck54 deck54;

    EXPECT_EQ(54, deck54.get_current_cards_count());
    EXPECT_EQ(54, deck54.get_max_cards_count());
    EXPECT_EQ(54, deck54.deck().size());
    EXPECT_LE(54, deck54.deck().capacity());
    
    for (int i = 0; i < 54; ++i)
        EXPECT_EQ(i, deck54[i].ident);

    for (int i = 0; i < 100; ++i)
        deck54.shuffle();

    for (int i = 0; i < 54; ++i)
        EXPECT_TRUE(deck54.contains(CardFr(i)));


    // tests 52-cards decks
    Deck52 deck52;

    EXPECT_EQ(52, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());
    EXPECT_EQ(52, deck52.deck().size());
    EXPECT_LE(52, deck52.deck().capacity());

    for (int i = 0; i < 52; ++i)
        EXPECT_EQ(i, deck52[i].ident);

    for (int i = 0; i < 100; ++i)
        deck52.shuffle();

    for (int i = 0; i < 52; ++i)
        EXPECT_TRUE(deck52.contains(CardFr(i)));


    // tests 32-cards decks
    Deck32 deck32;

    EXPECT_EQ(32, deck32.get_current_cards_count());
    EXPECT_EQ(32, deck32.get_max_cards_count());
    EXPECT_EQ(32, deck32.deck().size());
    EXPECT_LE(32, deck32.deck().capacity());

    int n{ 0 };
    for (int i = 0; i <4; ++n, ++i)
        EXPECT_EQ(i, deck32[n].ident);
    for (int i = 24; i < 52; ++n, ++i)
        EXPECT_EQ(i, deck32[n].ident);

    for (int i = 0; i < 100; ++i)
        deck32.shuffle();

    for (int i = 0; i < 4; ++i)
        EXPECT_TRUE(deck32.contains(CardFr(i)));
    for (int i = 24; i < 52; ++i)
        EXPECT_TRUE(deck32.contains(CardFr(i)));

}
