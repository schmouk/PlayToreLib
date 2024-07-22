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

module;

#include <cstdint>
#include <filesystem>


export module pltr:cards;


//===========================================================================
export namespace pltr::cards
{
    //=======================================================================
    /* \brief The generic template for all playing cards.
    */
    export template<
        typename IdentT = char,
        typename ValueT = std::int32_t
    > struct PlayingCardT
    {
        //-----   Data   -----//
        IdentT ident{};
        ValueT value{};
        std::filesystem::path image_path{};


        //-----   Constructors / Desctructor   -----//
        inline PlayingCardT() noexcept = default;                               //!< default empty constructor.


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_
        ) noexcept                                                              //!< 2-valued constructor.
            : ident(ident)
            , value(value_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_
        ) noexcept                                                              //!< 3-valued constructor.
            : ident(ident)
            , value(value_)
            , image_path(image_path_)
        {}

        inline PlayingCardT(const PlayingCardT&) noexcept = default;            //!< default copy constructor.
        inline PlayingCardT(PlayingCardT&&) noexcept = default;                 //!< default move constructor.

        inline virtual ~PlayingCardT() noexcept = default;                      //!< default destructor.


        //-----   Operators   -----//
        inline PlayingCardT& operator=(const PlayingCardT&) noexcept = default; //!< default copy assignment.
        inline PlayingCardT& operator=(PlayingCardT&&) noexcept = default;      //!< default move assignment.


        inline const bool operator< (const PlayingCardT& other) const noexcept  //!< less-than operator.
        {
            return this->value < other.value;
        }


        inline const bool operator== (const PlayingCardT& other) const noexcept  //!< equality operator.
        {
            return this->value == other.value;
        }


        //-----   Mutators   -----//
        inline void set(const IdentT ident_, const ValueT value_) noexcept      //!< sets data.
        {
            ident = ident_;
            value = value_;
        }

        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_) noexcept                  //!< sets data.
        {
            ident = ident_;
            value = value_;
            image_path = image_path_;
        }

    };

}