# `unique_stantard_cards_deck_doc.md` - intro

This file documents the implementation of the class of decks that contain standard playing cards: `pltr::cards::UniqueStandardCardsDeck<>`.  
This class is defined within namespace `pltr::cards`. It inherits from its template class argument which must be of type `pltr::cards::StandardCardsDeck<>`.

The related header file is `include/pltr/playing_cards/unique_standard_cards_deck.h`.

It defines what are decks of standard playing cards and what are the actions that can be applied to them.

Notice: class `UniqueStandardCardsDeck<>` accepts the presence of only one occurence of any card in deck.  
For decks that may contain more than one same standard card ocurence, see class [`pltr::cards::StandardCardsDeck`](./standard_cards_deck_doc.md).


## `unique_standard_cards_deck.h` header file - table of content <!-- omit in toc -->
- [`unique_stantard_cards_deck_doc.md` - intro](#unique_stantard_cards_deck_docmd---intro)
- [class `UniqueStandardCardsDeck<>`](#class-uniquestandardcardsdeck)
  - [Types Wrappers](#types-wrappers)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`UniqueStandardCardsDeck()`](#uniquestandardcardsdeck)
    - [`UniqueStandardCardsDeck(const UniqueStandardCardsDeck&) noexcept`](#uniquestandardcardsdeckconst-uniquestandardcardsdeck-noexcept)
    - [`UniqueStandardCardsDeck(UniqueStandardCardsDeck&&) noexcept`](#uniquestandardcardsdeckuniquestandardcardsdeck-noexcept)
    - [`virtual ~UniqueStandardCardsDeck() noexcept`](#virtual-uniquestandardcardsdeck-noexcept)
  - [Assignment operators](#assignment-operators)
    - [`UniqueStandardCardsDeck& operator= (const UniqueStandardCardsDeck&)`](#uniquestandardcardsdeck-operator-const-uniquestandardcardsdeck)
    - [`UniqueStandardCardsDeck& operator= (UniqueStandardCardsDeck&&)`](#uniquestandardcardsdeck-operator-uniquestandardcardsdeck)
  - [Indexing operators](#indexing-operators)
    - [`CardType& operator[] (const IndexType index)`](#cardtype-operator-const-indextype-index)
    - [`const CardType& operator[] (const IndexType index) const`](#const-cardtype-operator-const-indextype-index-const)
  - [Accessors / Mutators](#accessors--mutators)
    - [`const IndexType get_current_cards_count() const`](#const-indextype-get_current_cards_count-const)
    - [`const IndexType get_max_cards_count() const noexcept`](#const-indextype-get_max_cards_count-const-noexcept)
    - [`CardsList<CardType>& deck()`](#cardslistcardtype-deck)
    - [`const CardsList<CardType>& deck() const`](#const-cardslistcardtype-deck-const)
  - [Operations](#operations)
    - [`virtual const bool allowed_card(const CardType& card) const noexcept override`](#virtual-const-bool-allowed_cardconst-cardtype-card-const-noexcept-override)
    - [`virtual const bool append_card(const CardType& card)`](#virtual-const-bool-append_cardconst-cardtype-card)
    - [`virtual void append_cards(const CardsList<CardType>& cards)`](#virtual-void-append_cardsconst-cardslistcardtype-cards)
    - [`inline void clear()`](#inline-void-clear)
    - [`inline virtual const bool contains(const CardType& card)  const`](#inline-virtual-const-bool-containsconst-cardtype-card--const)
    - [`inline const bool contains_all()  const`](#inline-const-bool-contains_all--const)
    - [`template<typename` `FirstT, typename... RestT>` `inline const bool contains_all(const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-inline-const-bool-contains_allconst-firstt-first-const-restt-rest)
    - [`const inline bool contains_all(const CardsList<CardType>& cards) const`](#const-inline-bool-contains_allconst-cardslistcardtype-cards-const)
    - [`inline const bool contains_any()  const`](#inline-const-bool-contains_any--const)
    - [`template<typename` `FirstT, typename... RestT>` `inline const bool contains_any(const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-inline-const-bool-contains_anyconst-firstt-first-const-restt-rest)
    - [`const bool contains_any(const CardsList<CardType>& cards) const`](#const-bool-contains_anyconst-cardslistcardtype-cards-const)
    - [`inline const CardType draw_card()`](#inline-const-cardtype-draw_card)
    - [`inline const bool draw_card(const CardType& card)`](#inline-const-bool-draw_cardconst-cardtype-card)
    - [`inline const CardsList<CardType> draw_n_cards(const IndexType n)`](#inline-const-cardslistcardtype-draw_n_cardsconst-indextype-n)
    - [`inline const CardType draw_nth_card(const IndexType index)`](#inline-const-cardtype-draw_nth_cardconst-indextype-index)
    - [`inline const CardType draw_rand_card()`](#inline-const-cardtype-draw_rand_card)
    - [`const IndexType get_index(const CardType& card) const`](#const-indextype-get_indexconst-cardtype-card-const)
    - [`virtual const bool insert_card(const CardType& card)`](#virtual-const-bool-insert_cardconst-cardtype-card)
    - [`inline void insert_cards()`](#inline-void-insert_cards)
    - [`template<typename` `FirstT, typename... RestT>` `void insert_cards(const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-void-insert_cardsconst-firstt-first-const-restt-rest)
    - [`virtual void insert_cards(const CardsList<CardType>& cards)`](#virtual-void-insert_cardsconst-cardslistcardtype-cards)
    - [`virtual const bool insert_nth_card(const IndexType index, const CardType& card)`](#virtual-const-bool-insert_nth_cardconst-indextype-index-const-cardtype-card)
    - [`void insert_nth_cards(const IndexType index)`](#void-insert_nth_cardsconst-indextype-index)
    - [`template<typename` `FirstT, typename... RestT>` `void insert_nth_cards(const IndexType index, const FirstT& first, const RestT&... rest)`](#templatetypename-firstt-typename-restt-void-insert_nth_cardsconst-indextype-index-const-firstt-first-const-restt-rest)
    - [`virtual void insert_nth_cards(const IndexType index, const CardsList<CardType>& cards)`](#virtual-void-insert_nth_cardsconst-indextype-index-const-cardslistcardtype-cards)
    - [`virtual const bool insert_rand_card(const CardType& card)`](#virtual-const-bool-insert_rand_cardconst-cardtype-card)
    - [`inline const bool is_empty() const noexcept`](#inline-const-bool-is_empty-const-noexcept)
    - [`inline const bool is_full() const noexcept`](#inline-const-bool-is_full-const-noexcept)
    - [`const CardType pop_bottom_card()`](#const-cardtype-pop_bottom_card)
    - [`const CardsList<CardType> pop_bottom_n_cards(const IndexType n)`](#const-cardslistcardtype-pop_bottom_n_cardsconst-indextype-n)
    - [`const CardType pop_indexed_card(const IndexType index)`](#const-cardtype-pop_indexed_cardconst-indextype-index)
    - [`const CardType pop_rand_card()`](#const-cardtype-pop_rand_card)
    - [`const CardType pop_up_card()`](#const-cardtype-pop_up_card)
    - [`const CardsList<CardType> pop_up_n_cards(const IndexType n)`](#const-cardslistcardtype-pop_up_n_cardsconst-indextype-n)
    - [`virtual void refill_deck() override`](#virtual-void-refill_deck-override)
    - [`void refill_deck(const CardsList<CardType>& filling_deck)`](#void-refill_deckconst-cardslistcardtype-filling_deck)
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
  - [`UniqueStandardCardsDeck54<>`](#uniquestandardcardsdeck54)
  - [`UniqueStandardCardsDeck52<>`](#uniquestandardcardsdeck52)
  - [`UniqueStandardCardsDeck32<>`](#uniquestandardcardsdeck32)
- [Type traits](#type-traits)
  - [`pltr::cards::is_unique_standard_cards_deck<>`](#pltrcardsis_unique_standard_cards_deck)
  - [`pltr::cards::is_unique_standard_cards_deck_v<>`](#pltrcardsis_unique_standard_cards_deck_v)


# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::cards::UniqueStandardCardsDeck<>` and of the other declarations and definitions set in header file `include/pltr/playing_cards/unique_standard_cards_deck.h`..


# class `UniqueStandardCardsDeck<>`
Defined in file `include/pltr/playing_cards/unique_standard_cards_deck.h`.

`UniqueStandardCardsDeck<>` is the class for all decks that contain standard playing cards, and each card no more than once. It can be used to simulate players decks in hand as well, in which case the different sorting methods defined in this class will be useful for displaying hands.

It is defined as a template:

```
template<typename StandardDeckT>
    requires pltr::cards::is_standard_cards_deck_v<StandardDeckT>
class UniqueStandardCardsDeck : public StandardDeckT
```

The template argument is:
- `StandardDeckT`:  
the type of standard cards deck from which `UniqueStandardCardsDeck<>` inherits. It gets no default value. It MUST conform to the `is_standard_cards_deck` requirement: see [`StandardCardsDeck<>`](./standard_cards_deck_doc.md) documentation to get an overview of what it is and for some localized specialization types that are provided with library **PlayTore**.

This class inherits from base class `pltr::cards::StandardCardsDeck<>` and as such, from `pltr::core::Object` also.


## Types Wrappers
```
using MyBaseClass = StandardDeckT;
using CardType = typename StandardDeckT::CardType;
using CardsList = pltr::cards::CardsList<CardType>;
using IndexType = MyBaseClass::IndexType;
```
Notice: indexes are used to index cards in the deck.


## Attributes
Cards deck have next attributes, all of them being **private** with accessors/mutators provided for some of them, each of them being inherited from base class `cards::CardsDeck<>`:
- `_deck`:  
of type `CardsList<CardType>`.  
This is the internal storage of the list of cards that are contained in this deck. It may be accessed ouotside this class via accessor/mutator `deck()`.
- `_max_cards_count`:  
of type `IndexType`.  
This is an internal control on the max count of cards that can be actually contained within this deck. This value may evolve along the running of your application. It can be accessed via the not mutable accessor method `get_max_cards_count()`.


## Constructors / Destructor

### `UniqueStandardCardsDeck()`  
The empty constructor. It automatically fills the deck with standard cards, each one only once, and prepares for further refillings of the deck with these cards.

### `UniqueStandardCardsDeck(const UniqueStandardCardsDeck&) noexcept`  
The default copy constructor.

### `UniqueStandardCardsDeck(UniqueStandardCardsDeck&&) noexcept`  
Thedefault move constructor.

### `virtual ~UniqueStandardCardsDeck() noexcept`  
The default destructor.


## Assignment operators

### `UniqueStandardCardsDeck& operator= (const UniqueStandardCardsDeck&)`
The default copy operator.

### `UniqueStandardCardsDeck& operator= (UniqueStandardCardsDeck&&)`
DeThe defaultfault move operator.


## Indexing operators

### `CardType& operator[] (const IndexType index)`  
Mutable indexing operator. May throw exception on bad index.  
*Inherited from base class*.

### `const CardType& operator[] (const IndexType index) const`  
Not mutable indexing const operator. May throw exception on bad index.  
*Inherited from base class*.


## Accessors / Mutators

### `const IndexType get_current_cards_count() const`  
Returns the count of cards currently contained in this deck. Not mutable.  
*Inherited from base class*.

### `const IndexType get_max_cards_count() const noexcept`  
Returns the max count of cards that can be contained in this deck. Not mutable.  
*Inherited from base class*.

### `CardsList<CardType>& deck()`  
Accessor to private deck content, mutable. To be used cautiously when modifying the content of the deck. Changing its content with a content with more cards than current `max_cards_count` value.  
*Inherited from base class*.

### `const CardsList<CardType>& deck() const`  
Accessor to private deck content, not mutable: no modifications are allowed, so safe to be used for reading any data in it.  
*Inherited from base class*.


## Operations

### `virtual const bool allowed_card(const CardType& card) const noexcept override`  
Returns true if the specified card is allowed to be contained in this deck.  
*Overridden from base class*.

### `virtual const bool append_card(const CardType& card)`  
Appends a card at bottom of this deck. Returns `true` if the appended card was not already contained in deck, and `false` otherwise.  
*Overridden from base class*.

### `virtual void append_cards(const CardsList<CardType>& cards)`  
Appends a list of cards at bottom of this deck. Cards are appended in their order in the passed list of cards. Does not append a card from list if it is already contained in deck.  
*Overridden from base class*.

### `inline void clear()`  
Empties the content of this deck. The value of `_max_cards_count` is not modified.  
*Inherited from base class*.

### `inline virtual const bool contains(const CardType& card)  const`  
Returns true if the card ident is found in this deck.  
*Inherited from base class*.

### `inline const bool contains_all()  const`  
This is the end of the containment searching recursion in this deck of all listed cards. Should not be called by library user - always return true.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `inline const bool contains_all(const FirstT& first, const RestT&... rest)`  
Returns true if all cards in list are contained in this deck.  
*Inherited from base class*.

### `const inline bool contains_all(const CardsList<CardType>& cards) const`  
Returns true if all of the passed cards are contained in this deck.  
*Inherited from base class*.

### `inline const bool contains_any()  const`  
This is the end of the containment searching recursion in this deck of any listed card. Should not be called by library user - always return false.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `inline const bool contains_any(const FirstT& first, const RestT&... rest)` 
Returns true if any card in list is contained in this deck.  
*Inherited from base class*.

### `const bool contains_any(const CardsList<CardType>& cards) const`  
Returns true if any of the passed cards is contained in this deck.  
*Inherited from base class*.

### `inline const CardType draw_card()`  
Wrapper to `pop_up_card()`: removes and returns the card at the top of this deck.  
*Inherited from base class*.

### `inline const bool draw_card(const CardType& card)`  
If present in deck, removes the card and returns true; returns false else.  
*Inherited from base class*.

### `inline const CardsList<CardType> draw_n_cards(const IndexType n)`  
Wrapper to `pop_up_n_cards()`: removes and returns `n` cards at the top of this deck. May return less than `n` cards if `n` > current deck size.  
*Inherited from base class*.

### `inline const CardType draw_nth_card(const IndexType index)`  
Wrapper to `pop_indexed_card()`: removes and returns the card at `index` position in this deck.  
*Inherited from base class*.

### `inline const CardType draw_rand_card()`  
Wrapper to `pop_rand_card()`: removes and returns a card at random position in this deck. (see note 1)  
*Inherited from base class*.

### `const IndexType get_index(const CardType& card) const`  
Returns the index of this card in deck if found, or `-1` if not found.  
*Inherited from base class*.

### `virtual const bool insert_card(const CardType& card)`  
Inserts a card at top of this deck. Returns `true` if the inserted card was not already contained in deck, and `false` otherwise.  
*Overridden from base class*.

### `inline void insert_cards()`  
This is the end of inserts recursion of cards in this deck. Should not be called by library user - does nothing.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `void insert_cards(const FirstT& first, const RestT&... rest)`  
Inserts a list of cards in this deck at top of deck. Any card from list that is already contained in deck is not inserted twice in it.  
*Inherited from base class*.

### `virtual void insert_cards(const CardsList<CardType>& cards)`  
Inserts `n` cards at top of this deck. Any card from list that is already contained in deck is not inserted twice in it.  
*Inherited from base class*.

### `virtual const bool insert_nth_card(const IndexType index, const CardType& card)`  
Inserts a card at n-th position in this deck. Returns `true` if the inserted card was not already contained in deck, and `false` otherwise.  
*Overridden from base class*.

### `void insert_nth_cards(const IndexType index)`  
This is the end of inserts recursion of cards at some position in this deck. Should not be called by library user - does nothing.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `void insert_nth_cards(const IndexType index, const FirstT& first, const RestT&... rest)`  
Inserts a list of cards in this deck. Any card from list that is already contained in deck is not inserted twice.   
*Inherited from base class*.

### `virtual void insert_nth_cards(const IndexType index, const CardsList<CardType>& cards)`  
Inserts a list of cards at `index` position in this deck. Deck max capacity may grow up then. Any card from list that is already contained in deck is not inserted twice.  
*Overridden from base class*.

### `virtual const bool insert_rand_card(const CardType& card)`  
Inserts a card at a random position in this deck. Returns `true` if the inserted card was not already contained in deck, and `false` otherwise. (see note 1).  
*Overridden from base class*.

### `inline const bool is_empty() const noexcept`  
Returns true when this deck is empty.  
*Inherited from base class*.

### `inline const bool is_full() const noexcept`  
Returns true when this deck is full.  
*Inherited from base class*.

### `const CardType pop_bottom_card()`  
Removes and returns the card at the bottom of this deck. May be considered as an optimized wrapper to `pop_card(_current_cards_count - 1)`.  
*Inherited from base class*.

### `const CardsList<CardType> pop_bottom_n_cards(const IndexType n)`  
Removes and returns n cards from the bottom of this deck. May return less than n cards if n > current deck size.  
*Inherited from base class*.

### `const CardType pop_indexed_card(const IndexType index)`  
Removes and returns the card at `index` in this deck. calls `pop_bottom_card()` if `index` > current deck size.  
*Inherited from base class*.

### `const CardType pop_rand_card()`  
Removes and returns a card at random position from this deck. (see note 1)  
*Inherited from base class*.

### `const CardType pop_up_card()`  
Removes and returns the card at the top of this deck. May be considered as an optimized wrapper to `pop_indexed_card(0)`.  
*Inherited from base class*.

### `const CardsList<CardType> pop_up_n_cards(const IndexType n)`  
Removes and returns `n` cards from top of this deck. May return less than `n` cards if `n` > current deck size.  
*Inherited from base class*.

### `virtual void refill_deck() override`  
Fills this deck with all related playing cards.
*Overridden from base class*.

### `void refill_deck(const CardsList<CardType>& filling_deck)`  
Fills this deck according to a filling vector. Empties the deck first. Any card in list that is already contained in deck is not inserted in it twice.  
*Inherited from base class*.

### `template<typename` `FirstT, typename... RestT>` `void refill_deck(const FirstT& first, const RestT&... rest)`  
Fills this deck according to a variable length list of cards. Empties the deck first. Any card in list that is already contained in deck is not inserted in it twice.  
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

## `UniqueStandardCardsDeck54<>`

This is a template class that defines 54 standard cards deck (i.e. all standard cards plus Jokers), each card being contained only once.

It is declared as
```
template<
    typename CardType,
    const std::uint32_t START_VALUE = 2,
    const std::uint32_t START_ORDERING_VALUE = 0
> requires pltr::cards::is_standard_card_v<CardType>
using UniqueStandardCardsDeck54 = UniqueStandardCardsDeck<CardsDeck54<CardType, START_VALUE, START_ORDERING_VALUE, 1>>;
```

## `UniqueStandardCardsDeck52<>`

This is a template class that defines 52 standard cards deck (i.e. all standard cards without Jokers), each card being contained only once.

It is declared as
```
template<
    typename CardType,
    const std::uint32_t START_VALUE = 2,
    const std::uint32_t START_ORDERING_VALUE = 0
> requires pltr::cards::is_standard_card_v<CardType>
using UniqueStandardCardsDeck52 = UniqueStandardCardsDeck<CardsDeck52<CardType, START_VALUE, START_ORDERING_VALUE, 1>>;
```

## `UniqueStandardCardsDeck32<>`

This is a template class that defines 32 standard cards deck (i.e. all standard cards without Jokers, 2's 3's 4's 5's and 6's), each card being contained only once.

It is declared as
```
template<
    typename CardType,
    const std::uint32_t START_VALUE = 2,
    const std::uint32_t START_ORDERING_VALUE = 0
> requires pltr::cards::is_standard_card_v<CardType>
using UniqueStandardCardsDeck32 = UniqueStandardCardsDeck<CardsDeck32<CardType, START_VALUE, START_ORDERING_VALUE, 1>>;
```


# Type traits
Defined in file `include/pltr/playing_cards/unique_standard_cards_deck.h`.

## `pltr::cards::is_unique_standard_cards_deck<>`
Declared as
```
template<typename UniqueStandardDeckT>
struct is_unique_standard_cards_deck
```
This *UnaryTypeTrait* checks whether type `T` is a `UniqueStandardCardDeck<>` type.  
It provides the member contant value `value` which is equal to `true` if `T` is an `UniqueStandardCardDeck<>` type or `false` otherwise.

## `pltr::cards::is_unique_standard_cards_deck_v<>`
Defined as
```
template<typename UniqueStandardDeckT>
constexpr bool is_unique_standard_cards_deck_v = is_standard_cards_deck<UniqueStandardDeckT>::value;
```
This is the related helper variable template. It provides direct access to the value of the above *UnaryTypeTrait* checker.
