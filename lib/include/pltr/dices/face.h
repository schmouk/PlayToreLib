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
#include <concepts>
#include <cstdint>

#include "pltr/core/object.h"


//===========================================================================
namespace pltr::dices
{
    //=======================================================================
    /* \brief The generic template for faces of dices.
    */
    template<typename ValueT = std::int8_t>
        requires std::equality_comparable<ValueT>
    struct Face : public pltr::core::Object
    {
        //-----   Types wrappers   -----//
        using value_type = ValueT;


        //-----   Attributes   -----//
        ValueT value{};


        //-----   Constructors / Desctructor   -----//
        inline Face() noexcept = default;                               //!< default empty constructor.

        inline Face(const ValueT& value_) noexcept                      //!< initialization constructor.
            : value(value_)
        {}

        inline Face(const Face&) noexcept = default;                    //!< default copy constructor.
        inline Face(Face&&) noexcept = default;                         //!< default move constructor.

        virtual inline ~Face() noexcept = default;                      //!< default destructor.


        //-----   Operators   -----//
        inline Face& operator= (const Face&) noexcept = default;        //!< default copy assignment.
        inline Face& operator= (Face&&) noexcept = default;             //!< default copy assignment.

        [[nodiscard]]
        inline const bool operator== (const Face& other) const noexcept //!< equality operator
        {
            return this->value == other.value;
        }


        //-----   Operations   -----//
        virtual inline void action()                                    //!< actions to be processed that are associated with this face of dise
        {
            // does nothing in this base class
            // to be overridden in inheriting classes if this gets meaning.
        }

    };
    
}