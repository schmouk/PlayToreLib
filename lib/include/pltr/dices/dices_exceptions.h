#pragma once

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
#include <cstdint>
#include <exception>
#include <format>


//===========================================================================
namespace pltr::dices
{
    //=======================================================================
    /* \brief The InvalidDice exception. Raised when a dice is initalized with less than 2 faces.
    */
    struct InvalidDice : public std::exception
    {
        std::string _msg;

        inline InvalidDice(const std::int32_t faces_count)
            : _msg{ std::format("dices must be declared with at least two faces, '{}' is an invalid value", faces_count) }
        {}

        std::string& what()
        {
            return this->_msg;
        }

    };


    //=======================================================================
    /* \brief The InvalidDiceValue exception for dices. Raised when forced value for dice is invalid.
    */
    template<typename ValueT = std::int32_t>
        requires std::is_integral_v<ValueT>
    struct InvalidDiceValue : public std::exception
    {
        std::string _msg;

        inline InvalidDiceValue(const ValueT dice_value)
            : _msg{ std::format("'{}' is an invalid value for dice", dice_value) }
        {}

        std::string& what()
        {
            return this->_msg;
        }

    };


    //=======================================================================
    /* \brief The InvalidFaceIndex exception for dices. Raised when face index is out of range.
    */
    struct InvalidFaceIndex : public std::exception
    {
        std::string _msg;

        inline InvalidFaceIndex(const std::uint32_t face_index, const std::uint32_t max_index)
            : _msg{ std::format("out of bounds indexing of dice ({} > {})", face_index, std::int32_t(max_index) - 1) }
        {}

        std::string& what()
        {
            return this->_msg;
        }

    };

}