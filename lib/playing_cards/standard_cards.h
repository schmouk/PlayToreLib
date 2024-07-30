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


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* \brief The strings structure for template parameters
    */
    template<const int STR_LENGTH>
    struct StringTemplateParameter
    {
        char text[STR_LENGTH] {};

        consteval StringTemplateParameter(const char(&txt_)[STR_LENGTH]){
            std::copy_n(txt_, STR_LENGTH, text);
        }

        const char operator[] (const int index) const {
            return text[index];
        }

    };
    
    
    //=======================================================================
    /* \brief The base class for standard cards.
    */
    template<
        const StringTemplateParameter _CARDS_LETTERS = "A23456789XJQKJ",
        const StringTemplateParameter _COLORS_LETTERS = "CDHS",
        const StringTemplateParameter _JOKERS_COLORS = "RB"
    >
    class StandardCard : public pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>
    {
    public:

        //-----   Types wrappers   -----//
        using MyBaseClass = pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>;
        using IdentT = MyBaseClass::ident_type;
        using ValueT = MyBaseClass::value_type;


        //-----   Types declarations   -----//
        enum class EColor : IdentT //!< the standard colors for standard playing cards
        {
            E_CLUB, E_DIAMOND, E_HEART, E_SPADE,
        };


        //-----   constants   -----//
        static inline constexpr IdentT CARDS_PER_COLOR{ 13 };
        static inline constexpr IdentT COLORS_COUNT{ 4 };

        static inline constexpr IdentT JOKERS_FIRST_IDENT{ COLORS_COUNT * CARDS_PER_COLOR };
        static inline constexpr IdentT JOKERS_INDEX{ CARDS_PER_COLOR };


        //-----   Constructors / Desctructor   -----//
        inline StandardCard()                                           //!< default empty constructor.
            : MyBaseClass(0, 1)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_
        ) noexcept                                                      //!< 1-valued constructor.
            : MyBaseClass(ident_, ValueT(ident_ / 4 + 1))
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
            : MyBaseClass(ident_, ValueT(ident_ / 4 + 1), image_path_)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_
        ) noexcept                                                      //!< 3-valued constructor.
            : MyBaseClass(ident_, value_, image_path_)
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
            return EColor(this->ident % COLORS_COUNT);
        }


        [[nodiscard]]
        inline const bool is_joker() const noexcept                         //!< returns true if this card is a Joker one
        {
            return this->ident >= JOKERS_FIRST_IDENT;
        }


        inline void set(const IdentT ident_) noexcept                       //!< sets data (1 arg).
        {
            set(ident_, ident_ / 4 + 1);
        }


        inline void set(const IdentT ident_, const ValueT value_) noexcept  //!< sets data (2 args).
        {
            MyBaseClass::set(ident_, value_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_) noexcept              //!< sets data (3 args).
        {
            MyBaseClass::set(ident_, value_, image_path_);
            _set_text();
        }


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
    using StandardCardDe = StandardCard<"123456789XBDKJ", "RAHP", "RS">;  // notice: RAHP für kReuz, kAro, Herz, Pik


    //=======================================================================
    /* \brief The class for standard cards - English localization.
    */
    using StandardClassEn = StandardCard<>;  // that's all!


    //=======================================================================
    /* \brief The class for standard cards - Spanish localization.
    */
    using StandardCardEs = StandardCard<"123456789XJAYJ", "ECDT", "RN">;  // notice: ECDT para Jota, reinA, reY, Joker


    //=======================================================================
    /* \brief The class for standard cards - French localization.
    */
    using StandardCardFr = StandardCard<"123456789XVDRJ", "TKCP", "RN">;  // notice: TKCP pour Trèfle, (K)arreau, Coeur, Pique


    //=======================================================================
    /* \brief The class for standard cards - Italian localization.
    */
    using StandardCardIt = StandardCard<"123456789XJARJ", "PCQF", "RN">;  // notice: "PCQF"per Jack, reginA, Re, Joker


    //=======================================================================
    /* \brief The class for Windows console standard cards.
    */
    using StandardWindowsConsoleCard = StandardCard<"A23456789XJQKJ", "\005\004\003\006", "RB">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - German localization.
    */
    using StandardWindowsConsoleCardDe = StandardCard<"123456789XBDKJ", "\005\004\003\006", "RS">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - English localization.
    */
    using StandardWindowsConsoleClassEn = StandardWindowsConsoleCard;  // that's all!


    //=======================================================================
    /* \brief The class for Windows console standard cards - Spanish localization.
    */
    using StandardWindowsConsoleCardEs = StandardCard<"123456789XJAYJ", "\005\004\003\006", "RN">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - French localization.
    */
    using StandardWindowsConsoleCardFr = StandardCard<"123456789XVDRJ", "\005\004\003\006", "RN">;


    //=======================================================================
    /* \brief The class for Windows console standard cards - Italian localization.
    */
    using StandardWindowsConsoleCardIt = StandardCard<"123456789XJARJ", "\005\004\003\006", "RN">;

}