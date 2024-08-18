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

#include "pltr/dices/face.h"


//===========================================================================
TEST(TestSuiteDicess, TestFaces) {

    pltr::dices::Face<> face_int;
    EXPECT_EQ(0, face_int.value);

    const std::uint32_t VALUE{ std::uint32_t(0x1'ffff'ffff) };
    pltr::dices::Face<std::uint32_t> face32(VALUE);
    EXPECT_EQ(VALUE, face32.value);

    pltr::dices::Face<std::string> face_str("Joker");
    EXPECT_STREQ("Joker", face_str.value.c_str());
    EXPECT_STRNE("joker", face_str.value.c_str());

}
