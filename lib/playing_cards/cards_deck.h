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
#include <iterator>
#include <random>
#include <ranges>
#include <vector>


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    /* \brief The base class for decks of cards.
    */
    template<typename CardT>
    class CardsDeck
    {
    public:
        //-----   Types wrappers and declarations   -----//
        using MyCardType = CardT;
        using IndexType = std::uint32_t;
        using CardsList = std::vector<CardT>;


        //-----   Constructors / Desctructor   -----//
        CardsDeck() noexcept = default;                         //!< empty constructor is disabled.

        CardsDeck(const IndexType max_cards_count);             //!< constructor with size argument.

        CardsDeck(const CardsList& cards);                      //!< constructor with initialization vector.

        template<typename FirstCardT, typename... NextCardsT>
        CardsDeck(
            const IndexType max_cards_count,
            const FirstCardT& first_card,
            const NextCardsT&... next_cards)                    //!< constructor with initialization list
        {
            _set_deck(max_cards_count);
            _set_randomness();
            insert_cards(first_card, next_cards...);
        }

        CardsDeck(const CardsDeck&) noexcept = default;         //!< default copy constructor.
        CardsDeck(CardsDeck&&) noexcept = default;              //!< default move constructor.

        virtual ~CardsDeck() noexcept = default;                //!< default destructor.


        //-----   Operators   -----//
        CardsDeck& operator=(const CardsDeck&) noexcept = default;      //!< default copy operator.
        CardsDeck& operator=(CardsDeck&&) noexcept = default;           //!< default move operator.

        inline CardT& operator[] (const IndexType index)                //!< indexing operator. May throw exception on bad index.
        {
            return *_get_indexed_iterator(index);
        }

        inline const CardT& operator[] (const IndexType index) const    //!< indexing const operator. May throw exception on bad index.
        {
            return *_get_indexed_iterator(index);
        }


        //-----   Accessors   -----//
        [[nodiscard]]
        inline const IndexType get_current_cards_count() const noexcept //!< returns the count of cards currently contained in this deck.
        {
            return (const IndexType)this->_deck.size();
        }


        [[nodiscard]]
        inline const IndexType get_max_cards_count() const noexcept     //!< returns the max count of cards that can be contained in this deck.
        {
            return this->_max_cards_count;
        }


        inline const CardsList& deck() const noexcept                   //!< accessor to private deck content, no modifications allowed.
        {
            return this->_deck;
        }


        //-----   Operations   -----//
        virtual const bool append_card(const CardT& card);          //!< appends a card at bottom of this deck. Deck max capacity may grow up then. \see insert_card()

        virtual void append_cards(const CardsList& cards);          //!< appends n cards at bottom of this deck. Deck max capacity may grow up then.

        inline void clear()                                         //!< empties the content of this deck
        {
            this->_deck.clear();
            this->_deck.shrink_to_fit();
        }

        inline virtual const bool contains(const CardT& card) const //!< returns true if the card ident is found in this deck.
        {
            return get_index(card) != IndexType(-1);
        }

        inline const bool contains_all()  const                     //!< end of containment searching recursion of all cards in this deck. Should not be called by library user - always return true.
        {
            return true;
        }

        template<typename FirstT, typename... RestT>
        inline const bool contains_all(const FirstT& first, const RestT&... rest)    //!< returns true if all cards in list are contained in this deck.
        {
            return contains(first) && contains_all(rest...);
        }

        const inline bool contains_all(const CardsList& cards) const    //!< returns true if all of the passed cards are contained in this deck
        {
            return std::all_of(cards.cbegin(), cards.cend(), [this](const CardT& c) { return allowed_card(c) && contains(c); });
        }

        inline const bool contains_any()  const                     //!< end of containment searching recursion of any cards in this deck. Should not be called by library user - always return false.
        {
            return false;
        }

        template<typename FirstT, typename... RestT>
        inline const bool contains_any(const FirstT& first, const RestT&... rest)    //!< returns true if nay card in list is contained in this deck.
        {
            return contains(first) || contains_any(rest...);
        }

        const bool contains_any(const CardsList& cards) const       //!< returns true if any of the passed cards is contained in this deck
        {
            return std::any_of(cards.cbegin(), cards.cend(), [this](const CardT& c) { return allowed_card(c) && contains(c); });
        }

        inline const CardT draw_card()                              //!< wrapper to pop_up_card(): removes and returns the card at the top of this deck.
        {
            return pop_up_card();
        }

        inline const CardsList draw_n_cards(const IndexType n)      //!< wrapper to pop_up_n_cards(): removes and returns the card at the top of this deck. May return less than n cards if n > current deck size.
        {
            return pop_up_n_cards(n);
        }

        inline const CardT draw_nth_card(const IndexType index)     //!< wrapper to pop_indexed_card(): removes and returns the card at n-th position in this deck.
        {
            return pop_indexed_card(index);
        }

        inline const CardT draw_rand_card()                         //!< wrapper to pop_rand_card(): removes and returns a card at random position in this deck.
        {
            return pop_rand_card();
        }

        const IndexType get_index(const CardT& card) const;         //!< returns the index of this card in deck if found, or -1 if not found

        virtual const bool insert_card(const CardT& card);          //!< inserts a card at top of this deck. Deck max capacity may grow up then. \see append_card().

        inline void insert_cards()                                  //!< end of inserts recursion of cards in this deck. Should not be called by library user - does nothing.
        {}

        template<typename FirstT, typename... RestT>
        void insert_cards(const FirstT& first, const RestT&... rest)    //!< inserts a list of cards in this deck.
        {
            insert_cards(rest...);
            insert_card(first);
        }

        virtual void insert_cards(const CardsList& cards);           //!< inserts n cards at top of this deck. Deck max capacity may grow up then.

        virtual const bool insert_nth_card(const IndexType index, const CardT& card); //!< inserts a card at n-th position in this deck. Deck max capacity may grow up then.

        void insert_nth_cards(const IndexType index)                 //!< end of inserts recursion of cards at some position in this deck. Should not be called by library user - does nothing.
        {}

        template<typename FirstT, typename... RestT>
        void insert_nth_cards(const IndexType index, const FirstT& first, const RestT&... rest)   //!< inserts a list of cards in this deck.
        {
            insert_nth_cards(index, rest...);
            insert_nth_card(index, first);
        }

        virtual void insert_nth_cards(const IndexType index, const CardsList& cards);   //!< inserts n cards at n-th position in this deck. Deck max capacity may grow up then.

        virtual const bool insert_rand_card(const CardT& card);           //!< inserts a card at a random position in this deck. Deck max capacity may grow up then.

        [[nodiscard]]
        inline const bool is_empty() const noexcept                 //!< returns true when this deck is empty.
        {
            return this->_deck.empty();
        }

        [[nodiscard]]
        inline const bool is_full() const noexcept                  //!< returns true when this deck is full.
        {
            return !is_empty() && get_current_cards_count() == get_max_cards_count();
        }

        const CardT pop_bottom_card();                              //!< removes and returns the card at the bottom of this deck. May be considered as an optimized wrapper to pop_card(_current_cards_count - 1).

        const CardsList pop_bottom_n_cards(const IndexType n);      //!< removes and returns n cards from the bottom of this deck. May return less than n cards if n > current deck size.

        const CardT pop_indexed_card(const IndexType index);        //!< removes and returns the n-th card from top in this deck. calls pop_bottom_card() if n > current deck size.

        const CardT pop_rand_card()                                 //!< removes and returns a card at random position from this deck.
        {
            return pop_indexed_card(_get_random_index());
        }

        const CardT pop_up_card();                                  //!< removes and returns the card at the top of this deck. May be considered as an optimized wrapper to pop_indexed_card(0).

        const CardsList pop_up_n_cards(const IndexType index);      //!< removes and returns n cards from top of this deck. May return less than n cards if n > current deck size.

        inline virtual void refill_deck()                           //!< fills this deck with all related playing cards. Does nothing in this base class, must be overridden in inheriting classes.
        {}

        void refill_deck(const CardsList& filling_deck);            //!< fills this deck according to a filling vector. Empties the deck first.

        template<typename FirstT, typename... RestT>
        void refill_deck(const FirstT& first, const RestT&... rest)     //!< fills this deck according to a variable length list of cards. Empties the deck first.
        {
            if (sizeof...(rest) > 0) [[likely]] { // notice: necessary to not conflict with the virtual signature of refill() with no args
                refill_deck(rest...);
                insert_card(first);
            }
            else [[unlikely]] {
                clear();
                insert_card(first);
            }
        }

        void shuffle();                                             //!< shuffles this whole deck.

        void shuffle(const IndexType low, const IndexType high);    //!< shuffles some part of this deck. Automaticcaly clips indexes to the min and max values for this deck.


    private:
        std::uniform_real_distribution<float> _udistribution{ 1.0f };
        std::mt19937 _urand_generator{};
        CardsList _deck{};
        IndexType _max_cards_count{ 0 };

        [[nodiscard]]
        inline CardsList::iterator _get_indexed_iterator(const IndexType index)
        {
            return (index >= get_current_cards_count()) ? this->_deck.begin() : this->_deck.end() - index - 1;
        }

        [[nodiscard]]
        inline const CardsList::iterator _get_indexed_iterator(const IndexType index) const
        {
            return (index >= get_current_cards_count()) ? this->_deck.begin() : this->_deck.end() - index - 1;
        }

        [[nodiscard]]
        inline const IndexType _get_random_index()
        {
            return _get_random_index(this->get_current_cards_count());
        }

        [[nodiscard]]
        inline const IndexType _get_random_index(const IndexType n)
        {
            if (n > 0) [[likely]]
                return IndexType(this->_udistribution(this->_urand_generator) * float(n));
            else [[unlikely]]
                return IndexType(0);
        }

        inline void _set_deck()
        {
            _set_deck(this->_max_cards_count);
        }

        void _set_deck(const IndexType max_cards_count);

        void _set_randomness();

    };



    //=======================================================================
    // local implementations

    //-----------------------------------------------------------------------
    template<typename CardT>
    CardsDeck<CardT>::CardsDeck(const IndexType max_cards_count)
    {
        _set_deck(max_cards_count);
        _set_randomness();
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    CardsDeck<CardT>::CardsDeck(const CardsDeck<CardT>::CardsList& cards)
    {
        this->_deck = cards | std::views::reverse | std::ranges::to<decltype(this->_deck)>();
        this->_max_cards_count = std::uint32_t(this->_deck.size());
        _set_randomness();
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const bool CardsDeck<CardT>::append_card(const CardT& card)
    {
        // reminder: appends a card at bottom of this deck. Deck max capacity may grow up then.
        const bool allowed{ allowed_card(card) };
        if (allowed) {
            this->_deck.insert(this->_deck.begin(), card);
            this->_max_cards_count = std::max(this->_max_cards_count, std::uint32_t(this->_deck.size()));
        }
        return allowed;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::append_cards(const CardsList& cards)
    {
        // reminder: appends n cards at bottom of this deck. Deck max capacity may grow up then.
        this->_deck.insert_range(
            this->_deck.begin(),
            cards | std::views::filter([this](const CardT& c) { return this->allowed_card(c); }) | std::views::reverse
        );

        this->_max_cards_count = std::max(this->_max_cards_count, std::uint32_t(this->_deck.size()));
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const CardsDeck<CardT>::IndexType CardsDeck<CardT>::get_index(const CardT& card) const
    {
        // reminder: returns the index of this card in deck if found, or -1 if not found
        auto start_it{ this->_deck.crbegin() };
        auto end_it{ this->_deck.crend() };
        auto found_it{ std::find_if(start_it, end_it, [card](const CardT& c) {return c.ident == card.ident; }) };
        return IndexType(found_it == end_it ? -1 : found_it - start_it);
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const bool CardsDeck<CardT>::insert_card(const CardT& card)
    {
        // reminder: inserts a card at top of this deck. Deck max capacity may grow up then.
        const bool allowed{ allowed_card(card) };
        if (allowed) {
            this->_deck.push_back(card);
            this->_max_cards_count = std::max(this->_max_cards_count, std::uint32_t(this->_deck.size()));
        }
        return allowed;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::insert_cards(const CardsList& cards)
    {
        // reminder: inserts n cards at top of this deck. Deck max capacity may grow up then.
        // notice: very simple but not optimized implementation
        for (auto& card : cards)
            insert_card(card);
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const bool CardsDeck<CardT>::insert_nth_card(const IndexType index, const CardT& card)
    {
        // reminder! inserts a card at n-th position in this deck. Deck max capacity may grow up then.
        const bool allowed{ allowed_card(card) };
        if (allowed) {
            auto indexed_it{ _get_indexed_iterator(index) };
            if (index < get_max_cards_count())
                ++indexed_it;
            this->_deck.insert(indexed_it, card);
            this->_max_cards_count = std::max(this->_max_cards_count, std::uint32_t(this->_deck.size()));
        }
        return allowed;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::insert_nth_cards(const IndexType index, const CardsList& cards)
    {
        // reminder: inserts n cards at n-th position in this deck. Deck max capacity may grow up then.
        auto indexed_it{ _get_indexed_iterator(index) };
        if (index < get_max_cards_count())
            ++indexed_it;
        
        this->_deck.insert_range(
            indexed_it,
            cards | std::views::filter([this](const CardT& c) { return this->allowed_card(c); })
                  | std::views::reverse
        );

        this->_max_cards_count = std::max(this->_max_cards_count, std::uint32_t(this->_deck.size()));
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const bool CardsDeck<CardT>::insert_rand_card(const CardT& card)
    {
        // reminder: inserts a card at a random position in this deck. Deck max capacity may grow up then.
        const bool allowed{ allowed_card(card) };
        if (allowed) {
            insert_nth_card(_get_random_index(), card);
            this->_max_cards_count = std::max(this->_max_cards_count, std::uint32_t(this->_deck.size()));
        }
        return allowed;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const CardT CardsDeck<CardT>::pop_bottom_card()
    {
        // reminder: removes and returns the card at the bottom of this deck. May be considered as an optimized wrapper to pop_card(_current_cards_count - 1).
        const CardT popped_card{ this->_deck.front() };
        this->_deck.erase(this->_deck.begin());
        return popped_card;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const CardsDeck<CardT>::CardsList CardsDeck<CardT>::pop_bottom_n_cards(const IndexType n)
    {
        // reminder: removes and returns n cards from the bottom of this deck. May return less than n cards if n > current deck size.
        CardsList returned_list;
        for (IndexType i = 0; i < n && !is_empty(); ++i)
            returned_list.insert(returned_list.begin(), pop_bottom_card());
        return returned_list;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const CardT CardsDeck<CardT>::pop_indexed_card(const IndexType index)
    {
        // reminder: removes and returns the n-th card from top in this deck. calls pop_bottom_card() if n > current deck size.
        auto it{ _get_indexed_iterator(index) };
        const CardT popped_card{ *it };
        this->_deck.erase(it);
        return popped_card;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const CardT CardsDeck<CardT>::pop_up_card()
    {
        // reminder: removes and returns the card at the top of this deck. May be considered as an optimized wrapper to pop_indexed_card(0).
        const CardT popped_card{ this->_deck.back() };
        this->_deck.pop_back();
        return popped_card;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    const CardsDeck<CardT>::CardsList CardsDeck<CardT>::pop_up_n_cards(const IndexType n)
    {
        // reminder: removes and returns n cards from top of this deck. May return less than n cards if n > current deck size.
        CardsList returned_list;
        for (IndexType i = 0; i < n && !is_empty(); ++i)
            returned_list.push_back(pop_up_card());
        return returned_list;
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::refill_deck(const CardsList& filling_deck)
    {
        // reminder: fills this deck according to a filling vector. Empties the deck first.
        clear();
        if (!filling_deck.empty()) [[likely]] {
            this->_deck.reserve(filling_deck.size());
            append_cards(filling_deck);
            this->_max_cards_count = (decltype(this->_max_cards_count))filling_deck.size();
        }
        else [[unlikely]] {
            this->_max_cards_count = 0;
        }
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::shuffle()
    {
        // reminder: shuffles this whole deck.
        for (IndexType n = IndexType(this->_deck.size() - 1); n > 0; --n) {
            const IndexType i{ _get_random_index(n) };
            if (i != n)
                std::swap(this->_deck[n], this->_deck[i]);
        }
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::shuffle(const IndexType low, const IndexType high)
    {
        // reminder: shuffles some part of this deck. Automaticcaly clips indexes to the min and max values for this deck.
        const IndexType low_{ std::min(low, get_current_cards_count()) };
        const IndexType high_{ std::min(high, get_current_cards_count()) };

        for (IndexType n = high_ - low_; n > 0; --n) {
            const IndexType i{ _get_random_index(n + 1) };
            if (i != n)
                std::swap(this->_deck[low_ + n], this->_deck[low_ + i]);
        }
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::_set_deck(const IndexType max_cards_count)
    {
        this->_max_cards_count = max_cards_count;
        this->_deck.reserve(max_cards_count);
        this->refill_deck();
    }

    //-----------------------------------------------------------------------
    template<typename CardT>
    void CardsDeck<CardT>::_set_randomness()
    {
        std::random_device rd_seed;
        this->_urand_generator.seed(rd_seed());
    }

}