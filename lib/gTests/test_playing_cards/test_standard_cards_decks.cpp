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

#include "pltr/playing_cards/standard_cards.h"
#include "pltr/playing_cards/standard_cards_decks.h"


//===========================================================================
TEST(TestSuitePlayingCards, TestStandardCardsDeck) {

    constexpr std::uint32_t START_VALUE_54{ 2 };
    constexpr std::uint32_t START_VALUE_52{ 0 };
    constexpr std::uint32_t START_VALUE_32{ 7 };
    constexpr std::uint32_t START_INDEX_32{ 20 };
    constexpr std::uint32_t START_ORDERING_VALUE_32{ 1117 };

    using CardFr = pltr::cards::StandardCardFr<>;
    using Card52Fr = pltr::cards::StandardCardFr<0, 52>;
    using Card32Fr = pltr::cards::StandardCardFr<START_INDEX_32, 52>;

    using Deck54 = pltr::cards::StandardCardsDeck<CardFr, 54, 0, START_VALUE_54>;
    using Deck52 = pltr::cards::StandardCardsDeck<Card52Fr, 52, 0, START_VALUE_52>;
    using Deck32 = pltr::cards::StandardCardsDeck<Card32Fr, 32, 20, START_VALUE_32, START_ORDERING_VALUE_32>;

    // tests 54-cards decks
    Deck54 deck54;

    EXPECT_EQ(54, deck54.get_current_cards_count());
    EXPECT_EQ(54, deck54.get_max_cards_count());
    EXPECT_EQ(54, deck54.deck().size());
    EXPECT_LE(54, deck54.deck().capacity());
    
    for (int i = 0; i < 54; ++i) {
        EXPECT_EQ(i, deck54[i].ident);
        EXPECT_EQ(i / 4 + START_VALUE_54, deck54[i].value);
        EXPECT_EQ(i, deck54[i].ordering_value);
    }

    int n{ 0 };
    for (int i = 0; i < 100; ++i) {
        int id;
        deck54.shuffle();
        for (id = 0; id < 54; ++id)
            if (deck54[id].ident != id)
                break;
        if (id == 54)
            ++n;
    }
    EXPECT_GE(1, n);

    for (int i = 0; i < 54; ++i) {
        const CardFr card(i);
        EXPECT_TRUE(deck54.contains(card));
        EXPECT_TRUE(deck54.append_card(card));
    }
    for (int i = 54; i < 100; ++i) {
        EXPECT_THROW({
            const CardFr card(i);
            EXPECT_FALSE(deck54.contains(card));
            EXPECT_FALSE(deck54.append_card(card));
        }, pltr::cards::StandardInvalidIdent);
    }

    deck54.refill_deck();
    deck54.sort();
    EXPECT_EQ(53, deck54[0].ident);
    EXPECT_EQ(52, deck54[1].ident);
    int v{ 12 + START_VALUE_54 };
    for (int i = 2; i < 54; i += 4, v--) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(53 - i - j, int(deck54[i + j].ident));
            EXPECT_EQ(v, deck54[i + j].value);
            EXPECT_EQ(53 - i - j, deck54[i + j].ordering_value);
        }
    }

    deck54.refill_deck();
    deck54.sort_colors();
    EXPECT_EQ(53, deck54[0].ident);
    EXPECT_EQ(52, deck54[1].ident);
    pltr::cards::EColor color{ pltr::cards::EColor::E_SPADE };
    for (int i = 2; i < 54; i += 13) {
        for (int j = 12; j > 0; --j) {
            EXPECT_EQ(j + START_VALUE_54, deck54[i + 12 - j].value);
            EXPECT_EQ(4 * j + int(color), int(deck54[i + 12 - j].ident));
            EXPECT_EQ(int(color), int(deck54[i + j].get_color()));
        }
        color = pltr::cards::EColor(int(color) - 1);
    }

    deck54.refill_deck();
    deck54.sort_colors_values();
    EXPECT_EQ(53, deck54[0].ident);
    EXPECT_EQ(52, deck54[1].ident);
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 2; i < 54; i += 13) {
        for (int j = 12; j > 0; --j) {
            EXPECT_EQ(j + START_VALUE_54, deck54[i + 12 - j].value);
            EXPECT_EQ(4 * j + int(color), int(deck54[i + 12 - j].ident));
            EXPECT_EQ(int(color), int(deck54[i + 12 - j].get_color()));
        }
        color = pltr::cards::EColor(int(color) - 1);
    }

    deck54.refill_deck();
    deck54.sort_idents();
    EXPECT_EQ(53, deck54[0].ident);
    EXPECT_EQ(52, deck54[1].ident);
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 2; i < 54; ++i) {
        EXPECT_EQ((53 - i) / 4 + START_VALUE_54, deck54[i].value);
        EXPECT_EQ(53 - i, int(deck54[i].ident));
        EXPECT_EQ((53 - i) % 4, int(deck54[i].get_color()));
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
        const Card52Fr card(i);
        EXPECT_TRUE(deck52.contains(card));
        EXPECT_TRUE(deck52.append_card(card));
    }

    for (int i = 52; i < 56; ++i) {
        EXPECT_THROW({
            const Card52Fr card(i);
            EXPECT_FALSE(deck52.contains(card));
            EXPECT_FALSE(deck52.append_card(card));
        }, pltr::cards::StandardInvalidIdent);
    }

    deck52.refill_deck();
    deck52.sort();
    v = 12 + START_VALUE_52;
    for (int i = 0; i < 52; i += 4, v--) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(51 - i - j, int(deck52[i + j].ident));
            EXPECT_EQ(v, deck52[i + j].value);
            EXPECT_EQ(51 - i - j, deck52[i + j].ordering_value);
        }
    }

    deck52.refill_deck();
    deck52.sort_colors();
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 0; i < 52; i += 13) {
        for (int j = 12; j >= 0; --j) {
            EXPECT_EQ(j + START_VALUE_52, deck52[i + 12 - j].value);
            EXPECT_EQ(4 * j + int(color), int(deck52[i + 12 - j].ident));
            EXPECT_EQ(int(color), int(deck52[i + 12 - j].get_color()));
        }
        color = pltr::cards::EColor(int(color) - 1);
    }

    deck52.refill_deck();
    deck52.sort_colors_values();
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 0; i < 52; i += 13) {
        for (int j = 12; j > 0; --j) {
            EXPECT_EQ(j + START_VALUE_52, deck52[i + 12 - j].value);
            EXPECT_EQ(4 * j + int(color), int(deck52[i + 12 - j].ident));
            EXPECT_EQ(int(color), int(deck52[i + 12 - j].get_color()));
        }
        color = pltr::cards::EColor(int(color) - 1);
    }

    deck52.refill_deck();
    deck52.sort_idents();
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 0; i < 52; ++i) {
        EXPECT_EQ((51 - i) / 4 + START_VALUE_52, deck52[i].value);
        EXPECT_EQ(51 - i, int(deck52[i].ident));
        EXPECT_EQ((51 - i) % 4, int(deck52[i].get_color()));
    }


    // tests 32-cards decks
    Deck32 deck32;

    EXPECT_EQ(32, deck32.get_current_cards_count());
    EXPECT_EQ(32, deck32.get_max_cards_count());
    EXPECT_EQ(32, deck32.deck().size());
    EXPECT_LE(32, deck32.deck().capacity());

    for (int i = 0; i < START_INDEX_32; ++i) {
        EXPECT_THROW({
            const Card32Fr card(i);
            }, pltr::cards::StandardInvalidIdent
        );
    }

    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ(i + START_INDEX_32, deck32[i].ident);
        EXPECT_EQ(i / 4 + START_VALUE_32, deck32[i].value);
        EXPECT_EQ(i + START_ORDERING_VALUE_32, deck32[i].ordering_value);
    }

    for (int i = 32; i < 56; ++i) {
        EXPECT_THROW({
            const Card32Fr card(i + START_INDEX_32);
            }, pltr::cards::StandardInvalidIdent
        );
    }

    for (int i = 0; i < 100; ++i)
        deck32.shuffle();

    for (int i = 0; i < 32; ++i) {
        const Card32Fr card(i + START_INDEX_32);
        EXPECT_TRUE(deck32.contains(card));
        EXPECT_TRUE(deck32.append_card(card));
    }

    deck32.refill_deck();
    deck32.sort();
    v = 14;
    for (int i = 0; i < 32; i += 4, v--) {
        for (int j = 0; j < 4; ++j) {
            EXPECT_EQ(31 + START_INDEX_32- i - j, int(deck32[i + j].ident));
            EXPECT_EQ(v, deck32[i + j].value);
            EXPECT_EQ(31 - i - j + START_ORDERING_VALUE_32, deck32[i + j].ordering_value);
        }
    }

    deck32.refill_deck();
    deck32.sort_colors();
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 0; i < 32; i += 8) {
        for (int j = 7; j >= 0; --j) {
            EXPECT_EQ(j + START_VALUE_32, deck32[i + 7 - j].value);
            EXPECT_EQ(4 * j + int(color) + START_INDEX_32, int(deck32[i + 7 - j].ident));
            EXPECT_EQ(int(color), int(deck32[i + 7 - j].get_color()));
        }
        color = pltr::cards::EColor(int(color) - 1);
    }

    deck32.refill_deck();
    deck32.sort_colors_values();
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 0; i < 32; i += 8) {
        for (int j = 7; j > 0; --j) {
            EXPECT_EQ(j + START_VALUE_32, deck32[i + 7 - j].value);
            EXPECT_EQ(4 * j + int(color) + START_INDEX_32, int(deck32[i + 7 - j].ident));
            EXPECT_EQ(int(color), int(deck32[i + 7 - j].get_color()));
        }
        color = pltr::cards::EColor(int(color) - 1);
    }

    deck32.refill_deck();
    deck32.sort_idents();
    color = pltr::cards::EColor::E_SPADE;
    for (int i = 0; i < 32; ++i) {
        EXPECT_EQ((31 - i) / 4 + START_VALUE_32, deck32[i].value);
        EXPECT_EQ(31 + START_INDEX_32 - i, int(deck32[i].ident));
        EXPECT_EQ((31 + START_INDEX_32 - i) % 4, int(deck32[i].get_color()));
    }


    // tests multiple 54 cards decks
    constexpr std::uint32_t N{ 3 };
    pltr::cards::StandardCardsDeck<CardFr, 54, 0, START_VALUE_54, 0, N> deck543;

    EXPECT_EQ(54 * N, deck543.get_current_cards_count());
    EXPECT_EQ(54 * N, deck543.get_max_cards_count());
    EXPECT_EQ(54 * N, deck543.deck().size());
    EXPECT_LE(54 * N, deck543.deck().capacity());

    for (int i = 0; i < 54; ++i)
        for (int j = 0; j < N; ++j) {
            EXPECT_EQ(i, deck543[N * i + j].ident);
            EXPECT_EQ(i / 4 + START_VALUE_54, deck543[N * i + j].value);
            EXPECT_EQ(i, deck543[N * i + j].ordering_value);
        }

    for (int i = 0; i < 100; ++i)
        deck543.shuffle();

    for (int i = 0; i < 54; ++i) {
        const CardFr card(i);
        EXPECT_TRUE(deck543.contains(card));
        EXPECT_TRUE(deck543.append_card(card));
    }
    for (int i = 54; i < 100; ++i) {
        EXPECT_THROW({
            const CardFr card(i);
            EXPECT_FALSE(deck543.contains(card));
            EXPECT_FALSE(deck543.append_card(card));
            }, pltr::cards::StandardInvalidIdent);
    }

    deck543.refill_deck();

    for (int i = 0; i < 54; ++i)
        for (int j = 0; j < N; ++j) {
            EXPECT_EQ(i, deck543[N * i + j].ident);
            EXPECT_EQ(i / 4 + START_VALUE_54, deck543[N * i + j].value);
            EXPECT_EQ(i, deck543[N * i + j].ordering_value);
        }

    const CardFr card0(53);

    deck543.shuffle();
    for (int i = 0; i < N; ++i) {
        EXPECT_TRUE(deck543.draw_card(card0));
        EXPECT_EQ(54 * N - i - 1, deck543.get_current_cards_count());
    }

    EXPECT_FALSE(deck543.contains(card0));

    for (int i = 0; i < N; ++i) {
        EXPECT_FALSE(deck543.draw_card(card0)) << deck543.get_current_cards_count();
    }

}
