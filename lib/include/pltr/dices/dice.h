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
#include "pltr/dices/face.h"
#include "pltr/core/object.h"
#include "pltr/core/random.h"


//===========================================================================
namespace pltr::dices
{
    //=======================================================================
    /* \brief The generic template for dices.
    */
    template<
        typename FaceT = pltr::dices::Face<>,
        typename PRNGT = std::mt19937_64
    >
    class Dice : public pltr::core::Object
    {
    public:
        //-----   Types wrappers   -----//
        using FaceType = FaceT;
        using ValueType = typename FaceType::value_type;


        //-----   Constructors / Desctructor   -----//
        inline Dice() noexcept = default;                                       //!< default empty constructor.

        inline Dice(const std::vector<FaceT>& faces);                           //!< initialization constructor. Throws exception if vector size is less than 2.

        template<typename... RestT>
        inline Dice(const FaceT& first, const RestT&... rest);                  //!< constructor with variable arguments length. Throws exception if size of rest is 0.

        inline Dice(const Dice&) noexcept = default;                            //!< default copy constructor.
        inline Dice(Dice&&) noexcept = default;                                 //!< default move constructor.

        virtual inline ~Dice() noexcept = default;                              //!< default destructor.


        //-----   Operators   -----//
        inline Dice& operator= (const Dice&) noexcept = default;                //!< default copy assignment.
        inline Dice& operator= (Dice&&) noexcept = default;                     //!< default copy assignment.

        [[nodiscard]]
        inline ValueType& operator[] (const std::uint32_t num_face);              //!< mutable indexing operator. Face numbers start at 0. Throws exception if out of bound.

        [[nodiscard]]
        inline const ValueType& operator[] (const std::uint32_t num_face) const;  //!< not mutable indexing operator. Face numbers start at 0. Throws exception if out of bound.

        [[nodiscard]]
        inline const bool operator== (const Dice& other) const noexcept;        //!< equality operator.

        [[nodiscard]]
        inline const bool operator!= (const Dice& other) const noexcept;        //!< non equality operator.

        [[nodiscard]]
        inline const bool operator< (const Dice& other) const noexcept;         //!< less-than comparison operator.

        [[nodiscard]]
        inline const bool operator<= (const Dice& other) const noexcept;        //!< less-than-or-equal comparison operator.

        [[nodiscard]]
        inline const bool operator> (const Dice& other) const noexcept;         //!< greater-than comparison operator.

        [[nodiscard]]
        inline const bool operator>= (const Dice& other) const noexcept;        //!< greater-than-or-equal comparison operator.


        //-----   Accessors / Mutators   -----//
        inline const std::uint32_t faces_count() const noexcept;                //!< returns the number of faces for this dice.

        inline const FaceT& force_upper_face(const std::uint32_t num_face);       //!< forces the upper face of this dice.  Throws exception if out of bound.

        inline const float get_last_rotation_angle() const noexcept;            //!< returns the rotation angle of the dice got on last roll_with_angle call (degrees, [0.0, 360.0]).

        inline const FaceT& get_upper_face() const noexcept;                    //!< returns the current upper face of this dice.


        //-----   Operations   -----//
        const FaceT& roll();                                                    //!< rolls this dice and returns the new upper face. Throws error if dice is not initialized.

        const FaceT& roll_with_angle();                                         //!< rolls this dice, returns the new upper face and sets a rotation angle. Throws error if dice is not initialized.

        const FaceT& roll_with_angle(float& angle);                             //!< rolls this dice, returns the new upper face and gets a rotation angle. Throws error if dice is not initialized.

        void set(const std::vector<FaceT>& faces);                              //!< sets this dice faces with an initialization vector. Throws exception if less than 2 faces.


    private:
        //-----   Attributes   -----//
        std::vector<FaceT> _faces{};    //!< the list of faces for this dice.
        FaceT _upper_face{};            //!< the upper face of this dice once rolled.
        float _rotation_angle{};        //!< once rolled, the rotation angle of the upper face of this dice.


        //-----   Operations   -----//
        inline void _set() noexcept;                                        //!< end of faces list for this deck. Should not be called by library user - does nothing.

        template<typename... RestT>
        void _set(const FaceT& first, const RestT&... rest) noexcept;       //!< sets faces according to variable length of arguments.

    };


    //=======================================================================
    // Local implementations

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline Dice<FaceT, PRNGT>::Dice(const std::vector<FaceT>& faces)
        : pltr::core::Object()
    {
        // reminder: initialization constructor. Throws exception if vector size is less than 2.
        set(faces);
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    template<typename... RestT>
    inline Dice<FaceT, PRNGT>::Dice(const FaceT& first, const RestT&... rest)
        : pltr::core::Object()
    {
        // reminder: constructor with variable arguments length. Throws exception if size of rest is 0.
        if (sizeof...(RestT) == 0) {
            // dices with only 1 face are invalid
            throw pltr::dices::InvalidDice(1);
        }
        else {
            _set(first, rest...);
        }
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline Dice<FaceT, PRNGT>::ValueType& Dice<FaceT, PRNGT>::operator[] (const std::uint32_t num_face)
    {
        // reminder: mutable indexing operator.
        if (num_face >= this->faces_count())
            throw pltr::dices::InvalidFaceIndex(num_face, this->faces_count());
        return this->_faces[num_face].value;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const FaceT& Dice<FaceT, PRNGT>::force_upper_face(const std::uint32_t num_face)
    {
        // reminder: forces the upper face of this dice.  Throws exception if out of bound.
        if (num_face >= this->faces_count())
            throw pltr::dices::InvalidFaceIndex(num_face, this->faces_count());
        this->_upper_face = this->_faces[num_face];
        return this->_upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const Dice<FaceT, PRNGT>::ValueType& Dice<FaceT, PRNGT>::operator[] (const std::uint32_t num_face) const
    {
        // reminder: not mutable indexing operator.
        if (num_face >= this->faces_count())
            throw pltr::dices::InvalidFaceIndex(num_face, this->faces_count());
        return this->faces[num_face].value;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const bool Dice<FaceT, PRNGT>::operator== (const Dice& other) const noexcept
    {
        // reminder: equality operator.
        return this->_upper_face == other._upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const bool Dice<FaceT, PRNGT>::operator!= (const Dice& other) const noexcept
    {
        // reminder: non equality operator.
        return this->_upper_face != other._upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const bool Dice<FaceT, PRNGT>::operator< (const Dice& other) const noexcept
    {
        // reminder: less-than comparison operator.
        return this->_upper_face < other._upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const bool Dice<FaceT, PRNGT>::operator<= (const Dice& other) const noexcept
    {
        // reminder: less-than-or-equal comparison operator.
        return this->_upper_face <= other._upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const bool Dice<FaceT, PRNGT>::operator> (const Dice& other) const noexcept
    {
        // reminder: greater-than comparison operator.
        return this->_upper_face > other._upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const bool Dice<FaceT, PRNGT>::operator>= (const Dice& other) const noexcept
    {
        // reminder: greater-than-or-equal comparison operator.
        return this->_upper_face >= other._upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const std::uint32_t Dice<FaceT, PRNGT>::faces_count() const noexcept
    {
        // reminder: returns the number of faces for this dice.
        return std::uint32_t(this->_faces.size());
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const float Dice<FaceT, PRNGT>::get_last_rotation_angle() const noexcept
    {
        // reminder: returns the rotation angle of the dice got on last roll_with_angle call (degrees, [0.0, 360.0]).
        return this->_rotation_angle;
    }
    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline const FaceT& Dice<FaceT, PRNGT>::get_upper_face() const noexcept
    {
        // reminder: returns the current upper face of this dice.
        return this->_upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    const FaceT& Dice<FaceT, PRNGT>::roll()
    {
        // reminder: rolls this dice.
        const std::uint32_t index{ pltr::core::Random<PRNGT>::urand<std::uint32_t>(0, this->faces_count() - 1)};

        return this->_upper_face = this->_faces[index];
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    const FaceT& Dice<FaceT, PRNGT>::roll_with_angle()
    {
        // reminder: rolls this dice and gets a rotation angle.
        // so, rolls the dice to get its upper face
        roll();
        // then evaluates its rotation angle
        this->_rotation_angle = pltr::core::Random<PRNGT>::urand(0.0f, 360.0f);
        return this->_upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    const FaceT& Dice<FaceT, PRNGT>::roll_with_angle(float& angle)
    {
        // reminder: rolls this dice, returns the new upper face and gets a rotation angle.
        roll_with_angle();
        angle = this->_rotation_angle;
        return this->_upper_face;
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    inline void Dice<FaceT, PRNGT>::_set() noexcept
    {
        // reminder: end of faces list for this deck. Should not be called by library user - does nothing.
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    template<typename... RestT>
    void Dice<FaceT, PRNGT>::_set(const FaceT& first, const RestT&... rest) noexcept
    {
        // reminder: sets faces according to variable length of arguments.
        this->_faces.push_back(first);
        _set(rest...);
    }

    //-----------------------------------------------------------------------
    template<typename FaceT, typename PRNGT>
    void Dice<FaceT, PRNGT>::set(const std::vector<FaceT>& faces)
    {
        // reminder: sets this dice faces with an initialization vector. Throws exception if less than 2 faces.
        const std::int32_t faces_count{ std::int32_t(faces.size()) };
        if (faces_count < 2) {
            throw pltr::dices::InvalidDice(faces_count);
        }
        else {
            this->_faces = faces;
        }
    }

}