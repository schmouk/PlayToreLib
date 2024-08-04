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
#include "playing_cards/unique_standard_cards_decks.h"


//===========================================================================
TEST(TestSuitePlayingCards, TestUniqueStandardCardsDeck) {


    /**** /
    using CardFr = pltr::cards::StandardCardFr;
    using Deck54 = pltr::cards::UniqueStandardCardsDeck54<CardFr>;
    using Deck52 = pltr::cards::UniqueStandardCardsDeck52<CardFr>;
    using Deck32 = pltr::cards::UniqueStandardCardsDeck32<CardFr>;

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

    for (int i = 0; i < 54; ++i) {
        const CardFr card(i);
        EXPECT_TRUE(deck54.contains(card));
        EXPECT_FALSE(deck54.append_card(card));
    }
    for (int i = 54; i < 100; ++i) {
        const CardFr card(i);
        EXPECT_FALSE(deck54.contains(card));
        EXPECT_FALSE(deck54.append_card(card));
    }


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

    for (int i = 0; i < 52; ++i) {
        const CardFr card(i);
        EXPECT_TRUE(deck52.contains(card));
        EXPECT_FALSE(deck52.append_card(card));
    }
    for (int i = 52; i < 56; ++i) {
        const CardFr card(i);
        EXPECT_FALSE(deck52.contains(card));
        EXPECT_FALSE(deck52.append_card(card));
    }


    // tests 32-cards decks
    Deck32 deck32;

    EXPECT_EQ(32, deck32.get_current_cards_count());
    EXPECT_EQ(32, deck32.get_max_cards_count());
    EXPECT_EQ(32, deck32.deck().size());
    EXPECT_LE(32, deck32.deck().capacity());

    int n{ 0 };
    for (int i = 0; i < 4; ++n, ++i)
        EXPECT_EQ(i, deck32[n].ident);
    for (int i = 24; i < 52; ++n, ++i)
        EXPECT_EQ(i, deck32[n].ident);

    for (int i = 0; i < 100; ++i)
        deck32.shuffle();

    for (int i = 0; i < 4; ++i) {
        const CardFr card(i);
        EXPECT_TRUE(deck32.contains(card));
        EXPECT_FALSE(deck32.append_card(card));
    }
    for (int i = 4; i < 24; ++i) {
        const CardFr card(i);
        EXPECT_FALSE(deck32.contains(card));
        EXPECT_FALSE(deck32.append_card(card));
    }
    for (int i = 24; i < 52; ++i) {
        const CardFr card(i);
        EXPECT_TRUE(deck32.contains(card));
        EXPECT_FALSE(deck32.append_card(card));
    }
    for (int i = 52; i < 56; ++i) {
        const CardFr card(i);
        EXPECT_FALSE(deck32.contains(card));
        EXPECT_FALSE(deck32.append_card(card));
    }

    using CardsList = Deck52::CardsList;
    deck52.refill_deck();
    CardsList cards{ deck52.draw_n_cards(5) };
    for (int i = 0; i < 5; ++i)
        EXPECT_EQ(i, cards[i].ident);
    EXPECT_EQ(47, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    for (int i = 0; i < 5; ++i)
        EXPECT_TRUE(deck52.append_card(cards[i]));
    EXPECT_EQ(52, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    cards = deck52.draw_n_cards(6);
    EXPECT_EQ(46, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    for (int i = 0; i < 5; ++i)
        EXPECT_FALSE(deck52.append_card(CardFr(i)));
    for (int i = 11; i < 54; ++i)
        EXPECT_FALSE(deck52.append_card(CardFr(i)));
    for (int i = 0; i < 6; ++i)
        EXPECT_FALSE(deck52.contains(cards[i]));

    for (int i = 0; i < 6; ++i) {
        EXPECT_TRUE(deck52.append_card(cards[i]));
        EXPECT_FALSE(deck52.append_card(cards[i]));
    }

    for (int i = 0; i < 52; ++i)
        EXPECT_TRUE(deck52.contains(CardFr(i)));

    cards = deck52.pop_bottom_n_cards(6);
    EXPECT_EQ(46, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    for (int i = 0; i < 5; ++i)
        EXPECT_FALSE(deck52.insert_card(CardFr(i)));
    for (int i = 11; i < 54; ++i)
        EXPECT_FALSE(deck52.insert_card(CardFr(i)));
    for (int i = 0; i < 6; ++i)
        EXPECT_FALSE(deck52.contains(cards[i]));

    for (int i = 0; i < 6; ++i) {
        EXPECT_TRUE(deck52.insert_card(cards[i]));
        EXPECT_FALSE(deck52.insert_card(cards[i]));
    }

    cards = deck52.pop_up_n_cards(11);
    EXPECT_EQ(41, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    deck52.append_cards(cards);
    EXPECT_EQ(52, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());
    for (int i = 0; i < 52; ++i)
        EXPECT_TRUE(deck52.contains(CardFr(i)));

    cards = deck52.pop_up_n_cards(13);
    EXPECT_EQ(39, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    deck52.insert_cards(cards);
    EXPECT_EQ(52, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());
    for (int i = 0; i < 52; ++i)
        EXPECT_TRUE(deck52.contains(CardFr(i)));

    deck52.refill_deck();
    CardFr card{ deck52.draw_card() };
    EXPECT_EQ(51, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());
    EXPECT_FALSE(deck52.contains(card));
    for (int i=1; i < 52; ++i)
        EXPECT_FALSE(deck52.insert_nth_card(8, CardFr(i)));

    const int INDEX{ 5 };
    EXPECT_TRUE(deck52.insert_nth_card(INDEX, card));
    EXPECT_EQ(52, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());
    EXPECT_TRUE(deck52.contains(card));
    EXPECT_EQ(card.ident, deck52[INDEX].ident);
    for (int i = 0; i < 52; ++i)
        EXPECT_FALSE(deck52.insert_nth_card(INDEX, CardFr(i)));

    deck52.refill_deck();
    cards = deck52.draw_n_cards(17);
    EXPECT_EQ(35, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    for (int i = 0; i < 17; ++i) {
        cards.push_back(cards[i]);
        cards.push_back(cards[i]);
    }
    deck52.insert_nth_cards(23, cards);
    EXPECT_EQ(52, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());
    for (int i = 0; i < 52; ++i)
        EXPECT_TRUE(deck52.contains(CardFr(i)));

    deck52.refill_deck();
    cards = deck52.draw_n_cards(17);
    EXPECT_EQ(35, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());

    for (int i = 0; i < 17; ++i) {
        cards.push_back(cards[i]);
        cards.push_back(cards[i]);
    }
    deck52.append_cards(cards);
    EXPECT_EQ(52, deck52.get_current_cards_count());
    EXPECT_EQ(52, deck52.get_max_cards_count());
    for (int i = 0; i < 52; ++i)
        EXPECT_TRUE(deck52.contains(CardFr(i)));

    /*****/
}
