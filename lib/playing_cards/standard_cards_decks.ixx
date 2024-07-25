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
        requires std::is_base_of<pltr::cards::StandardCard, CardT>
    class CardsDeck54 : public CardsDeck<CardT>
    {
    public:
        //-----   Type wrappers   -----//
        using MyBaseClass = CardsDeck<CardT>;


        //-----   Constructors / Desctructor   -----//
        CardsDeck54();                                      //!< empty constructor is disabled.

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
    // local implementations

    //-----------------------------------------------------------------------
    template<typename CardT>
        requires std::is_base_of<pltr::cards::StandardCard, CardT>
    CardsDeck54<CardT>::CardsDeck54()
        : MyBaseClass(_CARDS_COUNT)
    {}

    //-----------------------------------------------------------------------
    template<typename CardT>
        requires std::is_base_of<pltr::cards::StandardCard, CardT>
    void CardsDeck54<CardT>::refill_deck()
    {
        for (typename CardT::IndexType ident = 0; ident < _CARDS_COUNT; ++ident)
            append_card(ident, (ident / 4) + 1);
    }

}