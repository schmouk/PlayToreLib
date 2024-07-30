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
#include <type_traits>

#include "playing_cards/standard_cards.h"
#include "playing_cards/cards_deck.h"


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* \brief The class of 54 standard cards decks.
    */
    template<typename CardT>
        requires pltr::cards::is_standard_card_v<CardT>
    class CardsDeck54 : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;


        //-----   Constructors / Desctructor   -----//
        inline CardsDeck54()                                //!< empty constructor
            : MyBaseClass(_CARDS_COUNT)
        {
            refill_deck();
        }

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
    template<typename CardT>
        requires pltr::cards::is_standard_card_v<CardT>
    class CardsDeck52 : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;


        //-----   Constructors / Desctructor   -----//
        inline CardsDeck52()                                //!< empty constructor
            : MyBaseClass(_CARDS_COUNT)
        {
            refill_deck();
        }

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
    template<typename CardT>
        requires pltr::cards::is_standard_card_v<CardT>
    class CardsDeck32 : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;


        //-----   Constructors / Desctructor   -----//
        inline CardsDeck32()                                //!< empty constructor
            : MyBaseClass(_CARDS_COUNT)
        {
            refill_deck();
        }

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
        requires pltr::cards::is_standard_card_v<CardT>
    void CardsDeck54<CardT>::refill_deck()
    {
        MyBaseClass::clear();
        for (typename MyBaseClass::IndexType ident = 0; ident < _CARDS_COUNT; ++ident)
            MyBaseClass::append_card(CardT(ident, CardT::value_type((ident / 4) + 1)));
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
        requires pltr::cards::is_standard_card_v<CardT>
    void CardsDeck52<CardT>::refill_deck()
    {
        MyBaseClass::clear();
        for (typename MyBaseClass::IndexType ident = 0; ident < _CARDS_COUNT; ++ident)
            MyBaseClass::append_card(CardT(ident, CardT::value_type((ident / 4) + 1)));
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
        requires pltr::cards::is_standard_card_v<CardT>
    void CardsDeck32<CardT>::refill_deck()
    {
        MyBaseClass::clear();

        // aces first
        for (typename MyBaseClass::IndexType ident = 0; ident < 4; ++ident)
            MyBaseClass::append_card(CardT(ident, CardT::value_type(1)));

        // then 7s to kings
        constexpr MyBaseClass::IndexType GAP{ 5 * 4 };  // skips 2s to 6s (included)
        for (typename MyBaseClass::IndexType i = 4; i < _CARDS_COUNT; ++i) {
            const MyBaseClass::IndexType ident{ i + GAP };
            MyBaseClass::append_card(CardT(ident, CardT::value_type((ident / 4) + 1)));
        }
    }

}