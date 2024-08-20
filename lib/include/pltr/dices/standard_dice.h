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
#include <random>


#include "pltr/dices/dices_exceptions.h"
#include "pltr/core/object.h"
#include "pltr/core/random.h"


//===========================================================================
namespace pltr::dices
{
    //=======================================================================
    /* \brief The generic template for standard dices - i.e. with numbers on faces.
    */
    template<typename ValueT = std::int32_t, typename PRNGT = std::mt19937_64>
        requires std::is_integral_v<ValueT>
    class StandardDice : public pltr::core::Object
    {
    public:
        //-----   Types wrappers   -----//
        using ValueType = ValueT;


        //-----   Attributes   -----//
        ValueT value{};


        //-----   Constructors / Desctructor   -----//
        inline StandardDice(
            const std::int32_t faces_count = 6,
            const ValueT min_value = 1,
            const ValueT step_value = 1
        );                                                                          //!< constructor with initialization values. faces_count must be set to 2 or more: throws an exception if not.

        inline StandardDice(const StandardDice&) noexcept = default;                //!< default copy constructor.
        inline StandardDice(StandardDice&&) noexcept = default;                     //!< default move constructor.

        virtual inline ~StandardDice() noexcept = default;                          //!< default destructor.


        //-----   Operators   -----//
        inline StandardDice& operator= (const StandardDice&) noexcept = default;    //!< default copy assignment.
        inline StandardDice& operator= (StandardDice&&) noexcept = default;         //!< default copy assignment.

        inline StandardDice& operator= (const ValueT new_value);                    //!< forces the value of this dice. May throw InvalidDiceValue exception.

        [[nodiscard]]
        inline const bool operator== (const StandardDice& other) const noexcept;    //!< equality operator.

        [[nodiscard]]
        inline const bool operator!= (const StandardDice& other) const noexcept;    //!< non equality operator.

        [[nodiscard]]
        inline const bool operator< (const StandardDice& other) const noexcept;     //!< less-than comparison operator.

        [[nodiscard]]
        inline const bool operator<= (const StandardDice& other) const noexcept;    //!< less-than-or-equal comparison operator.

        [[nodiscard]]
        inline const bool operator> (const StandardDice& other) const noexcept;     //!< greater-than comparison operator.

        [[nodiscard]]
        inline const bool operator>= (const StandardDice& other) const noexcept;    //!< greater-than-or-equal comparison operator.


        //-----   Accessors / Mutators   -----//
        inline const std::int32_t faces_count() const noexcept;                    //!< returns the number of faces for this dice.

        inline const float get_last_rotation_angle() const noexcept;                //!< returns the rotation angle of the dice got on last roll_with_angle call (degrees, [0.0, 360.0]).


        //-----   Operations   -----//
        const ValueT& roll();                                                       //!< rolls this dice and returns the new upper face. Throws error if dice is not initialized.

        const ValueT& roll_with_angle();                                            //!< rolls this dice, returns the new value of dice and sets a rotation angle. Throws error if dice is not initialized.

        const ValueT& roll_with_angle(float& angle);                                //!< rolls this dice, returns the new value of dice and gets a rotation angle. Throws error if dice is not initialized.


    private:
        //-----   Attributes   -----//
        std::int32_t _faces_count{};
        ValueT _min_value{};
        ValueT _step_value{};
        float _rotation_angle{};  // once rolled, the rotation angle of the upper face of this standard dice.

    };


    //=======================================================================
    // Local implementations

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline StandardDice<ValueT, PRNGT>::StandardDice(
        const std::int32_t faces_count,
        const ValueT min_value,
        const ValueT step_value
    )
        : pltr::core::Object()
        , value(min_value)
        , _faces_count(faces_count)
        , _min_value(min_value)
        , _step_value(step_value)
    {
        // reminder: constructor with initialization values. faces_count must be set to 2 or more: throws an exception if not.
        if (faces_count < 2)
            throw pltr::dices::InvalidDice(faces_count);
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline StandardDice<ValueT, PRNGT>& StandardDice<ValueT, PRNGT>::operator= (const ValueT new_value)
    {
        // reminder: forces the value of this dice. May throw InvalidDiceValue exception.
        if (new_value < this->_min_value ||
            new_value >= this->_min_value + this->_faces_count * this->_step_value ||
            (this->_step_value > 1 && (new_value - this->_min_value) % this->_step_value != 0))
        {
            throw pltr::dices::InvalidDiceValue(new_value);
        }
        else {
            this->value = new_value;
        }
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const bool StandardDice<ValueT, PRNGT>::operator== (const StandardDice& other) const noexcept
    {
        // reminder: equality operator.
        return this->value == other.value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const bool StandardDice<ValueT, PRNGT>::operator!= (const StandardDice& other) const noexcept
    {
        // reminder: non equality operator.
        return this->value != other.value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const bool StandardDice<ValueT, PRNGT>::operator< (const StandardDice& other) const noexcept
    {
        // reminder: less-than comparison operator.
        return this->value < other.value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const bool StandardDice<ValueT, PRNGT>::operator<= (const StandardDice& other) const noexcept
    {
        // reminder: less-than-or-equal comparison operator.
        return this->value <= other.value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const bool StandardDice<ValueT, PRNGT>::operator> (const StandardDice& other) const noexcept
    {
        // reminder: greater-than comparison operator.
        return this->value > other.value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const bool StandardDice<ValueT, PRNGT>::operator>= (const StandardDice& other) const noexcept
    {
        // reminder: greater-than-or-equal comparison operator.
        return this->value >= other.value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const std::int32_t StandardDice<ValueT, PRNGT>::faces_count() const noexcept
    {
        // reminder: returns the number of faces for this dice.
        return this->_faces_count;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    inline const float StandardDice<ValueT, PRNGT>::get_last_rotation_angle() const noexcept
    {
        // reminder: returns the rotation angle of the dice got on last roll_with_angle call (degrees, [0.0, 360.0]).
        return this->_rotation_angle;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    const ValueT& StandardDice<ValueT, PRNGT>::roll()
    {
        // reminder: rolls this dice.
        const std::int32_t index{ pltr::core::Random<PRNGT>::urand(std::int32_t(0), std::int32_t(this->_faces_count - 1)) };

        return this->value = this->_min_value + index * this->_step_value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    const ValueT& StandardDice<ValueT, PRNGT>::roll_with_angle()
    {
        // reminder: rolls this dice, returns the new value of dice and sets a rotation angle. Throws error if dice is not initialized.
        // so, rolls the dice to get its upper face
        roll();
        // then evaluates its rotation angle
        this->_rotation_angle = pltr::core::Random<PRNGT>::urand(0.0f, 360.0f);
        return this->value;
    }

    //-----------------------------------------------------------------------
    template<typename ValueT, typename PRNGT>
        requires std::is_integral_v<ValueT>
    const ValueT& StandardDice<ValueT, PRNGT>::roll_with_angle(float& angle)
    {
        // reminder: rolls this dice, returns the new value of dice and gets a rotation angle. Throws error if dice is not initialized.
        roll_with_angle();
        angle = this->_rotation_angle;
        return this->value;
    }

}