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
#include <algorithm>
#include <cstdint>
#include <exception>
#include <format>
#include <filesystem>

#include "pltr/core/object.h"
#include "pltr/playing_cards/playing_cards.h"
#include "pltr/core/template_utils.h"


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* Cards colors enumeration.
    */
    enum class EColor : std::uint8_t //!< the standard colors for standard playing cards
    {
        E_CLUB, E_DIAMOND, E_HEART, E_SPADE, E_RED, E_BLACK
    };


    //=======================================================================
    /* \brief The InvalidIdent exception for standard cards. Raised when an ident value is out of bounds [0, 53].
    */
    struct StandardInvalidIdent : public std::exception
    {
        std::string _msg;

        inline StandardInvalidIdent(const int ident)
            : _msg{ std::format("'{}' is an invalid identifier for standard cards (0 <= ident <= 53)", ident) }
        {}

        std::string& what()
        {
            return this->_msg;
        }

    };


    //=======================================================================
    /* \brief The base class for standard cards.
    */
    template<
        const pltr::core::StringTemplateParameter _CARDS_LETTERS = "23456789XJQKAJ",
        const pltr::core::StringTemplateParameter _COLORS_LETTERS = "CDHS",
        const pltr::core::StringTemplateParameter _JOKERS_COLORS = "RB",
        const std::uint32_t _START_VALUE = 2,
        const std::uint32_t _START_INDEX = 0,
        const std::uint32_t _END_INDEX = 54
    >
    class StandardCard : public pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>
    {
    public:
        //-----   Types wrappers   -----//
        using MyBaseClass = pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>;
        using IdentT = MyBaseClass::ident_type;
        using ValueT = MyBaseClass::value_type;

        using MyClassType = StandardCard<_CARDS_LETTERS, _COLORS_LETTERS, _JOKERS_COLORS>;


        //-----   constants   -----//
        static inline constexpr ValueT START_VALUE{ _START_VALUE };

        static inline constexpr IdentT CARDS_PER_COLOR{ 13 };
        static inline constexpr IdentT COLORS_COUNT{ 4 };

        static inline constexpr IdentT JOKERS_FIRST_IDENT{ COLORS_COUNT * CARDS_PER_COLOR };
        static inline constexpr IdentT JOKERS_INDEX{ CARDS_PER_COLOR };


        //-----   Constructors / Desctructor   -----//
        inline StandardCard()                                           //!< empty constructor.
            : MyBaseClass(_START_INDEX, _START_VALUE)
        {
            _check_ident();
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_
        )                                                               //!< 1-valued constructor.
            : MyBaseClass(ident_, ValueT((ident_ - _START_INDEX) / 4 + _START_VALUE))
        {
            _check_ident();
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_
        )                                                               //!< 2-valued constructor (1/2).
            : MyBaseClass(ident_, value_)
        {
            _check_ident();
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const std::filesystem::path& image_path_
        )                                                               //!< 2-valued constructor (2/2).
            : MyBaseClass(ident_, ValueT((ident_ - _START_INDEX) / 4 + _START_VALUE), image_path_)
        {
            _check_ident();
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_
        )                                                               //!< 3-valued constructor (1/2).
            : MyBaseClass(ident_, value_, ordering_value_)
        {
            _check_ident();
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_
        )                                                               //!< 3-valued constructor (2/2).
            : MyBaseClass(ident_, value_, image_path_)
        {
            _check_ident();
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_,
            const std::filesystem::path& image_path_
        )                                                               //!< 4-valued constructor.
            : MyBaseClass(ident_, value_, ordering_value_, image_path_)
        {
            _check_ident();
            _set_text();
        }

        inline StandardCard(const StandardCard&) noexcept = default;    //!< default copy constructor.
        inline StandardCard(StandardCard&&) noexcept = default;         //!< default move constructor.

        inline virtual ~StandardCard() noexcept = default;              //!< default destructor.


        //-----   Operators   -----//
        StandardCard& operator=(const StandardCard&) noexcept = default;    //!< default copy operator.
        StandardCard& operator=(StandardCard&&) noexcept = default;         //!< default move operator.


        //-----   Accessors / Mutators   -----//
        [[nodiscard]]
        inline const EColor get_color() const noexcept                      //!< returns the enum color of this card
        {
            return is_joker() ? EColor(this->ident - JOKERS_FIRST_IDENT + 4) : EColor(this->ident % COLORS_COUNT);
        }


        [[nodiscard]]
        inline const bool is_joker() const noexcept                         //!< returns true if this card is a Joker one
        {
            return this->ident >= JOKERS_FIRST_IDENT;
        }


        inline void set(const IdentT ident_)                                //!< sets data (1 arg).
        {
            _check_ident();
            set(ident_, (ident_ - _START_INDEX) / 4 + _START_VALUE);
        }


        inline void set(const IdentT ident_, const ValueT value_)           //!< sets data (2 args).
        {
            _check_ident();
            MyBaseClass::set(ident_, value_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_
        )                                                                   //!< sets data (3 args, 1/2).
        {
            MyBaseClass::set(ident_, value_, ordering_value_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_)                       //!< sets data (3 args, 2/2).
        {
            MyBaseClass::set(ident_, value_, image_path_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_,
            const std::filesystem::path& image_path_)                       //!< sets data (4 args).
        {
            MyBaseClass::set(ident_, value_, ordering_value_, image_path_);
            _set_text();
        }


    protected:
        inline virtual const std::string _get_object_name() const noexcept override  //!< returns the name of the object. Overridden from base class pltr::core::Object.
        {
            return this->text;
        }


        void _set_text() noexcept  //!< internally sets the text of this card
        {
            const char face_letter{ _CARDS_LETTERS[this->ident / COLORS_COUNT] };
            const int color_index{ int(get_color()) };
            const char color_letter{ color_index < COLORS_COUNT ? _COLORS_LETTERS[color_index] : _JOKERS_COLORS[color_index - COLORS_COUNT] };

            this->text = std::format("{:c}{:c}", face_letter, color_letter);
        }


    private:
        inline void _check_ident()  //!< throws exception if internal value of ident is out of bounds
        {
            if (this->ident < _START_INDEX || this->ident >= _END_INDEX)
                throw pltr::cards::StandardInvalidIdent(this->ident);
        }
    };


    //=======================================================================
    /* \brief The class for standard cards - German localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardCardDe = StandardCard<"23456789XBDK1J", "RAHP", "RS", 2, START_INDEX, LAST_INDEX>;  // notice: RAHP für kReuz, kAro, Herz, Pik


    //=======================================================================
    /* \brief The class for standard cards - English localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardClassEn = StandardCard<"23456789XJQKAJ", "CDHS", "RB", 2, START_INDEX, LAST_INDEX>;


    //=======================================================================
    /* \brief The class for standard cards - Spanish localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardCardEs = StandardCard<"23456789XJAR1J", "TDCE", "RN", 2, START_INDEX, LAST_INDEX>;  // notice: JARJ para Jota, reinA, Rey, Joker ; TDCE para Tréboles, Diamantes; Corazón, Espadas


    //=======================================================================
    /* \brief The class for standard cards - French localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardCardFr = StandardCard<"23456789XVDR1J", "TKCP", "RN", 2, START_INDEX, LAST_INDEX>;  // notice: TKCP pour Trèfle, (K)arreau, Coeur, Pique


    //=======================================================================
    /* \brief The class for standard cards - Italian localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardCardIt = StandardCard<"23456789XJAR1J", "MQCP", "RN", 2, START_INDEX, LAST_INDEX>;  // notice: JARJ per Jack, reginA, Re, Joker ; MQCP per Mazze, Quadri, Cuore, Picche


    //=======================================================================
    /* \brief The class for Windows console standard cards.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardWindowsConsoleCard = StandardCard<"23456789XJQKAJ", "\005\004\003\006", "RB", 2, START_INDEX, LAST_INDEX>;


    //=======================================================================
    /* \brief The class for Windows console standard cards - German localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardWindowsConsoleCardDe = StandardCard<"23456789XBDK1J", "\005\004\003\006", "RS", 2, START_INDEX, LAST_INDEX>;


    //=======================================================================
    /* \brief The class for Windows console standard cards - English localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardWindowsConsoleClassEn = StandardWindowsConsoleCard<START_INDEX, LAST_INDEX>;  // that's all!


    //=======================================================================
    /* \brief The class for Windows console standard cards - Spanish localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardWindowsConsoleCardEs = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN", 2, START_INDEX, LAST_INDEX>;


    //=======================================================================
    /* \brief The class for Windows console standard cards - French localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardWindowsConsoleCardFr = StandardCard<"23456789XVDR1J", "\005\004\003\006", "RN", 2, START_INDEX, LAST_INDEX>;


    //=======================================================================
    /* \brief The class for Windows console standard cards - Italian localization.
    */
    template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
    using StandardWindowsConsoleCardIt = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN", 2, START_INDEX, LAST_INDEX>;


    //=======================================================================
    // Local type traits concepts

    template<typename T>
    struct is_standard_card {
        static inline constexpr bool value{ false };
    };

    template<typename T>
    inline constexpr bool is_standard_card_v = is_standard_card<T>::value;


    template<>
    struct is_standard_card<StandardCard<>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardCardDe<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardCardEs<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardCardFr<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardCardIt<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardWindowsConsoleCard<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardWindowsConsoleCardDe<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardWindowsConsoleCardEs<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardWindowsConsoleCardFr<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };

    /* Notice: 'It' template version is exactly the same as 'Es' one. No need to set this specialization twice!
    template<const std::uint32_t START_INDEX, const std::uint32_t LAST_INDEX>
    struct is_standard_card<StandardWindowsConsoleCardIt<START_INDEX, LAST_INDEX>> {
        static inline constexpr bool value{ true };
    };
    */

}