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

#include <string>
#include "playing_cards/playing_cards.h"


//===========================================================================
TEST(TestSuitePlayingCards, TestPlayingCard) {
    const std::string EMPTY_STRING;
    const std::wstring EMPTY_WSTRING;

    // tests empty default constructor
    pltr::cards::PlayingCardT<> card0;
    EXPECT_EQ(0, card0.ident);
    EXPECT_EQ(0, card0.value);
    EXPECT_EQ(0, card0.ordering_value);
    EXPECT_STREQ(EMPTY_WSTRING.c_str(), card0.image_path.c_str());
    EXPECT_STREQ(EMPTY_STRING.c_str(), card0.text.c_str());

    // tests 4-args constructor
    pltr::cards::PlayingCardT<> card1(1, 11, "path-1", "txt-1");
    EXPECT_EQ(1, card1.ident);
    EXPECT_EQ(11, card1.value);
    EXPECT_EQ(11, card1.ordering_value);
    EXPECT_STREQ(L"path-1", card1.image_path.c_str());
    EXPECT_STREQ("txt-1", card1.text.c_str());

    // tests 5-args constructor
    pltr::cards::PlayingCardT<> card5(5, 15, 25, "path-5", "txt-5");
    EXPECT_EQ(5, card5.ident);
    EXPECT_EQ(15, card5.value);
    EXPECT_EQ(25, card5.ordering_value);
    EXPECT_STREQ(L"path-5", card5.image_path.c_str());
    EXPECT_STREQ("txt-5", card5.text.c_str());

    // tests operator=
    pltr::cards::PlayingCardT<> card11;
    card11 = card1;
    EXPECT_EQ(1, card11.ident);
    EXPECT_EQ(11, card11.value);
    EXPECT_EQ(11, card11.ordering_value);
    EXPECT_STREQ(L"path-1", card11.image_path.c_str());
    EXPECT_STREQ("txt-1", card11.text.c_str());

    // tests operator <
    EXPECT_TRUE(card0 < card1);
    EXPECT_FALSE(card1 < card0);
    EXPECT_FALSE(card0 < card0);

    // tests operator >
    EXPECT_TRUE(card1 > card0);
    EXPECT_FALSE(card0 > card1);
    EXPECT_FALSE(card0 > card0);
    EXPECT_FALSE(card1 > card1);

    // tests operator <=
    EXPECT_TRUE(card0 <= card1);
    EXPECT_FALSE(card1 <= card0);
    EXPECT_TRUE(card0 <= card0);
    EXPECT_TRUE(card1 <= card1);
    EXPECT_TRUE(card1 <= card11);
    EXPECT_TRUE(card11 <= card1);

    // tests operator >=
    EXPECT_FALSE(card0 >= card1);
    EXPECT_TRUE(card1 >= card0);
    EXPECT_TRUE(card0 >= card0);
    EXPECT_TRUE(card1 >= card1);
    EXPECT_TRUE(card1 >= card11);
    EXPECT_TRUE(card11 >= card1);

    // tests operator==
    EXPECT_TRUE(card0 == card0);
    EXPECT_TRUE(card1 == card1);
    EXPECT_FALSE(card0 == card1);
    EXPECT_FALSE(card1 == card0);
    EXPECT_TRUE(card11 == card1);
    EXPECT_TRUE(card1 == card11);

    // tests operator!=
    EXPECT_FALSE(card0 != card0);
    EXPECT_FALSE(card1 != card1);
    EXPECT_TRUE(card0 != card1);
    EXPECT_TRUE(card1 != card0);
    EXPECT_FALSE(card11 != card1);
    EXPECT_FALSE(card1 != card11);

    // tests set()
    card11.set(11, 21, "path-11", "text-11");
    EXPECT_EQ(11, card11.ident);
    EXPECT_EQ(21, card11.value);
    EXPECT_EQ(21, card11.ordering_value);
    EXPECT_STREQ(L"path-11", card11.image_path.c_str());
    EXPECT_STREQ("text-11", card11.text.c_str());
}
