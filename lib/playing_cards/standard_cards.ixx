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


export module pltr:standard_cards;

import :playing_cards;


//===========================================================================
export namespace pltr::cards
{
    //=======================================================================
    /* \brief The base class for standard cards.
    */
    export class StandardCard : public pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>
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
        inline StandardCard()                                                   //!< default empty constructor.
            : MyBaseClass()
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_
        ) noexcept                                                              //!< 2-valued constructor.
            : MyBaseClass(ident_, value_)
        {
            _set_text();
        }


        inline StandardCard(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_
        ) noexcept                                                              //!< 3-valued constructor.
            : MyBaseClass(ident_, value_, image_path_)
        {
            _set_text();
        }

        inline StandardCard(const StandardCard&) noexcept = default;            //!< default copy constructor.
        inline StandardCard(StandardCard&&) noexcept = default;                 //!< default move constructor.

        inline virtual ~StandardCard() noexcept = default;                      //!< default destructor.


        //-----   Operators   -----//
        inline StandardCard& operator=(const StandardCard&) noexcept = default; //!< default copy assignment.
        inline StandardCard& operator=(StandardCard&&) noexcept = default;      //!< default move assignment.


        [[nodiscard]]
        inline const bool operator< (const StandardCard& other) const noexcept  //!< less-than operator.
        {
            return this->value < other.value;
        }


        [[nodiscard]]
        inline const bool operator== (const StandardCard& other) const noexcept  //!< equality operator.
        {
            return this->value == other.value;
        }


        //-----   Accessors / Mutators   -----//
        [[nodiscard]]
        inline const EColor get_color() const noexcept                          //!< returns the enum color of this card
        {
            //return EColor(this->ident % IdentT(EColor::COLORS_COUNT));
            return EColor(this->ident % COLORS_COUNT);
        }


        [[nodiscard]]
        inline const bool is_joker() const noexcept                             //!< returns true if this card is a Joker one
        {
            return this->ident >= JOKERS_FIRST_IDENT;
        }

        inline void set(const IdentT ident_, const ValueT value_) noexcept      //!< sets data.
        {
            MyBaseClass::set(ident_, value_);
            _set_text();
        }


        inline void set(
            const IdentT ident_,
            const ValueT value_,
            const std::filesystem::path& image_path_) noexcept                  //!< sets data.
        {
            MyBaseClass::set(ident_, value_, image_path_);
            _set_text();
        }


    protected:
        static inline const std::string _CARDS_LETTERS{ "A23456789JQKJ" };
        static inline const std::string _COLORS_LETTERS{ "CDHS" };
        static inline const std::string _JOKERS_COLORS{ "RB" };


    private:
        void _set_text() noexcept;                                              //!< internally sets the text of this card
    
    };



    //=======================================================================
    /* \brief The class for standard cards - German localization.
    */
    export class StandardCardDe : public StandardCard
    {
    protected:
        static inline const std::string _CARDS_LETTERS{ "123456789BDKJ" };
        static inline const std::string _COLORS_LETTERS{ "PHAR" };  // für Pik, Herz, kAro, kReuz
        static inline const std::string _JOKERS_COLORS{ "RS" };

    };



    //=======================================================================
    /* \brief The class for standard cards - English localization.
    */
    export using StandardClassEn = StandardCard;  // that's all!



    //=======================================================================
    /* \brief The class for standard cards - Spanish localization.
    */
    export class StandardCardEs : public StandardCard
    {
    protected:
        static inline const std::string _CARDS_LETTERS{ "123456789JARJ" };  // para Jota, reinA, Rey, Joker
        static inline const std::string _COLORS_LETTERS{ "ECDT" };
        static inline const std::string _JOKERS_COLORS{ "RN" };

    };



    //=======================================================================
    /* \brief The class for standard cards - French localization.
    */
    export class StandardCardFr : public StandardCard
    {
    protected:
        static inline const std::string _CARDS_LETTERS{ "123456789VDRJ" };
        static inline const std::string _COLORS_LETTERS{ "TKCP" };
        static inline const std::string _JOKERS_COLORS{ "RN" };

    };



    //=======================================================================
    /* \brief The class for standard cards - Italian localization.
    */
    export class StandardCardIt : public StandardCard
    {
    protected:
        static inline const std::string _CARDS_LETTERS{ "123456789JARJ" };  // per Jack, Regina, Re, Joker
        static inline const std::string _COLORS_LETTERS{ "PCQF" };
        static inline const std::string _JOKERS_COLORS{ "RN" };

    };

}