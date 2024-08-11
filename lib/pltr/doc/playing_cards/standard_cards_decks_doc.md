# `stantard_cards_deck_doc.md` - intro

This file documents the implementation of the class of decks that contain standard playing cards: `pltr::cards::StandardCardsDeck<>`.  
This class is defined within namespace `pltr::cards`. It inherits from base class `pltr::cards::CardsDeck<>`.

The related header file is `include/pltr/playing_cards/standard_cards_deck.h`.

It defines what are decks of standaard playing cards and what are the actions that can be applied to them.

Notice: class `StandardCardsDeck<>` accepts the presence of multiple occurences of same card in deck. Some cards game rules state that multiple decks must be used altogether to play (e.g. the rules of Rami when more than 4 players are involved, or to simulate Blackjack sessions).  
For decks that contain at most one same standard card and not more at a time, see class [`pltr::cards::UniqueStandardCardsDeck`](./unique_standard_cards_deck_doc.md).


## `standard_cards_deck.h` header file - table of content <!-- omit in toc -->
- [`stantard_cards_deck_doc.md` - intro](#stantard_cards_deck_docmd---intro)
- [class `StandardCardsDeck<>`](#class-standardcardsdeck)
  - [Types Wrappers](#types-wrappers)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`StandardCardsDeck()`](#standardcardsdeck)
    - [`StandardCardsDeck(const StandardCardsDeck&) noexcept`](#standardcardsdeckconst-standardcardsdeck-noexcept)
    - [`StandardCardsDeck(StandardCardsDeck&&) noexcept`](#standardcardsdeckstandardcardsdeck-noexcept)
    - [`virtual ~StandardCardsDeck() noexcept`](#virtual-standardcardsdeck-noexcept)
  - [Assignment operators](#assignment-operators)
    - [`StandardCardsDeck& operator= (const StandardCardsDeck&)`](#standardcardsdeck-operator-const-standardcardsdeck)
    - [`StandardCardsDeck& operator= (CardsDeStandardCardsDeckck&&)`](#standardcardsdeck-operator-cardsdestandardcardsdeckck)
  - [Indexing operators](#indexing-operators)
    - [`CardT& operator[] (const IndexType index)`](#cardt-operator-const-indextype-index)
    - [`const CardT& operator[] (const IndexType index) const`](#const-cardt-operator-const-indextype-index-const)
  - [Accessors / Mutators](#accessors--mutators)
    - [`const IndexType get_current_cards_count() const`](#const-indextype-get_current_cards_count-const)
    - [`const IndexType get_max_cards_count() const noexcept`](#const-indextype-get_max_cards_count-const-noexcept)
    - [`CardsList<CardT>& deck()`](#cardslistcardt-deck)
    - [`const CardsList<CardT>& deck() const`](#const-cardslistcardt-deck-const)
  - [Operations](#operations)
    - [`virtual const bool allowed_card(const CardT& card) const noexcept override`](#virtual-const-bool-allowed_cardconst-cardt-card-const-noexcept-override)
    - [`virtual const bool append_card(const CardT& card)`](#virtual-const-bool-append_cardconst-cardt-card)
    - [`virtual void append_cards(const CardsList<CardT>& cards)`](#virtual-void-append_cardsconst-cardslistcardt-cards)
    - [`inline void clear()`](#inline-void-clear)
    - [`inline virtual const bool contains(const CardT& card)  const`](#inline-virtual-const-bool-containsconst-cardt-card--const)
    - [`inline const bool contains_all()  const`](#inline-const-bool-contains_all--const)
    - [`template<typename` `FirstT, typename... RestT>` `inline const bool contains_all(const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-inline-const-bool-contains_allconst-firstt-first-const-restt-rest)
    - [`const inline bool contains_all(const CardsList<CardT>& cards) const`](#const-inline-bool-contains_allconst-cardslistcardt-cards-const)
    - [`inline const bool contains_any()  const`](#inline-const-bool-contains_any--const)
    - [`template<typename` `FirstT, typename... RestT>` `inline const bool contains_any(const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-inline-const-bool-contains_anyconst-firstt-first-const-restt-rest)
    - [`const bool contains_any(const CardsList<CardT>& cards) const`](#const-bool-contains_anyconst-cardslistcardt-cards-const)
    - [`inline const CardT draw_card()`](#inline-const-cardt-draw_card)
    - [`inline const bool draw_card(const CardT& card)`](#inline-const-bool-draw_cardconst-cardt-card)
    - [`inline const CardsList<CardT> draw_n_cards(const IndexType n)`](#inline-const-cardslistcardt-draw_n_cardsconst-indextype-n)
    - [`inline const CardT draw_nth_card(const IndexType index)`](#inline-const-cardt-draw_nth_cardconst-indextype-index)
    - [`inline const CardT draw_rand_card()`](#inline-const-cardt-draw_rand_card)
    - [`const IndexType get_index(const CardT& card) const`](#const-indextype-get_indexconst-cardt-card-const)
    - [`virtual const bool insert_card(const CardT& card)`](#virtual-const-bool-insert_cardconst-cardt-card)
    - [`inline void insert_cards()`](#inline-void-insert_cards)
    - [`template<typename` `FirstT, typename... RestT>` `void insert_cards(const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-void-insert_cardsconst-firstt-first-const-restt-rest)
    - [`virtual void insert_cards(const CardsList<CardT>& cards)`](#virtual-void-insert_cardsconst-cardslistcardt-cards)
    - [`virtual const bool insert_nth_card(const IndexType index, const CardT& card)`](#virtual-const-bool-insert_nth_cardconst-indextype-index-const-cardt-card)
    - [`void insert_nth_cards(const IndexType index)`](#void-insert_nth_cardsconst-indextype-index)
    - [`template<typename` `FirstT, typename... RestT>` `void insert_nth_cards(const IndexType index, const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-void-insert_nth_cardsconst-indextype-index-const-firstt-first-const-restt-rest)
    - [`virtual void insert_nth_cards(const IndexType index, const CardsList<CardT>& cards)`](#virtual-void-insert_nth_cardsconst-indextype-index-const-cardslistcardt-cards)
    - [`virtual const bool insert_rand_card(const CardT& card)`](#virtual-const-bool-insert_rand_cardconst-cardt-card)
    - [`inline const bool is_empty() const noexcept`](#inline-const-bool-is_empty-const-noexcept)
    - [`inline const bool is_full() const noexcept`](#inline-const-bool-is_full-const-noexcept)
    - [`const CardT pop_bottom_card()`](#const-cardt-pop_bottom_card)
    - [`const CardsList<CardT> pop_bottom_n_cards(const IndexType n)`](#const-cardslistcardt-pop_bottom_n_cardsconst-indextype-n)
    - [`const CardT pop_indexed_card(const IndexType index)`](#const-cardt-pop_indexed_cardconst-indextype-index)
    - [`const CardT pop_rand_card()`](#const-cardt-pop_rand_card)
    - [`const CardT pop_up_card()`](#const-cardt-pop_up_card)
    - [`const CardsList<CardT> pop_up_n_cards(const IndexType n)`](#const-cardslistcardt-pop_up_n_cardsconst-indextype-n)
    - [`virtual void refill_deck() override`](#virtual-void-refill_deck-override)
    - [`void refill_deck(const CardsList<CardT>& filling_deck)`](#void-refill_deckconst-cardslistcardt-filling_deck)
    - [`template<typename` `FirstT, typename... RestT>` `void refill_deck(const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-void-refill_deckconst-firstt-first-const-restt-rest)
    - [`void shuffle()`](#void-shuffle)
    - [`void shuffle(const IndexType low, const IndexType high)`](#void-shuffleconst-indextype-low-const-indextype-high)
    - [`void sort()`](#void-sort)
    - [`void sort_colors_values()`](#void-sort_colors_values)
    - [`void sort_idents()`](#void-sort_idents)
  - [Internal implementation topics](#internal-implementation-topics)
  - [Notes](#notes)
    - [note 1](#note-1)
- [Specializations](#specializations)
  - [`CardsDeck54<>`](#cardsdeck54)
  - [`CardsDeck52<>`](#cardsdeck52)
  - [`CardsDeck22<>`](#cardsdeck22)
- [Type traits](#type-traits)
  - [`pltr::cards::is_standard_cards_deck<>`](#pltrcardsis_standard_cards_deck)
  - [`pltr::cards::is_standard_cards_deck_v<>`](#pltrcardsis_standard_cards_deck_v)


# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::cards::StandardCardsDeck<>` and of the other declarations and definitions set in header file `include/pltr/playing_cards/standard_cards_deck.h`..


# class `StandardCardsDeck<>`
Defined in file `include/pltr/playing_cards/standard_cards_deck.h`.

`StandardCardsDeck<>` is the class for all decks that contain standard playing cards. It can be used to simulate players decks in hand as well, in which case the different sorting methods defined in this class will be useful for displaying hands.

It is defined as a template:

```
template<
    typename CardT,
    const std::uint32_t _CARDS_COUNT,
    const std::uint32_t _START_INDEX = 0,
    const std::uint32_t _START_VALUE = 0,
    const std::uint32_t _START_ORDERING_VALUE = 0,
    const std::uint32_t _DECKS_COUNT = 1
>
    requires pltr::cards::is_standard_card_v<CardT>
class StandardCardsDeck : public CardsDeck<CardT>

 ```

The template arguments are:
- `CardT`:  
the type of playing cards that are contained in this type of deck. It gets no default value. It MUST conform to the `is_standard_card` requirement: see [`StandardCard<>`](./standard_cards_doc.md) documentation to get an overview of what it is and for some localized specialization types that are provided with library **PlayTore**.
- `_CARDS_COUNT`:  
the count of cards that are contained in this type of deck. Mostly, this should be 32, 52 or 54. See specializations of the template at end of this documentation.
- `_START_INDEX`:  
the lowest index to be assigned to cards that are contained in this deck. This index should be unique for every different card, while in this base class a same card may be present many times in a deck;
- `_START_VALUE`:  
the lowest value to be set for cards in deck. This is used when filling the deck with cards at construction time. It is associated with the card with the lowest face value and is incremented by one for each next face value. Defaults to 0 in this base class.  
Notice: defaults to 2 for 54- and 52- cards decks specializations; defaults to 7 for 32 cards decks specialization;
- `_START_ORDERING_VALUE`:  
the lowest ordering value to be set for cards in deck. This is used when filling the deck with cards at construction time. It is associated with the card with the lowest identifier in deck and is incremented by one for each next card. Defaults to 0 in this base class as well as in its  specializations;
- `_DECKS_COUNT`:  
the number of same decks containing each `_CARDS_COUNT` cards that are to be mixed in this deck; defaults to 1. This way, it is possible to get a deck taht contains multiple times same cards.

This class inherits from class `pltr::cards::CardsDeck<CardT>` and as such, from `pltr::core::Object` also.


## Types Wrappers
```
using MyBaseClass = pltr::cards::CardsDeck<CardT>;
using CardsList = pltr::cards::CardsList<CardT>;
using CardType = CardT;
```
Notice: indexes are used to index cards in the deck.


## Attributes
Cards deck have next attributes, all of them being **private** with accessors/mutators provided for some of them, each of them being inherited from base class `cards::CardsDeck<>`:
- `_deck`:  
of type `CardsList<CardT>`.  
This is the internal storage of the list of cards that are contained in this deck. It may be accessed ouotside this class via accessor/mutator `deck()`.
- `_max_cards_count`:  
of type `IndexType`.  
This is an internal control on the max count of cards that can be actually contained within this deck. This value may evolve along the running of your application. It can be accessed via the not mutable accessor method `get_max_cards_count()`.


## Constructors / Destructor

### `StandardCardsDeck()`  
The empty constructor. It automatically fills the deck with standard cards, each one as many times as stated by template parameter `_DECKS_COUNT`, and prepares for further refillings of the deck with these cards.

### `StandardCardsDeck(const StandardCardsDeck&) noexcept`  
The default copy constructor.

### `StandardCardsDeck(StandardCardsDeck&&) noexcept`  
Thedefault move constructor.

### `virtual ~StandardCardsDeck() noexcept`  
The default destructor.


## Assignment operators

### `StandardCardsDeck& operator= (const StandardCardsDeck&)`
The default copy operator.

### `StandardCardsDeck& operator= (CardsDeStandardCardsDeckck&&)`
DeThe defaultfault move operator.


## Indexing operators

### `CardT& operator[] (const IndexType index)`  
Mutable indexing operator. May throw exception on bad index.  
*Inherited from base class*.

### `const CardT& operator[] (const IndexType index) const`  
Not mutable indexing const operator. May throw exception on bad index.  
*Inherited from base class*.


## Accessors / Mutators

### `const IndexType get_current_cards_count() const`  
Returns the count of cards currently contained in this deck. Not mutable.  
*Inherited from base class*.

### `const IndexType get_max_cards_count() const noexcept`  
Returns the max count of cards that can be contained in this deck. Not mutable.  
*Inherited from base class*.

### `CardsList<CardT>& deck()`  
Accessor to private deck content, mutable. To be used cautiously when modifying the content of the deck. Changing its content with a content with more cards than current `max_cards_count` value.  
*Inherited from base class*.

### `const CardsList<CardT>& deck() const`  
Accessor to private deck content, not mutable: no modifications are allowed, so safe to be used for reading any data in it.  
*Inherited from base class*.


## Operations

### `virtual const bool allowed_card(const CardT& card) const noexcept override`  
Returns true if the specified card is allowed to be contained in this deck.

### `virtual const bool append_card(const CardT& card)`  
Appends a card at bottom of this deck. Deck max capacity may grow up then. See `insert_card()`.  
*Inherited from base class*.

### `virtual void append_cards(const CardsList<CardT>& cards)`  
Appends a list of cards at bottom of this deck. Cards are appended in their order in the passed list of cards. Deck max capacity may grow up then.  
*Inherited from base class*.

### `inline void clear()`  
Empties the content of this deck. The value of `_max_cards_count` is not modified.  
*Inherited from base class*.

### `inline virtual const bool contains(const CardT& card)  const`  
Returns true if the card ident is found in this deck.  
*Inherited from base class*.

### `inline const bool contains_all()  const`  
This is the end of the containment searching recursion in this deck of all listed cards. Should not be called by library user - always return true.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `inline const bool contains_all(const FirstT& first, const RestT&... rest)`  
Returns true if all cards in list are contained in this deck.  
*Inherited from base class*.

### `const inline bool contains_all(const CardsList<CardT>& cards) const`  
Returns true if all of the passed cards are contained in this deck.  
*Inherited from base class*.

### `inline const bool contains_any()  const`  
This is the end of the containment searching recursion in this deck of any listed card. Should not be called by library user - always return false.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `inline const bool contains_any(const FirstT& first, const RestT&... rest)` 
Returns true if any card in list is contained in this deck.  
*Inherited from base class*.

### `const bool contains_any(const CardsList<CardT>& cards) const`  
Returns true if any of the passed cards is contained in this deck.  
*Inherited from base class*.

### `inline const CardT draw_card()`  
Wrapper to `pop_up_card()`: removes and returns the card at the top of this deck.  
*Inherited from base class*.

### `inline const bool draw_card(const CardT& card)`  
If present in deck, removes the card and returns true; returns false else.  
*Inherited from base class*.

### `inline const CardsList<CardT> draw_n_cards(const IndexType n)`  
Wrapper to `pop_up_n_cards()`: removes and returns `n` cards at the top of this deck. May return less than `n` cards if `n` > current deck size.  
*Inherited from base class*.

### `inline const CardT draw_nth_card(const IndexType index)`  
Wrapper to `pop_indexed_card()`: removes and returns the card at `index` position in this deck.  
*Inherited from base class*.

### `inline const CardT draw_rand_card()`  
Wrapper to `pop_rand_card()`: removes and returns a card at random position in this deck. (see note 1)  
*Inherited from base class*.

### `const IndexType get_index(const CardT& card) const`  
Returns the index of this card in deck if found, or `-1` if not found.  
*Inherited from base class*.

### `virtual const bool insert_card(const CardT& card)`  
Inserts a card at top of this deck. Deck max capacity may grow up then. \see append_card().  
*Inherited from base class*.

### `inline void insert_cards()`  
This is the end of inserts recursion of cards in this deck. Should not be called by library user - does nothing.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `void insert_cards(const FirstT& first, const RestT&... rest)`  
Inserts a list of cards in this deck at top of deck.  
*Inherited from base class*.

### `virtual void insert_cards(const CardsList<CardT>& cards)`  
Inserts `n` cards at top of this deck. Deck max capacity may grow up then.  
*Inherited from base class*.

### `virtual const bool insert_nth_card(const IndexType index, const CardT& card)`  
Inserts a card at n-th position in this deck. Deck max capacity may grow up then.  
*Inherited from base class*.

### `void insert_nth_cards(const IndexType index)`  
This is the end of inserts recursion of cards at some position in this deck. Should not be called by library user - does nothing.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `void insert_nth_cards(const IndexType index, const FirstT& first, const RestT&... rest)`  
Inserts a list of cards in this deck.  
*Inherited from base class*.

### `virtual void insert_nth_cards(const IndexType index, const CardsList<CardT>& cards)`  
Inserts a list of cards at `index` position in this deck. Deck max capacity may grow up then.  
*Inherited from base class*.

### `virtual const bool insert_rand_card(const CardT& card)`  
Inserts a card at a random position in this deck. Deck max capacity may grow up then. (see note 1)  
*Inherited from base class*.

### `inline const bool is_empty() const noexcept`  
Returns true when this deck is empty.  
*Inherited from base class*.

### `inline const bool is_full() const noexcept`  
Returns true when this deck is full.  
*Inherited from base class*.

### `const CardT pop_bottom_card()`  
Removes and returns the card at the bottom of this deck. May be considered as an optimized wrapper to `pop_card(_current_cards_count - 1)`.  
*Inherited from base class*.

### `const CardsList<CardT> pop_bottom_n_cards(const IndexType n)`  
Removes and returns n cards from the bottom of this deck. May return less than n cards if n > current deck size.  
*Inherited from base class*.

### `const CardT pop_indexed_card(const IndexType index)`  
Removes and returns the card at `index` in this deck. calls `pop_bottom_card()` if `index` > current deck size.  
*Inherited from base class*.

### `const CardT pop_rand_card()`  
Removes and returns a card at random position from this deck. (see note 1)  
*Inherited from base class*.

### `const CardT pop_up_card()`  
Removes and returns the card at the top of this deck. May be considered as an optimized wrapper to `pop_indexed_card(0)`.  
*Inherited from base class*.

### `const CardsList<CardT> pop_up_n_cards(const IndexType n)`  
Removes and returns `n` cards from top of this deck. May return less than `n` cards if `n` > current deck size.  
*Inherited from base class*.

### `virtual void refill_deck() override`  
Fills this deck with all related playing cards. Does nothing in this base class, must be overridden in inheriting classes.

### `void refill_deck(const CardsList<CardT>& filling_deck)`  
Fills this deck according to a filling vector. Empties the deck first.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `void refill_deck(const FirstT& first, const RestT&... rest)`  
Fills this deck according to a variable length list of cards. Empties the deck first.  
*Inherited from base class*.

### `void shuffle()`  
Shuffles this whole deck. (see note 1)  
*Inherited from base class*.

### `void shuffle(const IndexType low, const IndexType high)`  
Shuffles some part of this deck. Automaticcaly clips indexes to the min and max values for this deck. (see note 1)  
*Inherited from base class*.

### `void sort()`  
Sorts this deck according to descending order of values then in the descending order of colors.

### `void sort_colors_values()`  
Sorts this deck according to the descending order of colors first then on cards descending values in same color.

### `void sort_idents()`  
Ssorts this deck according to the descending order of colors first then on cards descending idents in same color.


## Internal implementation topics
A static reference deck is initialized once for every specialization of template `cards::StandardCardsDeck<>`. The initialization takes place at the very first instantiation of the specialized class. This reference deck is used back every time a call to `refill_deck()` is done. It is a way to speed up refills.


## Notes

### note 1
Base class `pltr::cards::CardsDeck<>` uses internally and per default the (not-thread safe) **PlayTore** core class `pltr::core::Random`, defined in header file `pltr/core/random.h`. The curious reader will take benefit from looking at the implemented code of private method `CardsDeck<>::_get_random_index(const IndexType max_index)`.


# Specializations
Defined in file `include/pltr/playing_cards/standard_cards_deck.h`.

## `CardsDeck54<>`

This is a template class that defines 54 standard cards deck (i.e. all standard cards plus Jokers).

It is declared as
```
template<
    typename CardT,
    const std::uint32_t START_VALUE = 2,
    const std::uint32_t START_ORDERING_VALUE = 0,
    const std::uint32_t _DECKS_COUNT = 1
>
using CardsDeck54 = StandardCardsDeck<CardT, 54, 0, START_VALUE, START_ORDERING_VALUE, _DECKS_COUNT>;
```

## `CardsDeck52<>`

This is a template class that defines 52 standard cards deck (i.e. all standard cards without Jokers).

It is declared as
```
template<
    typename CardT,
    const std::uint32_t START_VALUE = 2,
    const std::uint32_t START_ORDERING_VALUE = 0,
    const std::uint32_t _DECKS_COUNT = 1
>
using CardsDeck52 = StandardCardsDeck<CardT, 52, 0, START_VALUE, START_ORDERING_VALUE, _DECKS_COUNT>;
```

## `CardsDeck22<>`

This is a template class that defines 22 standard cards deck (i.e. all standard cards without Jokers, 2's 3's 4's 5's and 6's).

It is declared as
```
template<
    typename CardT,
    const std::uint32_t START_VALUE = 7,
    const std::uint32_t START_ORDERING_VALUE = 0,
    const std::uint32_t _DECKS_COUNT = 1
>
using CardsDeck32 = StandardCardsDeck<CardT, 32, 20, START_VALUE, START_ORDERING_VALUE, _DECKS_COUNT>;
```


# Type traits
Defined in file `include/pltr/playing_cards/standard_cards_deck.h`.

## `pltr::cards::is_standard_cards_deck<>`
Declared as
```
template<typename DeckT, typename CardT = typename DeckT::CardType>
struct is_standard_cards_deck
```
This *UnaryTypeTrait* checks whether type `T` is a `StandardCardDeck<>` type.  
It provides the member contant value `value` which is equal to `true` if `T` is a `StandardCardDeck<>` type or `false` otherwise. Notice: returns true for all template specializations defined in here.

## `pltr::cards::is_standard_cards_deck_v<>`
Defined as
```
template<typename DeckT, typename CardT = typename DeckT::CardType>
constexpr bool is_standard_cards_deck_v = is_standard_cards_deck<DeckT>::value;
```
This is the related helper variable template. It provides direct access to the value of the above *UnaryTypeTrait* checker.
