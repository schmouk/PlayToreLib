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
#include <filesystem>

#include "playing_cards/playing_cards.h"
#include "core/template_utils.h"


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
    /* \brief The base class for standard cards.
    */
    template<
        const pltr::core::StringTemplateParameter _CARDS_LETTERS = "23456789XJQKAJ",
        const pltr::core::StringTemplateParameter _COLORS_LETTERS = "CDHS",
        const pltr::core::StringTemplateParameter _JOKERS_COLORS = "RB",
        const std::uint32_t _START_VALUE = 2
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
        static inline constexpr ValueT _START_VALUE{ _START_VALUE };


        //-----   constants   -----//
        static inline constexpr IdentT CARDS_PER_COLOR{ 13 };
        static inline constexpr IdentT COLORS_COUNT{ 4 };

        static inline constexpr IdentT JOKERS_FIRST_IDENT{ COLORS_COUNT * CARDS_PER_COLOR };
        static inline constexpr IdentT JOKERS_INDEX{ CARDS_PER_COLOR };


        //-----   Constructors / Desctructor   -----//
        inline StandardCard()                                           //!< default empty constructor.
            : MyBaseClass(0, _START_VALUE)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_
        ) noexcept                                                      //!< 1-valued constructor.
            : MyBaseClass(ident_, ValueT(ident_ / 4 + _START_VALUE))
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_
        ) noexcept                                                      //!< 2-valued constructor (1/2).
            : MyBaseClass(ident_, value_)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const std::filesystem::path& image_path_
        ) noexcept                                                      //!< 2-valued constructor (2/2).
            : MyBaseClass(ident_, ValueT(ident_ / 4 + _START_VALUE), image_path_)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_
        ) noexcept                                                      //!< 3-valued constructor (1/2).
            : MyBaseClass(ident_, value_, ordering_value_)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_
        ) noexcept                                                      //!< 3-valued constructor (2/2).
            : MyBaseClass(ident_, value_, image_path_)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_,
            const std::filesystem::path& image_path_
        ) noexcept                                                      //!< 4-valued constructor.
            : MyBaseClass(ident_, value_, ordering_value_, image_path_)
        {
            _set_text();
        }

        inline StandardCard(const StandardCard&) noexcept = default;    //!< default copy constructor.
        inline StandardCard(StandardCard&&) noexcept = default;         //!< default move constructor.

        inline virtual ~StandardCard() noexcept = default;              //!< default destructor.


        //-----   Operators   -----//
        StandardCard& operator=(const StandardCard&) noexcept = default;      //!< default copy operator.
        StandardCard& operator=(StandardCard&&) noexcept = default;           //!< default move operator.


        //-----   Accessors / Mutators   -----//
        [[nodiscard]]
        inline const EColor get_color() const noexcept                      //!< returns the enum color of this card
        {
            //return EColor(this->ident % IdentT(EColor::COLORS_COUNT));
            return is_joker() ? EColor(this->ident - JOKERS_FIRST_IDENT + 4) : EColor(this->ident % COLORS_COUNT);
        }


        [[nodiscard]]
        inline const bool is_joker() const noexcept                         //!< returns true if this card is a Joker one
        {
            return this->ident >= JOKERS_FIRST_IDENT;
        }


        inline void set(const IdentT ident_) noexcept                       //!< sets data (1 arg).
        {
            set(ident_, ident_ / 4 + _START_VALUE);
        }


        inline void set(const IdentT ident_, const ValueT value_) noexcept  //!< sets data (2 args).
        {
            MyBaseClass::set(ident_, value_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_
        ) noexcept                                                          //!< sets data (3 args, 1/2).
        {
            MyBaseClass::set(ident_, value_, ordering_value_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_) noexcept              //!< sets data (3 args, 2/2).
        {
            MyBaseClass::set(ident_, value_, image_path_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const ValueT ordering_value_,
            const std::filesystem::path& image_path_) noexcept              //!< sets data (4 args).
        {
            MyBaseClass::set(ident_, value_, ordering_value_, image_path_);
            _set_text();
        }


        //-----   Comparison Operations   -----//
        static struct CmpColors {
            bool operator() (const MyClassType& left, const MyClassType& right) {
                return left.get_color() < right.get_color();
            }
        } cmp_colors;                                                       //!< comparison on sole colors of cards


        static struct {
            bool operator() (const MyClassType& left, const MyClassType& right) {
                return left.get_color() < right.get_color() ||
                    (left.get_color() == right.get_color() && left.value < right.value);
            }
        } CmpColorsValues;                                                  //!< comparison on colors of cards first then on cards value in same color


        static struct {
            bool operator() (const MyClassType& left, const MyClassType& right) {
                return left.ident < right.ident;
            }
        } CmpIdents;                                                        //!< comparison on sole ident of cards 


        static struct {
            bool operator() (const MyClassType& left, const MyClassType& right) {
                return left < right;
            }
        } CmpValue;                                                         //!< comparison on sole value of cards 



    protected:
        void _set_text() noexcept  //!< internally sets the text of this card
        {
            if (!is_joker())
                this->text = std::format(
                    "{:c}{:c}",
                    _CARDS_LETTERS[this->ident / COLORS_COUNT],
                    _COLORS_LETTERS[this->ident % COLORS_COUNT]
                );
            else
                this->text = std::format(
                    "{:c}{:c}",
                    _CARDS_LETTERS[JOKERS_INDEX],
                    (this->ident == JOKERS_FIRST_IDENT) ? _JOKERS_COLORS[0] : _JOKERS_COLORS[1]
                );
        }

    };


    //=======================================================================
    /* \brief The class for standard cards - German localization.
    */
    using StandardCardDe = StandardCard<"23456789XBDK1J", "RAHP", "RS">;  // notice: RAHP für kReuz, kAro, Herz, Pik


    //=======================================================================
    /* \brief The class for standard cards - English localization.
    */
    using StandardClassEn = StandardCard<>;  // that's all!


    //=======================================================================
    /* \brief The class for standard cards - Spanish localization.
    */
    using StandardCardEs = StandardCard<"23456789XJAR1J", "TDCE", "RN">;  // notice: JARJ para Jota, reinA, Rey, Joker ; TDCE para Tréboles, Diamantes; Corazón, Espadas


    //=======================================================================
    /* \brief The class for standard cards - French localization.
    */
    using StandardCardFr = StandardCard<"23456789XVDR1J", "TKCP", "RN">;  // notice: TKCP pour Trèfle, (K)arreau, Coeur, Pique


    //=======================================================================
    /* \brief The class for standard cards - Italian localization.
    */
    using StandardCardIt = StandardCard<"23456789XJAR1J", "MQCP", "RN">;  // notice: JARJ per Jack, reginA, Re, Joker ; MQCP per Mazze, Quadri; Cuore, Picche


    //=======================================================================
    /* \brief The class for Windows console standard cards.
    */
    using StandardWindowsConsoleCard = StandardCard<"23456789XJQKAJ", "\005\004\003\006", "RB">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - German localization.
    */
    using StandardWindowsConsoleCardDe = StandardCard<"23456789XBDK1J", "\005\004\003\006", "RS">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - English localization.
    */
    using StandardWindowsConsoleClassEn = StandardWindowsConsoleCard;  // that's all!


    //=======================================================================
    /* \brief The class for Windows console standard cards - Spanish localization.
    */
    using StandardWindowsConsoleCardEs = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - French localization.
    */
    using StandardWindowsConsoleCardFr = StandardCard<"23456789XVDR1J", "\005\004\003\006", "RN">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - Italian localization.
    */
    using StandardWindowsConsoleCardIt = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN">;


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

    template<>
    struct is_standard_card<StandardCardDe> {
        static inline constexpr bool value{ true };
    };

    template<>
    struct is_standard_card<StandardCardEs> {
        static inline constexpr bool value{ true };
    };

    template<>
    struct is_standard_card<StandardCardFr> {
        static inline constexpr bool value{ true };
    };

    template<>
    struct is_standard_card<StandardCardIt> {
        static inline constexpr bool value{ true };
    };

    template<>
    struct is_standard_card<StandardWindowsConsoleCard> {
        static inline constexpr bool value{ true };
    };

    template<>
    struct is_standard_card<StandardWindowsConsoleCardDe> {
        static inline constexpr bool value{ true };
    };

    template<>
    struct is_standard_card<StandardWindowsConsoleCardEs> {
        static inline constexpr bool value{ true };
    };

    template<>
    struct is_standard_card<StandardWindowsConsoleCardFr> {
        static inline constexpr bool value{ true };
    };

    /* Notice: 'It' template version is exactly the same as 'Es' one. No need to set this specialization twice!
    template<>
    struct is_standard_card<StandardWindowsConsoleCardIt> {
        static inline constexpr bool value{ true };
    };
    */

}