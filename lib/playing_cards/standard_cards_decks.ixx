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
#include <type_traits>


export module pltr:standard_cards_decks;

import :cards_deck;
import :standard_cards;


//===========================================================================
export namespace pltr::cards
{
    //=======================================================================
    /* \brief The class of 54 standard cards decks.
    */
    export template<typename CardT>
        requires std::is_base_of_v<pltr::cards::StandardCard, CardT>
    class CardsDeck54 : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;


        //-----   Constructors / Desctructor   -----//
        inline CardsDeck54()                                //!< empty constructor
            : MyBaseClass(_CARDS_COUNT)
        {}

        CardsDeck54(const CardsDeck54&) noexcept = default; //!< default copy constructor.
        CardsDeck54(CardsDeck54&&) noexcept = default;      //!< default move constructor.

        virtual ~CardsDeck54() noexcept = default;          //!< default destructor.


        //-----   Operators   -----//
        CardsDeck54& operator=(const CardsDeck54&) noexcept = default;  //!< default copy operator.
        CardsDeck54& operator=(CardsDeck54&&) noexcept = default;       //!< default move operator.


        //-----   Operations   -----//
        inline virtual void refill_deck();  //!< fills this deck with all related playing cards. Does nothing in this base class, must be overridden in inheriting classes.


    private:
        static inline constexpr std::uint32_t _CARDS_COUNT{ 54 };
    };



    //=======================================================================
    /* \brief The class of 52 standard cards decks.
    */
    export template<typename CardT>
        requires std::is_base_of_v<pltr::cards::StandardCard, CardT>
    class CardsDeck52 : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;


        //-----   Constructors / Desctructor   -----//
        inline CardsDeck52()                                //!< empty constructor
            : MyBaseClass(_CARDS_COUNT)
        {}

        CardsDeck52(const CardsDeck52&) noexcept = default; //!< default copy constructor.
        CardsDeck52(CardsDeck52&&) noexcept = default;      //!< default move constructor.

        virtual ~CardsDeck52() noexcept = default;          //!< default destructor.


        //-----   Operators   -----//
        CardsDeck52& operator=(const CardsDeck52&) noexcept = default;  //!< default copy operator.
        CardsDeck52& operator=(CardsDeck52&&) noexcept = default;       //!< default move operator.


        //-----   Operations   -----//
        inline virtual void refill_deck();  //!< fills this deck with all related playing cards. Does nothing in this base class, must be overridden in inheriting classes.


    private:
        static inline constexpr std::uint32_t _CARDS_COUNT{ 52 };
    };



    //=======================================================================
    /* \brief The class of 32 standard cards decks.
    */
    export template<typename CardT>
        requires std::is_base_of_v<pltr::cards::StandardCard, CardT>
    class CardsDeck32 : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;


        //-----   Constructors / Desctructor   -----//
        inline CardsDeck32()                                //!< empty constructor
            : MyBaseClass(_CARDS_COUNT)
        {}

        CardsDeck32(const CardsDeck32&) noexcept = default; //!< default copy constructor.
        CardsDeck32(CardsDeck32&&) noexcept = default;      //!< default move constructor.

        virtual ~CardsDeck32() noexcept = default;          //!< default destructor.


        //-----   Operators   -----//
        CardsDeck32& operator=(const CardsDeck32&) noexcept = default;  //!< default copy operator.
        CardsDeck32& operator=(CardsDeck32&&) noexcept = default;       //!< default move operator.


        //-----   Operations   -----//
        inline virtual void refill_deck();  //!< fills this deck with all related playing cards. Does nothing in this base class, must be overridden in inheriting classes.


    private:
        static inline constexpr std::uint32_t _CARDS_COUNT{ 32 };
    };



    //=======================================================================
    // local implementations

    //-----------------------------------------------------------------------
    template<typename CardT>
        requires std::is_base_of_v<pltr::cards::StandardCard, CardT>
    void CardsDeck54<CardT>::refill_deck()
    {
        for (typename CardT::index_type ident = 0; ident < _CARDS_COUNT; ++ident)
            append_card(ident, CardT::value_type((ident / 4) + 1));
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
        requires std::is_base_of_v<pltr::cards::StandardCard, CardT>
    void CardsDeck52<CardT>::refill_deck()
    {
        for (typename CardT::index_type ident = 0; ident < _CARDS_COUNT; ++ident)
            append_card(ident, CardT::value_type((ident / 4) + 1));
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
        requires std::is_base_of_v<pltr::cards::StandardCard, CardT>
    void CardsDeck32<CardT>::refill_deck()
    {
        // aces first
        for (typename CardT::index_type ident = 0; ident < 4; ++ident)
            append_card(ident, CardT::value_type(1));

        // then 7s to kings
        constexpr CardT::index_type gap{ 5 * 4 };  // skips 2s to 6s (included)
        for (typename CardT::index_type i = 4; i < _CARDS_COUNT; ++i) {
            const CardT::index_type ident{ i + gap };
            append_card(ident, CardT::value_type((ident / 4) + 1));
        }

    }

}