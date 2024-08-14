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

#include <random>
#include "pltr/core/random.h"


//===========================================================================
TEST(TestSuiteCore, TestRandom) {

    pltr::core::Random rand;
    std::uniform_int_distribution distrib(0, 100);
    std::uniform_real_distribution<float> distribF(0.0f, 1.0f);

    for (int i = 0; i < 100'000; ++i) {
        const int rnd{ rand(distrib) };
        EXPECT_LE(0, rnd) << rnd;
        EXPECT_GE(100, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const float rnd{ rand(distribF) };
        EXPECT_LE(0.0f, rnd) << rnd;
        EXPECT_GT(1.0f, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const int rnd{ rand.urand(1, 6) };
        EXPECT_LE(1, rnd) << rnd;
        EXPECT_GE(6, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const float rnd{ pltr::core::Random<>::urand<float>(10.0f, 12.0f) };
        EXPECT_LE(10.0f, rnd) << rnd;
        EXPECT_GT(12.0f, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const double rnd{ pltr::core::Random<>::urand<double>() };
        EXPECT_LE(0.0, rnd) << rnd;
        EXPECT_GT(1.0, rnd) << rnd;
    }

}

//===========================================================================
TEST(TestSuiteCore, TestRandomThreadSafe) {

    pltr::core::RandomThreadSafe rand;
    std::uniform_int_distribution distrib(0, 100);
    std::uniform_real_distribution<float> distribF(0.0f, 1.0f);

    for (int i = 0; i < 100'000; ++i) {
        const int rnd{ rand(distrib) };
        EXPECT_LE(0, rnd) << rnd;
        EXPECT_GE(100, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const float rnd{ rand(distribF) };
        EXPECT_LE(0.0f, rnd) << rnd;
        EXPECT_GT(1.0f, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const int rnd{ rand.urand(1, 6) };
        EXPECT_LE(1, rnd) << rnd;
        EXPECT_GE(6, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const float rnd{ pltr::core::Random<>::urand<float>(10.0f, 12.0f) };
        EXPECT_LE(10.0f, rnd) << rnd;
        EXPECT_GT(12.0f, rnd) << rnd;
    }

    for (int i = 0; i < 100'000; ++i) {
        const double rnd{ pltr::core::Random<>::urand<double>() };
        EXPECT_LE(0.0, rnd) << rnd;
        EXPECT_GT(1.0, rnd) << rnd;
    }

}
