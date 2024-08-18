# `cards_deck_doc.md` - intro

This file documents the implementation of the base class for all types decks that contain playing cards: `pltr::cards::CardsDeck<>`. This class is defined within namespace `pltr::cards`.

The related header file is `include/pltr/playing_cards/cards_deck.h`.

It defines what are decks of playing cards and what are the actions that can be applied to them.


## `cards_deck.h` header file - table of content <!-- omit in toc -->
- [`cards_deck_doc.md` - intro](#cards_deck_docmd---intro)
- [class type `CardsList<>`](#class-type-cardslist)
- [class `CardsDeck<>`](#class-cardsdeck)
  - [Types Wrappers](#types-wrappers)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`CardsDeck ()`](#cardsdeck-)
    - [`CardsDeck (const IndexType max_cards_count)`](#cardsdeck-const-indextype-max_cards_count)
    - [`CardsDeck(const CardsList<CardT>& cards)`](#cardsdeckconst-cardslistcardt-cards)
    - [`CardsDeck (const CardsList<CardT>& cards, std::filesystem::path& back_image_path_)`](#cardsdeck-const-cardslistcardt-cards-stdfilesystempath-back_image_path_)
    - [`template<typename... NextCardsT> CardsDeck (const IndexType max_cards_count, const CardT& first_card, const NextCardsT&... next_cards)`](#templatetypename-nextcardst-cardsdeck-const-indextype-max_cards_count-const-cardt-first_card-const-nextcardst-next_cards)
    - [`template<typename... NextCardsT> CardsDeck (const IndexType max_cards_count, const std::filesystem::path& back_image_path_, const CardT& first_card, const NextCardsT&... next_cards)`](#templatetypename-nextcardst-cardsdeck-const-indextype-max_cards_count-const-stdfilesystempath-back_image_path_-const-cardt-first_card-const-nextcardst-next_cards)
    - [`CardsDeck(const CardsDeck&)`](#cardsdeckconst-cardsdeck)
    - [`CardsDeck(CardsDeck&&)`](#cardsdeckcardsdeck)
    - [`virtual ~CardsDeck()`](#virtual-cardsdeck)
  - [Assignment operators](#assignment-operators)
    - [`CardsDeck& operator= (const CardsDeck&)`](#cardsdeck-operator-const-cardsdeck)
    - [`CardsDeck& operator= (CardsDeck&&)`](#cardsdeck-operator-cardsdeck)
  - [Indexing operators](#indexing-operators)
    - [`CardT& operator[] (const IndexType index)`](#cardt-operator-const-indextype-index)
    - [`const CardT& operator[] (const IndexType index) const`](#const-cardt-operator-const-indextype-index-const)
  - [Other operator(s)](#other-operators)
    - [`CardsDeck& operator+= (const CardsDeck& other)`](#cardsdeck-operator-const-cardsdeck-other)
  - [Accessors / Mutators](#accessors--mutators)
    - [`const IndexType get_current_cards_count() const`](#const-indextype-get_current_cards_count-const)
    - [`const IndexType get_max_cards_count() const noexcept`](#const-indextype-get_max_cards_count-const-noexcept)
    - [`CardsList<CardT>& deck()`](#cardslistcardt-deck)
    - [`const CardsList<CardT>& deck() const`](#const-cardslistcardt-deck-const)
  - [Operations](#operations)
    - [`virtual const bool allowed_card (const CardT& card) const noexcept`](#virtual-const-bool-allowed_card-const-cardt-card-const-noexcept)
    - [`virtual const bool append_card (const CardT& card)`](#virtual-const-bool-append_card-const-cardt-card)
    - [`virtual void append_cards(const CardsList<CardT>& cards)`](#virtual-void-append_cardsconst-cardslistcardt-cards)
    - [`void append_deck (const CardsDeck& other)`](#void-append_deck-const-cardsdeck-other)
    - [`inline void clear()`](#inline-void-clear)
    - [`inline virtual const bool contains(const CardT& card)  const`](#inline-virtual-const-bool-containsconst-cardt-card--const)
    - [`inline const bool contains_all()  const`](#inline-const-bool-contains_all--const)
    - [`template<typename... RestT> inline const bool contains_all(const CardT& first, const RestT&... rest)`](#templatetypename-restt-inline-const-bool-contains_allconst-cardt-first-const-restt-rest)
    - [`const inline bool contains_all(const CardsList<CardT>& cards) const`](#const-inline-bool-contains_allconst-cardslistcardt-cards-const)
    - [`inline const bool contains_any()  const`](#inline-const-bool-contains_any--const)
    - [`template<typename... RestT> inline const bool contains_any(const CardT& first, const RestT&... rest)`](#templatetypename-restt-inline-const-bool-contains_anyconst-cardt-first-const-restt-rest)
    - [`const bool contains_any(const CardsList<CardT>& cards) const`](#const-bool-contains_anyconst-cardslistcardt-cards-const)
    - [`virtual inline void draw_back_image(const int x, const int y)`](#virtual-inline-void-draw_back_imageconst-int-x-const-int-y)
    - [`inline const CardT draw_card()`](#inline-const-cardt-draw_card)
    - [`inline const bool draw_card(const CardT& card)`](#inline-const-bool-draw_cardconst-cardt-card)
    - [`inline const CardsList<CardT> draw_n_cards(const IndexType n)`](#inline-const-cardslistcardt-draw_n_cardsconst-indextype-n)
    - [`inline const CardT draw_nth_card(const IndexType index)`](#inline-const-cardt-draw_nth_cardconst-indextype-index)
    - [`inline const CardT draw_rand_card()`](#inline-const-cardt-draw_rand_card)
    - [`const IndexType get_index(const CardT& card) const`](#const-indextype-get_indexconst-cardt-card-const)
    - [`virtual const bool insert_card(const CardT& card)`](#virtual-const-bool-insert_cardconst-cardt-card)
    - [`inline void insert_cards()`](#inline-void-insert_cards)
    - [`template<typename... RestT> void insert_cards(const CardT& first, const RestT&... rest)`](#templatetypename-restt-void-insert_cardsconst-cardt-first-const-restt-rest)
    - [`virtual void insert_cards(const CardsList<CardT>& cards)`](#virtual-void-insert_cardsconst-cardslistcardt-cards)
    - [`virtual const bool insert_nth_card(const IndexType index, const CardT& card)`](#virtual-const-bool-insert_nth_cardconst-indextype-index-const-cardt-card)
    - [`void insert_nth_cards(const IndexType index)`](#void-insert_nth_cardsconst-indextype-index)
    - [`template<typename... RestT> void insert_nth_cards(const IndexType index, const CardT& first, const RestT&... rest)`](#templatetypename-restt-void-insert_nth_cardsconst-indextype-index-const-cardt-first-const-restt-rest)
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
    - [`inline virtual void refill_deck()`](#inline-virtual-void-refill_deck)
    - [`void refill_deck(const CardsList<CardT>& filling_deck)`](#void-refill_deckconst-cardslistcardt-filling_deck)
    - [`template<typename... RestT> void refill_deck(const CardT& first, const RestT&... rest)`](#templatetypename-restt-void-refill_deckconst-cardt-first-const-restt-rest)
    - [`void shuffle()`](#void-shuffle)
    - [`void shuffle(const IndexType low, const IndexType high)`](#void-shuffleconst-indextype-low-const-indextype-high)
  - [Notes](#notes)
    - [note 1](#note-1)


# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::cards::CardsDeck<>` and of the other declarations and definitions set in header file `include/pltr/playing_cards/cards_deck.h`..


---

# class type `CardsList<>`
This type is used at many places within PlayTore code. It defines lists of playing cards and is declared as a template:
```
template<typename CardT>
using CardsList = std::vector<CardT>;
```
The `CardT` template argument should be of type or inherit from type `pltr::cards::PlayingCardT<>`. This condition is not checked at compilation time. It is your responsability to ensure it - well, you may use also `CardsList` to contain anything else if this fits your needs, but you should not.

The `PRNGT` template argument describes a type that must conform with 


---

# class `CardsDeck<>`
Defined in file `include/pltr/playing_cards/cards_deck.h`.

`CardsDeck<>` is the base class for all decks that contain playing cards and is defined as a template:

```
template<typename CardT, typename PRNGT = pltr::core::Random<>>
    requires std::is_base_of_v<pltr::core::BaseRandom, PRNGT>
class CardsDeck : pltr::core::Object
 ```

This class inherits from `pltr::core::Object`.

The template arguments are:
- `CardT`:  
the type of playing cards that are contained in this type of deck. It gets no default value.
- `PRNGT`:  
the type of the pseudo random numbers generator that is used to shuffle the deck, to draw a random card from deck, or to insert cards at random position in deck. It defaults to `std::mt19337_64`, the STL Mersenne Twister 64 bits algorithm. See [https://en.cppreference.com/w/cpp/numeric/random](https://en.cppreference.com/w/cpp/numeric/random) to get an overview of all the random number generators that are predefined in the STL (since c++11).  
Notice: external library **CppRandLib** will eventually be used at some time in place of the STL `<random>` package. Actually, this is not the case.


## Types Wrappers
```
using CardType = CardT;
using IndexType = std::uint32_t;
```
Notice: indexes are used to index cards in the deck.

## Attributes
Cards deck have next attributes, two of them being **private** with accessors/mutators provided for one or the other:
- `back_image_path`:
of type `std::filesystem::path`. *public*
This is the file path to the image of the back of this deck of cards. May be specified at construction time or either directly set. Aims at being used when displaying this deck in graphical environment with card faces down.
- `_deck`:  
of type `CardsList<CardT>`. *private*  
This is the internal storage of the list of cards that are contained in this deck. It may be accessed outside this class via accessor/mutator `deck()`.
- `_max_cards_count`:  
of type `IndexType`. *private*  
This is an internal control on the max count of cards that can be actually contained within this deck. This value may evolve along the running of your application.


## Constructors / Destructor

### `CardsDeck ()`
The empty constructor.  
`_deck` attribute is set as an empty list, `_max_cards_count` is set to 0, and the class random generation attributes are set if this is the very first instantiation of this class within your application. 

### `CardsDeck (const IndexType max_cards_count)`  
The constructor with size argument.  
`_deck` attribute is set as a list of cards of reserved length `max_cards_count` and is filled according to method `refill_deck()` - notice: this method does nothing in this base class and may (should) be overridden in inheriting classes. Attribute `_max_cards_count` is set to the specified size `max_cards_count`, and the class random generation attributes are set if this is the very first instantiation of this class within your application. 

### `CardsDeck(const CardsList<CardT>& cards)`  
The constructor with initialization vector.  
Attribute `deck` is set as a copy of the specified list of cards (first card at bottom of deck, last card at top of deck), attribute `max_cards_count` is set to the count of cards in list, and the class random generation attributes are set if this is the very first instantiation of this class within your application.

### `CardsDeck (const CardsList<CardT>& cards, std::filesystem::path& back_image_path_)`
The constructor with initialization vector and file path to back image.  
Attribute `deck` is set as a copy of the specified list of cards (first card at bottom of deck, last card at top of deck), attribute `max_cards_count` is set to the count of cards in list, and the class random generation attributes are set if this is the very first instantiation of this class within your application.  
Attribute `back_image_path` is set with a copy of parameter `back_image_path_`.

### `template<typename... NextCardsT> CardsDeck (const IndexType max_cards_count, const CardT& first_card, const NextCardsT&... next_cards)`  
The constructor with an initialization list.  
According to this signature of constructor, you can pass a list of cards as parameters. Attribute `deck` is set as containing the specified list of cards (first card at bottom of deck, last card at top of deck), attribute `max_cards_count` is set to the count of cards in parameters list, and the class random generation attributes are set if this is the very first instantiation of this class within your application. It can be accessed via the not mutable accessor method `get_max_cards_count()`.

### `template<typename... NextCardsT> CardsDeck (const IndexType max_cards_count, const std::filesystem::path& back_image_path_, const CardT& first_card, const NextCardsT&... next_cards)`
The constructor with initialization list and file path to back image.  
According to this signature of constructor, you can pass a list of cards as parameters. Attribute `deck` is set as containing the specified list of cards (first card at bottom of deck, last card at top of deck), attribute `max_cards_count` is set to the count of cards in parameters list, and the class random generation attributes are set if this is the very first instantiation of this class within your application. It can be accessed via the not mutable accessor method `get_max_cards_count()`.  
Attribute `back_image_path` is set with a copy of parameter `back_image_path_`.

### `CardsDeck(const CardsDeck&)`  
The default copy constructor.

### `CardsDeck(CardsDeck&&)`  
The default move constructor.

### `virtual ~CardsDeck()`  
The default destructor.


## Assignment operators

### `CardsDeck& operator= (const CardsDeck&)`
Default copy operator.

### `CardsDeck& operator= (CardsDeck&&)`
Default move operator.


## Indexing operators

### `CardT& operator[] (const IndexType index)`  
Mutable indexing operator. May throw exception on bad index.

### `const CardT& operator[] (const IndexType index) const`  
Not mutable indexing const operator. May throw exception on bad index.


## Other operator(s)

### `CardsDeck& operator+= (const CardsDeck& other)`
Appends an other deck at end of this deck.


## Accessors / Mutators

### `const IndexType get_current_cards_count() const`  
Returns the count of cards currently contained in this deck. Not mutable.

### `const IndexType get_max_cards_count() const noexcept`  
Returns the max count of cards that can be contained in this deck. Not mutable.

### `CardsList<CardT>& deck()`  
Accessor to private deck content, mutable. To be used cautiously when modifying the content of the deck. Changing its content with a content with more cards than current `max_cards_count` value.

### `const CardsList<CardT>& deck() const`  
Accessor to private deck content, not mutable: no modifications are allowed, so safe to be used for reading any data in it.


## Operations

### `virtual const bool allowed_card (const CardT& card) const noexcept`  
Returns true if the specified card is allowed to be contained in this deck.

### `virtual const bool append_card (const CardT& card)`  
Appends a card at bottom of this deck. Deck max capacity may grow up then. See `insert_card()`.

### `virtual void append_cards(const CardsList<CardT>& cards)`  
Appends a list of cards at bottom of this deck. Cards are appended in their order in the passed list of cards. Deck max capacity may grow up then.

### `void append_deck (const CardsDeck& other)`
Appends an other deck at end of this deck.

### `inline void clear()`  
Empties the content of this deck. The value of `_max_cards_count` is not modified.

### `inline virtual const bool contains(const CardT& card)  const`  
Returns true if the card ident is found in this deck.

### `inline const bool contains_all()  const`  
This is the end of the containment searching recursion in this deck of all listed cards. Should not be called by library user - always return true.

### `template<typename... RestT> inline const bool contains_all(const CardT& first, const RestT&... rest)`  
Returns true if all cards in list are contained in this deck.

### `const inline bool contains_all(const CardsList<CardT>& cards) const`  
Returns true if all of the passed cards are contained in this deck.

### `inline const bool contains_any()  const`  
This is the end of the containment searching recursion in this deck of any listed card. Should not be called by library user - always return false.

### `template<typename... RestT> inline const bool contains_any(const CardT& first, const RestT&... rest)` 
Returns true if any card in list is contained in this deck.

### `const bool contains_any(const CardsList<CardT>& cards) const`  
Returns true if any of the passed cards is contained in this deck.

### `virtual inline void draw_back_image(const int x, const int y)`
Draws the back image of this deck at position (x, y) on display.  
The `x` and `y` coordinates may follow any convention at your wish (e.g. top-left as well as bottom-left corner of card).  
Notice: does nothing in this base class; to be overridden in inheriting classes if this gets meaning.

### `inline const CardT draw_card()`  
Wrapper to `pop_up_card()`: removes and returns the card at the top of this deck.

### `inline const bool draw_card(const CardT& card)`  
If present in deck, removes the card and returns true; returns false else.

### `inline const CardsList<CardT> draw_n_cards(const IndexType n)`  
Wrapper to `pop_up_n_cards()`: removes and returns `n` cards at the top of this deck. May return less than `n` cards if n > current deck size.

### `inline const CardT draw_nth_card(const IndexType index)`  
Wrapper to `pop_indexed_card()`: removes and returns the card at `index` position in this deck.  

### `inline const CardT draw_rand_card()`  
Wrapper to `pop_rand_card()`: removes and returns a card at random position in this deck. (see note 1)

### `const IndexType get_index(const CardT& card) const`  
Returns the index of this card in deck if found, or `-1` if not found.

### `virtual const bool insert_card(const CardT& card)`  
Inserts a card at top of this deck. Deck max capacity may grow up then. \see append_card().

### `inline void insert_cards()`  
This is the end of inserts recursion of cards in this deck. Should not be called by library user - does nothing.

### `template<typename... RestT> void insert_cards(const CardT& first, const RestT&... rest)`  
Inserts a list of cards in this deck at top of deck.

### `virtual void insert_cards(const CardsList<CardT>& cards)`  
Inserts `n` cards at top of this deck. Deck max capacity may grow up then.

### `virtual const bool insert_nth_card(const IndexType index, const CardT& card)`  
Inserts a card at n-th position in this deck. Deck max capacity may grow up then.

### `void insert_nth_cards(const IndexType index)`  
This is the end of inserts recursion of cards at some position in this deck. Should not be called by library user - does nothing.

### `template<typename... RestT> void insert_nth_cards(const IndexType index, const CardT& first, const RestT&... rest)`  
Inserts a list of cards in this deck.

### `virtual void insert_nth_cards(const IndexType index, const CardsList<CardT>& cards)`  
Inserts a list of cards at `index` position in this deck. Deck max capacity may grow up then.

### `virtual const bool insert_rand_card(const CardT& card)`  
Inserts a card at a random position in this deck. Deck max capacity may grow up then. (see note 1)

### `inline const bool is_empty() const noexcept`  
Returns true when this deck is empty.

### `inline const bool is_full() const noexcept`  
Returns true when this deck is full.

### `const CardT pop_bottom_card()`  
Removes and returns the card at the bottom of this deck. May be considered as an optimized wrapper to `pop_card(_current_cards_count - 1)`.

### `const CardsList<CardT> pop_bottom_n_cards(const IndexType n)`  
Removes and returns n cards from the bottom of this deck. May return less than n cards if n > current deck size.

### `const CardT pop_indexed_card(const IndexType index)`  
Removes and returns the card at `index` in this deck. calls `pop_bottom_card()` if `index` > current deck size.

### `const CardT pop_rand_card()`  
Removes and returns a card at random position from this deck. (see note 1)

### `const CardT pop_up_card()`  
Removes and returns the card at the top of this deck. May be considered as an optimized wrapper to `pop_indexed_card(0)`.

### `const CardsList<CardT> pop_up_n_cards(const IndexType n)`  
Removes and returns `n` cards from top of this deck. May return less than `n` cards if `n` > current deck size.

### `inline virtual void refill_deck()`  
Fills this deck with all related playing cards. Does nothing in this base class, must be overridden in inheriting classes.

### `void refill_deck(const CardsList<CardT>& filling_deck)`  
Fills this deck according to a filling vector. Empties the deck first.

### `template<typename... RestT> void refill_deck(const CardT& first, const RestT&... rest)`  
Fills this deck according to a variable length list of cards. Empties the deck first.

### `void shuffle()`  
Shuffles this whole deck. (see note 1)

### `void shuffle(const IndexType low, const IndexType high)`  
Shuffles some part of this deck. Automaticcaly clips indexes to the min and max values for this deck. (see note 1)


## Notes

### note 1
Class `pltr::cards::CardsDeck<>` uses internally and per default the (not-thread safe) **PlayTore** core class `pltr::core::Random`, defined in header file `pltr/core/random.h`. The curious reader will take benefit from looking at the implemented code of private method `CardsDeck<>::_get_random_index(const IndexType max_index)`.

---
