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

#include <format>
#include <string>

#include "playing_cards/standard_cards.h"


//===========================================================================
TEST(TestSuitePlayingCards, TestStandardCard) {
    const std::string EMPTY_STRING;
    const std::wstring EMPTY_WSTRING;

    using StandardCard = pltr::cards::StandardCard<>;

    // tests empty default constructor
    StandardCard card0;
    EXPECT_EQ(0, card0.ident);
    EXPECT_EQ(1, card0.value);
    EXPECT_STREQ(EMPTY_WSTRING.c_str(), card0.image_path.c_str());
    EXPECT_STREQ("AC", card0.text.c_str());

    // tests all stuff for every card
    StandardCard card;
    int i = 0;
    for (char id : {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K'}) {
        for (char color : {'C', 'D', 'H', 'S'}) {
            card.set(i);

            if (i < 4) {
                EXPECT_TRUE(card0 == card);
                EXPECT_FALSE(card0 != card);
                EXPECT_FALSE(card0 < card);
                EXPECT_TRUE(card0 <= card);
                EXPECT_FALSE(card0 > card);
                EXPECT_TRUE(card0 >= card);
            }
            else {
                EXPECT_FALSE(card0 == card);
                EXPECT_TRUE(card0 != card);
                EXPECT_TRUE(card0 < card);
                EXPECT_TRUE(card0 <= card);
                EXPECT_FALSE(card0 > card);
                EXPECT_FALSE(card0 >= card);
            }

            EXPECT_EQ(i, card.ident);
            EXPECT_EQ(i / 4 + 1, card.value);
            EXPECT_STREQ(EMPTY_WSTRING.c_str(), card.image_path.c_str());
            EXPECT_STREQ(std::format("{:c}{:c}", id, color).c_str(), card.text.c_str());

            switch (color)
            {
            case 'C':
                EXPECT_EQ(StandardCard::EColor::E_CLUB, card.get_color());
                break;
            case 'D':
                EXPECT_EQ(StandardCard::EColor::E_DIAMOND, card.get_color());
                break;
            case 'H':
                EXPECT_EQ(StandardCard::EColor::E_HEART, card.get_color());
                break;
            case 'S':
                EXPECT_EQ(StandardCard::EColor::E_SPADE, card.get_color());
                break;
            default:
                ADD_FAILURE();
                break;
            }

            EXPECT_FALSE(card.is_joker());

            ++i;
        }
    }

    card.set(i);
    EXPECT_EQ(i, card.ident);
    EXPECT_EQ(i / 4 + 1, card.value);
    EXPECT_STREQ(EMPTY_WSTRING.c_str(), card.image_path.c_str());
    EXPECT_STREQ("JR", card.text.c_str());
    EXPECT_TRUE(card.is_joker());
    EXPECT_FALSE(card0 == card);
    EXPECT_TRUE(card0 != card);
    EXPECT_TRUE(card0 < card);
    EXPECT_TRUE(card0 <= card);
    EXPECT_FALSE(card0 > card);
    EXPECT_FALSE(card0 >= card);

    ++i;

    card.set(i);
    EXPECT_EQ(i, card.ident);
    EXPECT_EQ(i / 4 + 1, card.value);
    EXPECT_STREQ(EMPTY_WSTRING.c_str(), card.image_path.c_str());
    EXPECT_STREQ("JB", card.text.c_str());
    EXPECT_TRUE(card.is_joker());
    EXPECT_FALSE(card0 == card);
    EXPECT_TRUE(card0 != card);
    EXPECT_TRUE(card0 < card);
    EXPECT_TRUE(card0 <= card);
    EXPECT_FALSE(card0 > card);
    EXPECT_FALSE(card0 >= card);


}
