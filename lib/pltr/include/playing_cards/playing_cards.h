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
#include <filesystem>
#include <string>

#include "core/object.h"


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* \brief The generic template for all playing cards.
    */
    template<
        typename IdentT = char,
        typename ValueT = std::int32_t
    > struct PlayingCardT : public pltr::core::Object
    {
        //-----   Types wrappers   -----//
        using ident_type = IdentT;
        using value_type = ValueT;


        //-----   Data   -----//
        std::filesystem::path image_path{};
        std::string text{};
        IdentT ident{};
        ValueT ordering_value{};
        ValueT value{};


        //-----   Constructors / Desctructor   -----//
        inline PlayingCardT() noexcept = default;                               //!< default empty constructor.


        inline PlayingCardT(const IdentT ident_) noexcept                       //!< 1-arg constructor.
            : pltr::core::Object()
            , ident(ident_)
            , value(ValueT(ident_))
            , ordering_value(ValueT(ident_))
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_
        ) noexcept                                                              //!< 2-args constructor with value.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(value_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const std::filesystem::path& image_path_
        ) noexcept                                                              //!< 2-args constructor with image path.
            : pltr::core::Object()
            , ident(ident_)
            , value(ValueT(ident_))
            , ordering_value(ValueT(ident_))
            , image_path(image_path_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const std::string& text_
        ) noexcept                                                              //!< 2-args constructor with text.
            : pltr::core::Object()
            , ident(ident_)
            , value(ValueT(ident_))
            , ordering_value(ValueT(ident_))
            , text(text_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_
        ) noexcept                                                              //!< 3-args constructor with value and ordering value.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(ordering_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_
        ) noexcept                                                              //!< 3-args constructor with value and image path.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(value_)
            , image_path(image_path_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const std::string& text_
        ) noexcept                                                              //!< 3-args constructor with value and text.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(value_)
            , text(text_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const std::filesystem::path& image_path_,
            const std::string& text_
        ) noexcept                                                              //!< 3-args constructor with image path and text.
            : pltr::core::Object()
            , ident(ident_)
            , value(ValueT(ident_))
            , ordering_value(ValueT(ident_))
            , image_path(image_path_)
            , text(text_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_,
            const std::filesystem::path& image_path_
        ) noexcept                                                              //!< 4-args constructor with value, ordering value and image path.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(ordering_)
            , image_path(image_path_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_,
            const std::string& text_
        ) noexcept                                                              //!< 4-args constructor with value, ordering value and text.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(ordering_)
            , text(text_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_,
            const std::string& text_
        ) noexcept                                                              //!< 4-args constructor with value, image path and text.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(value_)
            , image_path(image_path_)
            , text(text_)
        {}


        inline PlayingCardT(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_,
            const std::filesystem::path& image_path_,
            const std::string& text_
        ) noexcept                                                              //!< 5-args constructor.
            : pltr::core::Object()
            , ident(ident_)
            , value(value_)
            , ordering_value(ordering_)
            , image_path(image_path_)
            , text(text_)
        {}


        inline PlayingCardT(const PlayingCardT&) noexcept = default;            //!< default copy constructor.
        inline PlayingCardT(PlayingCardT&&) noexcept = default;                 //!< default move constructor.

        inline virtual ~PlayingCardT() noexcept = default;                      //!< default destructor.


        //-----   Operators   -----//
        inline PlayingCardT& operator=(const PlayingCardT&) noexcept = default; //!< default copy assignment.
        inline PlayingCardT& operator=(PlayingCardT&&) noexcept = default;      //!< default move assignment.

        [[nodiscard]]
        inline const bool operator< (const PlayingCardT& other) const noexcept  //!< less-than operator.
        {
            return this->value < other.value;
        }


        [[nodiscard]]
        inline const bool operator> (const PlayingCardT& other) const noexcept  //!< greater-than operator.
        {
            return this->value > other.value;
        }


        [[nodiscard]]
        inline const bool operator<= (const PlayingCardT& other) const noexcept  //!< less-than-or-equal operator.
        {
            return !(*this > other);
        }


        [[nodiscard]]
        inline const bool operator>= (const PlayingCardT& other) const noexcept  //!< greater-than-or-equal operator.
        {
            return !(*this < other);
        }


        [[nodiscard]]
        inline const bool operator== (const PlayingCardT& other) const noexcept  //!< equality operator.
        {
            return this->value == other.value;
        }


        [[nodiscard]]
        inline const bool operator!= (const PlayingCardT& other) const noexcept  //!< not-equality operator.
        {
            return this->value != other.value;
        }


        //-----   Mutators   -----//
        inline void set(const IdentT ident_, const ValueT value_) noexcept      //!< sets data.
        {
            ident = ident_;
            value = value_;
            ordering_value = value_;
        }

        inline void set(const IdentT ident_, const ValueT value_, const ValueT ordering_value_) noexcept      //!< sets data.
        {
            set(ident_, value_);
            ordering_value = ordering_value_;
        }

        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_) noexcept                  //!< sets data.
        {
            set(ident_, value_);
            image_path = image_path_;
        }

        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_,
            const std::filesystem::path& image_path_) noexcept                  //!< sets data.
        {
            set(ident_, value_, ordering_value_);
            image_path = image_path_;
        }

        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_,
            const std::string& text_) noexcept                                  //!< sets data.
        {
            set(ident_, value_);
            image_path = image_path_;
            text = text_;
        }

        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_,
            const std::filesystem::path& image_path_,
            const std::string& text_) noexcept                                  //!< sets data.
        {
            set(ident_, value_, ordering_value_);
            image_path = image_path_;
            text = text_;
        }


        //-----   Operations   -----//
        virtual inline void action()                                            //!< actions to be processed when this card is played
        {
            // does nothing in this base class
            // to be overridden in inheriting classes if this gets meaning.
        }


        virtual inline void draw()                                              //!< draws this card (caution: this is a drawing action on screen, not from a deck!)
        {
            // does nothing in this base class
            // to be overridden in inheriting classes if this gets meaning.
        }

    };

}