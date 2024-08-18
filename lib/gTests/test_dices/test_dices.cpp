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

#include "pltr/dices/dice.h"


//===========================================================================
TEST(TestSuiteDices, TestDices) {

    // Types definitions
    using DefaultFace = pltr::dices::Face<int>;
    using DefaultDice = pltr::dices::Dice<DefaultFace>;


    // Tests empty dice
    DefaultDice empty_dice;
    EXPECT_EQ(0, empty_dice.faces_count());
    EXPECT_FLOAT_EQ(0.0f, empty_dice.get_last_rotation_angle());
    EXPECT_EQ(0, empty_dice.get_upper_face().value);

    EXPECT_THROW({
        try {
            const int value = empty_dice[0];
        }
        catch (pltr::dices::InvalidFaceIndex& e) {
            EXPECT_STREQ("out of bounds indexing of dice (0 > -1)", e.what().c_str());
            throw e;
        }
    }, pltr::dices::InvalidFaceIndex);

    EXPECT_THROW({
        try {
            const int value = empty_dice[1];
        }
        catch (pltr::dices::InvalidFaceIndex& e) {
            EXPECT_STREQ("out of bounds indexing of dice (1 > -1)", e.what().c_str());
            throw e;
        }
    }, pltr::dices::InvalidFaceIndex);


    // Tests initialized dice with initialization list
    DefaultDice dice_list({ DefaultFace(1), DefaultFace(22), DefaultFace(333), DefaultFace(4444) });
    EXPECT_EQ(4, dice_list.faces_count());
    EXPECT_FLOAT_EQ(0.0f, dice_list.get_last_rotation_angle());
    EXPECT_EQ(0, dice_list.get_upper_face().value);

    EXPECT_EQ(1, dice_list[0]);
    EXPECT_EQ(22, dice_list[1]);
    EXPECT_EQ(333, dice_list[2]);
    EXPECT_EQ(4444, dice_list[3]);


    // Tests initialized dice with variable arguments list
    DefaultDice dice(DefaultFace(1111), DefaultFace(222), DefaultFace(33), DefaultFace(4), DefaultFace(55555));
    EXPECT_EQ(5, dice.faces_count());
    EXPECT_FLOAT_EQ(0.0f, dice.get_last_rotation_angle());
    EXPECT_EQ(0, dice.get_upper_face().value);

    EXPECT_EQ(1111, dice[0]);
    EXPECT_EQ(222, dice[1]);
    EXPECT_EQ(33, dice[2]);
    EXPECT_EQ(4, dice[3]);
    EXPECT_EQ(55555, dice[4]);

    EXPECT_THROW({
        try {
            const int value = dice[5];
        }
        catch (pltr::dices::InvalidFaceIndex& e) {
            EXPECT_STREQ("out of bounds indexing of dice (5 > 4)", e.what().c_str());
            throw e;
        }
    }, pltr::dices::InvalidFaceIndex);

    EXPECT_THROW({
        try {
            const int value = dice[6];
        }
        catch (pltr::dices::InvalidFaceIndex& e) {
            EXPECT_STREQ("out of bounds indexing of dice (6 > 4)", e.what().c_str());
            throw e;
        }
    }, pltr::dices::InvalidFaceIndex);


    // Tests copy constructor
    DefaultDice dice_copy(dice_list);
    EXPECT_EQ(4, dice_copy.faces_count());
    EXPECT_FLOAT_EQ(0.0f, dice_copy.get_last_rotation_angle());
    EXPECT_EQ(0, dice_copy.get_upper_face().value);

    EXPECT_EQ(1, dice_copy[0]);
    EXPECT_EQ(22, dice_copy[1]);
    EXPECT_EQ(333, dice_copy[2]);
    EXPECT_EQ(4444, dice_copy[3]);


    // Tests copy assignment
    DefaultDice dice2 = dice;
    EXPECT_EQ(5, dice2.faces_count());
    EXPECT_FLOAT_EQ(0.0f, dice2.get_last_rotation_angle());
    EXPECT_EQ(0, dice2.get_upper_face().value);

    EXPECT_EQ(1111, dice2[0]);
    EXPECT_EQ(222, dice2[1]);
    EXPECT_EQ(33, dice2[2]);
    EXPECT_EQ(4, dice2[3]);
    EXPECT_EQ(55555, dice2[4]);


    // Tests comparison btw. dices
    dice.force_upper_face(1);
    dice2.force_upper_face(2);

    EXPECT_EQ(222, dice.get_upper_face().value);
    EXPECT_EQ(33, dice2.get_upper_face().value);
    EXPECT_TRUE(dice > dice2);
    EXPECT_TRUE(dice >= dice2);
    EXPECT_TRUE(dice2 < dice);
    EXPECT_TRUE(dice2 <= dice);
    EXPECT_TRUE(dice != dice2);
    EXPECT_TRUE(dice2 != dice);
    EXPECT_FALSE(dice == dice2);
    EXPECT_FALSE(dice2 == dice);

    dice.force_upper_face(2);
    EXPECT_EQ(33, dice.get_upper_face().value);
    EXPECT_EQ(33, dice2.get_upper_face().value);
    EXPECT_FALSE(dice > dice2);
    EXPECT_TRUE(dice >= dice2);
    EXPECT_FALSE(dice2 < dice);
    EXPECT_TRUE(dice2 <= dice);
    EXPECT_FALSE(dice != dice2);
    EXPECT_FALSE(dice2 != dice);
    EXPECT_TRUE(dice == dice2);
    EXPECT_TRUE(dice2 == dice);


}
