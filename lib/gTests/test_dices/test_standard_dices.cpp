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

#include <cstdint>
#include <string>

#include "pltr/dices/standard_dice.h"


//===========================================================================
TEST(TestSuiteDices, TestStandardDices) {

    // Different dices types
    using Dice6 = pltr::dices::StandardDice<>;
    using Dice10 = pltr::dices::StandardDice<std::uint8_t>;
    using Dice100 = pltr::dices::StandardDice<std::uint16_t>;

    // Different dices
    Dice6 dice6a;
    Dice6 dice6b;
    Dice10 dice10(10);
    Dice100 dice100(10, 0, 10);
    Dice100 dice_1_100(100, 1);


    // Tests erroneouos dices declarations
    EXPECT_THROW({
        try {
            pltr::dices::StandardDice<> dice_err(1, 1, 1);
        }
        catch (pltr::dices::InvalidDice& e) {
            EXPECT_STREQ("dices must be declared with at least two faces, '1' is an invalid value", e.what().c_str());
            throw e;
        }
    }, pltr::dices::InvalidDice);

    EXPECT_THROW({
        try {
            pltr::dices::StandardDice<std::int8_t> dice_err(-1, 15, 10);
        }
        catch (pltr::dices::InvalidDice& e) {
            EXPECT_STREQ("dices must be declared with at least two faces, '-1' is an invalid value", e.what().c_str());
            throw e;
        }
    }, pltr::dices::InvalidDice);


    // Tests Dices 6 faces
    EXPECT_EQ(6, dice6a.faces_count());
    EXPECT_EQ(6, dice6b.faces_count());
    
    for (int i = 0; i < 10'000; ++i) {
        const Dice6::ValueType value = dice6a.roll();
        EXPECT_LE(1, int(value));
        EXPECT_GE(6, int(value));
    }

    for (int i = 0; i < 10'000; ++i) {
        const Dice10::ValueType value = dice10.roll();
        EXPECT_LE(1,  int(value));
        EXPECT_GE(10, int(value));
    }

    for (int i = 0; i < 10'000; ++i) {
        const Dice100::ValueType value = dice100.roll();
        EXPECT_LE(0,   int(value));
        EXPECT_GE(90, int(value));
        EXPECT_EQ(0, value % 10);
    }

    for (int i = 0; i < 10'000; ++i) {
        const Dice100::ValueType value = dice_1_100.roll();
        EXPECT_LE(1,   int(value));
        EXPECT_GE(100, int(value));
    }

    float angle;
    for (int i = 0; i < 10'000; ++i) {
        const Dice100::ValueType value = dice_1_100.roll_with_angle(angle);
        EXPECT_LE(1, int(value));
        EXPECT_GE(100, int(value));
        EXPECT_LE(0.0f, angle);
        EXPECT_GE(360.0f, angle);
        EXPECT_EQ(angle, dice_1_100.get_last_rotation_angle());
        
        dice100.roll_with_angle();
        EXPECT_LE(0.0f, dice100.get_last_rotation_angle());
        EXPECT_GE(360.0f, dice100.get_last_rotation_angle());
    }

}
