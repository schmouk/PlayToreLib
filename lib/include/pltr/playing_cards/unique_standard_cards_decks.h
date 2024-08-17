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

#include "pltr/playing_cards/standard_cards.h"
#include "pltr/playing_cards/standard_cards_decks.h"


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* \brief The generic class of decks that contains unique standard cards.
    */
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    class UniqueStandardCardsDeck : public StandardDeckT
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = StandardDeckT;
        using CardType = typename StandardDeckT::CardType;
        using CardsList = pltr::cards::CardsList<CardType>;
        using IndexType = MyBaseClass::IndexType;


        //-----   Constructors / Desctructor   -----//
        inline UniqueStandardCardsDeck()                                                        //!< empty constructor
            : MyBaseClass()
        {}

        UniqueStandardCardsDeck(const UniqueStandardCardsDeck&) noexcept = default;             //!< default copy constructor.
        UniqueStandardCardsDeck(UniqueStandardCardsDeck&&) noexcept = default;                  //!< default move constructor.

        virtual ~UniqueStandardCardsDeck() noexcept = default;                                  //!< default destructor.


        //-----   Operators   -----//
        UniqueStandardCardsDeck& operator=(const UniqueStandardCardsDeck&) noexcept = default;  //!< default copy operator.
        UniqueStandardCardsDeck& operator=(UniqueStandardCardsDeck&&) noexcept = default;       //!< default move operator.


        //-----   Operations   -----//
        virtual const bool append_card(const CardType& card) override;                          //!< appends a card at bottom of this deck if not already present in it.

        virtual void append_cards(const CardsList& cards) override;                             //!< appends n cards at bottom of this deck except for cards already present in deck.

        virtual const bool insert_card(const CardType& card) override;                          //!< inserts a card at top of this deck except for cards already present in deck.

        virtual void insert_cards(const CardsList& cards) override;                             //!< inserts n cards at top of this deck except for cards already present in deck.

        virtual const bool insert_nth_card(const IndexType index, const CardType& card) override;   //!< inserts a card at n-th position in this deck if not already present in deck

        virtual void insert_nth_cards(const IndexType index, const CardsList& cards) override;  //!< inserts n cards at n-th position in this deck. Deck max capacity may grow up then.

        virtual const bool insert_rand_card(const CardType& card) override;                     //!< inserts a card at a random position in this deck. Deck max capacity may grow up then.


    private:
        inline const bool _may_insert(const CardType& card) const
        {
            return !MyBaseClass::is_full() && !MyBaseClass::contains(card);
        }

    };


    //=======================================================================
    /* \brief The class of decks that contains 54 unique standard cards.
    */
    template<
        typename CardType,
        const std::uint32_t START_VALUE = 2,
        const std::uint32_t START_ORDERING_VALUE = 0
    > requires pltr::cards::is_standard_card_v<CardType>
    using UniqueStandardCardsDeck54 = UniqueStandardCardsDeck<CardsDeck54<CardType, START_VALUE, START_ORDERING_VALUE, 1>>;


    //=======================================================================
    /* \brief The class of decks that contains 52 unique standard cards.
    */
    template<
        typename CardType,
        const std::uint32_t START_VALUE = 2,
        const std::uint32_t START_ORDERING_VALUE = 0
    > requires pltr::cards::is_standard_card_v<CardType>
    using UniqueStandardCardsDeck52 = UniqueStandardCardsDeck<CardsDeck52<CardType, START_VALUE, START_ORDERING_VALUE, 1>>;


    //=======================================================================
    /* \brief The class of decks that contains 32 unique standard cards.
    */
    template<
        typename CardType,
        const std::uint32_t START_VALUE = 7,
        const std::uint32_t START_ORDERING_VALUE = 0
    > requires pltr::cards::is_standard_card_v<CardType>
    using UniqueStandardCardsDeck32 = UniqueStandardCardsDeck<CardsDeck32<CardType, START_VALUE, START_ORDERING_VALUE, 1>>;



    //=======================================================================
    // Local implementations

    //-----------------------------------------------------------------------
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    const bool UniqueStandardCardsDeck<StandardDeckT>::append_card(const CardType& card)
    {
        // reminder: appends a card at bottom of this deck if not already present in it.
        if (_may_insert(card))
            return MyBaseClass::append_card(card);
        else
            return false;
    }

    //-----------------------------------------------------------------------
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    void UniqueStandardCardsDeck<StandardDeckT>::append_cards(const CardsList& cards)
    {
        // reminder: appends n cards at bottom of this deck except for cards already present in deck.
        for (auto& card : cards)
            append_card(card);
    }

    //-----------------------------------------------------------------------
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    const bool UniqueStandardCardsDeck<StandardDeckT>::insert_card(const CardType& card)
    {
        // reminder: inserts a card at top of this deck except for cards already present in deck.
        if (_may_insert(card))
            return MyBaseClass::insert_card(card);
        else
            return false;
    }

    //-----------------------------------------------------------------------
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    void UniqueStandardCardsDeck<StandardDeckT>::insert_cards(const CardsList& cards)
    {
        // reminder: inserts n cards at top of this deck except for cards already present in deck.
        for (auto& card : cards)
            insert_card(card);
    }

    //-----------------------------------------------------------------------
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    const bool UniqueStandardCardsDeck<StandardDeckT>::insert_nth_card(const IndexType index, const CardType& card)
    {
        // reminder: inserts a card at n-th position in this deck if not already present in deck.
        if (_may_insert(card))
            return MyBaseClass::insert_nth_card(index, card);
        else
            return false;
    }

    //-----------------------------------------------------------------------
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    void UniqueStandardCardsDeck<StandardDeckT>::insert_nth_cards(const IndexType index, const CardsList& cards)
    {
        // reminder: inserts n cards at n-th position in this deck.
        CardsList unique_cards{};

        for (auto& card : cards) {
            auto doubloon_it{
                std::ranges::find_if(unique_cards, [card](CardType& c) { return c.ident == card.ident; })
            };

            if (doubloon_it == unique_cards.end() && _may_insert(card))
                unique_cards.push_back(card);
        }

        MyBaseClass::insert_nth_cards(index, unique_cards);
    }

    //-----------------------------------------------------------------------
    template<typename StandardDeckT>
        requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
    const bool UniqueStandardCardsDeck<StandardDeckT>::insert_rand_card(const CardType& card)
    {
        // reminder: inserts a card at a random position in this deck.
        if (_may_insert(card))
            return MyBaseClass::insert_rand_card(card);
        else
            return false;
    }


    //=======================================================================
    // Type traits concepts
    //
    template<typename UniqueStandardDeckT>
    struct is_unique_standard_cards_deck {
        static inline const bool value{ pltr::cards::is_standard_cards_deck_v<typename UniqueStandardDeckT::MyBaseClass> };
    };

    template<typename UniqueStandardDeckT>
    constexpr bool is_unique_standard_cards_deck_v = is_standard_cards_deck<UniqueStandardDeckT>::value;

}