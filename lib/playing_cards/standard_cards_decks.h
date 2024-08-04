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
#include <ranges>
#include <type_traits>

#include "playing_cards/standard_cards.h"
#include "playing_cards/cards_deck.h"


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* \brief The class of 54 standard cards decks.
    */
    template<typename CardT, const std::uint32_t _CARDS_COUNT, const std::uint32_t _START_VALUE = 0>
        requires pltr::cards::is_standard_card_v<CardT>
    class StandardCardsDeck : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;
        using CardType = CardT;


        //-----   Constructors / Desctructor   -----//
        inline StandardCardsDeck()                                                  //!< empty constructor
            : MyBaseClass(_CARDS_COUNT)
        {
            _set_reference_deck();
            refill_deck();
        }

        StandardCardsDeck(const StandardCardsDeck&) noexcept = default;             //!< default copy constructor.
        StandardCardsDeck(StandardCardsDeck&&) noexcept = default;                  //!< default move constructor.

        virtual ~StandardCardsDeck() noexcept = default;                            //!< default destructor.


        //-----   Operators   -----//
        StandardCardsDeck& operator=(const StandardCardsDeck&) noexcept = default;  //!< default copy operator.
        StandardCardsDeck& operator=(StandardCardsDeck&&) noexcept = default;       //!< default move operator.


        //-----   Operations   -----//
        virtual inline const bool allowed_card(const CardT& card) const noexcept override  //!< returns true if this card is allowed to be contained in this deck.
        {
            return card.ident < _CARDS_COUNT;
        }

        inline virtual void refill_deck() override      //!< fills this deck with all related playing cards. Does nothing in this base class, must be overridden in inheriting classes.
        {
            //MyBaseClass::clear();
            //std::ranges::copy(_reference_deck.deck(), MyBaseClass::deck());
            MyBaseClass::deck() = _reference_deck.deck();
        }

        inline void sort()                              //!< sorts this deck according to descending order of values then in the descending order of colors
        {
            auto cmp = [](const CardT& left, const CardT& right) {
                return left.value < right.value ||
                    (left.value == right.value && left.get_color() < right.get_color());
            };
            std::ranges::stable_sort(MyBaseClass::deck(), cmp);
        }

        inline void sort_colors()                       //!< sorts this deck according to the descending order of colors then in the descending order of ordering values
        {
            auto cmp_colors = [](const CardT& left, const CardT& right) {
                return left.get_color() < right.get_color() ||
                    (left.get_color() == right.get_color() && left.ordering_value < right.ordering_value);
            };
            std::ranges::stable_sort(MyBaseClass::deck(), cmp_colors);
        }

        inline void sort_colors_values()                //!< sorts this deck according to the descending order of colors first then on cards descending values in same color
        {
            auto cmp_colors_values = [](const CardT& left, const CardT& right) {
                return left.get_color() < right.get_color() ||
                    (left.get_color() == right.get_color() && left.value < right.value);
            };
            std::ranges::stable_sort(MyBaseClass::deck(), cmp_colors_values);
        }

        inline void sort_idents()                       //!< sorts this deck according to the descending order of colors first then on cards descending idents in same color
        {
            auto cmp_idents = [](const CardT& left, const CardT& right) {
                return left.ident < right.ident;
            };
            std::ranges::stable_sort(MyBaseClass::deck(), cmp_idents);
        }


    private:
        static inline MyBaseClass _reference_deck{ MyBaseClass(_CARDS_COUNT) };
        static inline bool _reference_already_set{ false };
        
        static void _set_reference_deck();

    };



    //=======================================================================
    // local implementations

    //-----------------------------------------------------------------------
    template<typename CardT, const std::uint32_t _CARDS_COUNT, const std::uint32_t _START_VALUE>
        requires pltr::cards::is_standard_card_v<CardT>
    void StandardCardsDeck<CardT, _CARDS_COUNT, _START_VALUE>::_set_reference_deck()
    {
        if (!_reference_already_set) {
            _reference_deck.clear();

            /*
            for (typename MyBaseClass::IndexType ident = 0; ident < _CARDS_COUNT; ++ident) {
                CardT card(ident);
                card.value += _START_VALUE;
                _reference_deck.append_card(card);
            }
            */
            for (std::uint32_t i : std::views::iota(std::uint32_t(0), _CARDS_COUNT))
                _reference_deck.append_card(CardT(i, (i / 4) + _START_VALUE));

            _reference_already_set = true;
        }
    }



    //=======================================================================
    // Specializations
    //

    //-----------------------------------------------------------------------
    /* \brief 54 standard cards decks. */
    template<typename CardT>
    using CardsDeck54 = StandardCardsDeck<CardT, 54>;

    //-----------------------------------------------------------------------
    /* \brief 52 standard cards decks. */
    template<typename CardT>
    using CardsDeck52 = StandardCardsDeck<CardT, 52>;

    //-----------------------------------------------------------------------
    /* \brief 32 standard cards decks. */
    template<typename CardT>
    using CardsDeck32 = StandardCardsDeck<CardT, 32>;




    //=======================================================================
    // Type traits concepts
    //
    template<typename DeckT, typename CardT>
    struct is_standard_cards_deck {
        static inline constexpr bool value{ false };
    };

    template<typename DeckT, typename CardT>
    inline constexpr bool is_standard_cards_deck_v = is_standard_cards_deck<CardT>::value;


    template<typename CardT>
    struct is_standard_cards_deck<CardsDeck54<CardT>, CardT> {
        static inline constexpr bool value{ pltr::cards::is_standard_card_v<CardT> };
    };

    template<typename CardT>
    struct is_standard_cards_deck<CardsDeck52<CardT>, CardT> {
        static inline constexpr bool value{ pltr::cards::is_standard_card_v<CardT> };
    };

    template<typename CardT>
    struct is_standard_cards_deck<CardsDeck32<CardT>, CardT> {
        static inline constexpr bool value{ pltr::cards::is_standard_card_v<CardT> };
    };

}