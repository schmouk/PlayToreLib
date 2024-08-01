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

#include "playing_cards/standard_cards_decks.h"


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* \brief The generic class of decks that contains unique standard cards.
    */
    template<typename StandardCardsDeckT>
    class UniqueStandardCardsDeck : public StandardCardsDeckT
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = StandardCardsDeckT;
        using CardT = StandardCardsDeckT::CardT;
        using CardsList = StandardCardsDeckT::CardsList;
        using IndexType = StandardCardsDeckT::IndexType;


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
        virtual const bool append_card(const CardT& card) override;                             //!< appends a card at bottom of this deck if not already present in it.

        virtual void append_cards(const CardsList& cards) override;                             //!< appends n cards at bottom of this deck except for cards already present in deck.

        virtual const bool contains(const CardT& card) const override;                          //!< returns true if the card ident is found in this deck.

        virtual void insert_card(const CardT& card) override;                                   //!< inserts a card at top of this deck except for cards already present in deck.

        virtual void insert_cards(const CardsList& cards) override;                             //!< inserts n cards at top of this deck except for cards already present in deck.

        virtual const bool insert_nth_card(const IndexType index, const CardT& card) override;  //!< inserts a card at n-th position in this deck if not already present in deck

        virtual void insert_nth_cards(const IndexType index, const CardsList& cards) override;  //!< inserts n cards at n-th position in this deck. Deck max capacity may grow up then.

        virtual const bool insert_rand_card(const CardT& card) override;                        //!< inserts a card at a random position in this deck. Deck max capacity may grow up then.

    };


    //=======================================================================
    /* \brief The class of decks that contains 54 unique standard cards.
    */
    template<typename CardT>
    using UniqueStandardCardsDeck54 = UniqueStandardCardsDeck<CardsDeck54<CardT>>;


    //=======================================================================
    /* \brief The class of decks that contains 52 unique standard cards.
    */
    template<typename CardT>
    using UniqueStandardCardsDeck52 = UniqueStandardCardsDeck<CardsDeck52<CardT>>;


    //=======================================================================
    /* \brief The class of decks that contains 32 unique standard cards.
    */
    template<typename CardT>
    using UniqueStandardCardsDeck32 = UniqueStandardCardsDeck<CardsDeck32<CardT>>;


    //=======================================================================
    /* Local implementations
    */

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    const bool UniqueStandardCardsDeck<StandardCardsDeckT>::append_card(const CardT& card)
    {
        // reminder: appends a card at bottom of this deck if not already present in it.
        if (!contains(card))
            return MyBaseClass:append_card(card);
        else
            return false;
    }

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    void UniqueStandardCardsDeck<StandardCardsDeckT>::append_cards(const CardsList& cards)
    {
        // reminder: appends n cards at bottom of this deck except for cards already present in deck.
        for (auto& card : cards)
            append_card(card);
    }

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    const bool UniqueStandardCardsDeck<StandardCardsDeckT>::contains(const CardT& card) const
    {
        // reminder: returns true if the card ident is found in this deck.
        return !is_full() && !MyBaseClass::contains(card);
    }

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    void UniqueStandardCardsDeck<StandardCardsDeckT>::insert_card(const CardT& card) 
    {
        // reminder: inserts a card at top of this deck except for cards already present in deck.
        if (!contains(card))
            return MyBaseClass:insert_card(card);
        else
            return false;
    }

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    void UniqueStandardCardsDeck<StandardCardsDeckT>::insert_cards(const CardsList& cards)
    {
        // reminder: inserts n cards at top of this deck except for cards already present in deck.
        for (auto& card : cards)
            insert_card(card);
    }

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    const bool UniqueStandardCardsDeck<StandardCardsDeckT>::insert_nth_card(const IndexType index, const CardT& card)
    {
        // reminder: inserts a card at n-th position in this deck if not already present in deck
        if (!contains(card))
            return MyBaseClass:insert_nth_card(index, card);
        else
            return false;
    }

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    void UniqueStandardCardsDeck<StandardCardsDeckT>::insert_nth_cards(const IndexType index, const CardsList& cards)
    {
        // reminder: inserts n cards at n-th position in this deck. Deck max capacity may grow up then.
        CardsList unique_cards{};

        for (auto& card : cards) {
            auto doubloon_it{
                std::find_if(unique_cards.begin(), unique_cards.end(), [unique_cards, card](CardT& c) { return c.ident == card.ident; })
            };

            if (doubloon_it == unique_cards.end() && !contains(card))
                unique_cards.push_back(card);
        }

        MyBaseClass::insert_nth_cards(index, unique_cards);
    }

    //-----------------------------------------------------------------------
    template<typename StandardCardsDeckT>
    const bool UniqueStandardCardsDeck<StandardCardsDeckT>::insert_rand_card(const CardT& card)
    {
        // reminder: inserts a card at a random position in this deck. Deck max capacity may grow up then.
        if (!contains(card))
            return MyBaseClass::insert_rand_card(card);
        else
            return false;
    }

}