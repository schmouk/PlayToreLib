# `playing_cards_doc.md` - intro

This file documents the implementation of the base class for all types of playing cards: `pltr::cards::PlayingCardsT<>`. This class is defined within namespace `pltr::cards`.

The related header file is [`include/pltr/playing_cards/playing_cards.h`](../../include/pltr/playing_cards/playing_cards.h).

It defines what are playing cards and what are the actions that can be applied to them.


## `playing_cards.h` header file - table of content <!-- omit in toc -->
- [`playing_cards_doc.md` - intro](#playing_cards_docmd---intro)
- [class `PlayingCardT<>`](#class-playingcardt)
  - [Types Wrappers](#types-wrappers)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`PlayingCardT ()`](#playingcardt-)
    - [`PlayingCardT (const IdentT ident_)`](#playingcardt-const-identt-ident_)
    - [`PlayingCardT (const IdentT ident_,const ValueT value_)`](#playingcardt-const-identt-ident_const-valuet-value_)
    - [`PlayingCardT (const IdentT ident_, const std::filesystem::path& image_path_)`](#playingcardt-const-identt-ident_-const-stdfilesystempath-image_path_)
    - [`PlayingCardT (const IdentT ident_,const std::string& text_)`](#playingcardt-const-identt-ident_const-stdstring-text_)
    - [`PlayingCardT (const IdentT ident_, const ValueT value_,const ValueT ordering_)`](#playingcardt-const-identt-ident_-const-valuet-value_const-valuet-ordering_)
    - [`PlayingCardT (const IdentT ident_, const ValueT value_, const std::string& text_)`](#playingcardt-const-identt-ident_-const-valuet-value_-const-stdstring-text_)
    - [`PlayingCardT (const IdentT ident_, const std::filesystem::path& image_path_, const std::string& text_)`](#playingcardt-const-identt-ident_-const-stdfilesystempath-image_path_-const-stdstring-text_)
    - [`PlayingCardT (const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::filesystem::path& image_path_)`](#playingcardt-const-identt-ident_-const-valuet-value_-const-valuet-ordering_-const-stdfilesystempath-image_path_)
    - [`PlayingCardT (const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::string& text_)`](#playingcardt-const-identt-ident_-const-valuet-value_-const-valuet-ordering_-const-stdstring-text_)
    - [`PlayingCardT (const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_, const std::string& text_)`](#playingcardt-const-identt-ident_-const-valuet-value_-const-stdfilesystempath-image_path_-const-stdstring-text_)
    - [`PlayingCardT (const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::filesystem::path& image_path_, const std::string& text_)`](#playingcardt-const-identt-ident_-const-valuet-value_-const-valuet-ordering_-const-stdfilesystempath-image_path_-const-stdstring-text_)
    - [`PlayingCardT (const PlayingCardT&)`](#playingcardt-const-playingcardt)
    - [`PlayingCardT (PlayingCardT&&)`](#playingcardt-playingcardt)
    - [`virtual ~PlayingCardT ()`](#virtual-playingcardt-)
  - [Assignment operators](#assignment-operators)
    - [`PlayingCardT& operator= (const PlayingCardT&)`](#playingcardt-operator-const-playingcardt)
    - [`PlayingCardT& operator= (PlayingCardT&&)`](#playingcardt-operator-playingcardt)
  - [Comparison operators](#comparison-operators)
    - [`const bool operator< (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const)
    - [`const bool operator> (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-1)
    - [`const bool operator<= (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-2)
    - [`const bool operator>= (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-3)
    - [`const bool operator== (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-4)
    - [`const bool operator!= (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-5)
  - [Operations](#operations)
    - [`void set (const IdentT ident_, const ValueT value_)`](#void-set-const-identt-ident_-const-valuet-value_)
    - [`void set (const IdentT ident_, const ValueT value_, const ValueT ordering_value_)`](#void-set-const-identt-ident_-const-valuet-value_-const-valuet-ordering_value_)
    - [`void set ( const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_)`](#void-set--const-identt-ident_-const-valuet-value_-const-stdfilesystempath-image_path_)
    - [`void set (const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_)`](#void-set-const-identt-ident_-const-valuet-value_-const-valuet-ordering_value_-const-stdfilesystempath-image_path_)
    - [`void set (const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_, const std::string& text_)`](#void-set-const-identt-ident_-const-valuet-value_-const-stdfilesystempath-image_path_-const-stdstring-text_)
    - [`void set (const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_, const std::string& text_)`](#void-set-const-identt-ident_-const-valuet-value_-const-valuet-ordering_value_-const-stdfilesystempath-image_path_-const-stdstring-text_)
    - [`virtual void action ()`](#virtual-void-action-)
    - [`virtual void draw ()`](#virtual-void-draw-)
    - [`protected: virtual const std::string _get_object_name() const noexcept override`](#protected-virtual-const-stdstring-_get_object_name-const-noexcept-override)


# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::cards::PlayingCardT<>`.


---

# class `PlayingCardT<>`
Defined in file [`include/pltr/playing_cards/playing_cards.h`](../../include/pltr/playing_cards/playing_cards.h).

`PlayingCardsT<>` is the base class for all playing cards and is defined as a template:

```
 template<
     typename IdentT = char,
     typename ValueT = std::int32_t
 > struct PlayingCardT
 ```

The template arguments are:
- `IdentT`:  
the type of the identifiers of the cards, defaults to `char`;
- `ValueT`:  
the type of the values of the cards, defaults to unsigned 32-bits integers.

This class inherits from [`pltr::core::Object`](../core/object_doc.md).

## Types Wrappers
```
    using ident_type = IdentT;
    using value_type = ValueT;
```

## Attributes
Playing cards have next attributes:
- `ident` :  
of type `IdentT`.  
The identifier of this card;
- `image_path`:  
of type `std::filesystem::path`.  
The path to the image associated with this card (may be left empty, to be used only when displaying the face of the card on screen);
- `ordering_value`:  
of type `ValueT`.  
Used to sort cards in decks. The higher the ordering value, the topper in deck the card will be placed (defaults to `value` if not specified at construction time);
- `text`:  
of type `std::string`.  
Some text associated with this card (may be left empty if this gets no meaning);
- `value`:  
of type `ValueT`.  
The value associated with this card. The higher the value, the "stronger" the card in game. Used to compare strengths of cards, and used also with some of the defined sorting methods in decks.


## Constructors / Destructor

### `PlayingCardT ()`
The default empty constructor. `ident` attribute gets value 0, as do attributes `value` and `ordering_value`. `image_path` and `text` are left empty.

### `PlayingCardT (const IdentT ident_)`
1-arg contructor. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type). `image_path` and `text` are left empty.

### `PlayingCardT (const IdentT ident_,const ValueT value_)`
2-args constructor with value. Attribute `ordering_value` gets same value as `value`. `image_path` and `text` are left empty.

### `PlayingCardT (const IdentT ident_, const std::filesystem::path& image_path_)`
2-args constructor with image path. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type). `text` is left empty.

### `PlayingCardT (const IdentT ident_,const std::string& text_)`
2-args constructor with text. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type). `image_path` is left empty.

### `PlayingCardT (const IdentT ident_, const ValueT value_,const ValueT ordering_)`
3-args constructor with value and ordering value. `image_path` and `text` are left empty.

### `PlayingCardT (const IdentT ident_, const ValueT value_, const std::string& text_)`
3-args constructor with value and text. Attribute `ordering_value` gets same value as `value`. `image_path` is left empty.

### `PlayingCardT (const IdentT ident_, const std::filesystem::path& image_path_, const std::string& text_)`
3-args constructor with image path and text. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type).

### `PlayingCardT (const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::filesystem::path& image_path_)`
4-args constructor with value, ordering value and image path. Attribute `text` is left empty.

### `PlayingCardT (const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::string& text_)`
4-args constructor with value, ordering value and text. Attribute `image_path` is left empty.

### `PlayingCardT (const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_, const std::string& text_)`
4-args constructor with value, image path and text. Attribute `ordering_value` gets same value as `value`.

### `PlayingCardT (const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::filesystem::path& image_path_, const std::string& text_)`
5-args constructor. Sets all attributes.

### `PlayingCardT (const PlayingCardT&)`
Default copy constructor.

### `PlayingCardT (PlayingCardT&&)`
Default move constructor.

### `virtual ~PlayingCardT ()`
Default destructor.


## Assignment operators

### `PlayingCardT& operator= (const PlayingCardT&)`
Default copy operator.

### `PlayingCardT& operator= (PlayingCardT&&)`
Default move operator.


## Comparison operators

### `const bool operator< (const PlayingCardT& other) const`
less-than operator. Operates on attributes `value`.

### `const bool operator> (const PlayingCardT& other) const`
greater-than operator. Operates on attributes `value`.

### `const bool operator<= (const PlayingCardT& other) const`
less-than-or-equal operator. Operates on attributes `value`.

### `const bool operator>= (const PlayingCardT& other) const`
greater-than-or-equal operator. Operates on attributes `value`.

### `const bool operator== (const PlayingCardT& other) const`
equality operator. Operates on attributes `value`.

### `const bool operator!= (const PlayingCardT& other) const`
non-equality operator. Operates on attributes `value`.


## Operations

### `void set (const IdentT ident_, const ValueT value_)`
Sets attributes `ident` and `value`. Attribute `ordering_value` gets same value as `value`. Attributes `image_path` and `text` are left unchanged.

### `void set (const IdentT ident_, const ValueT value_, const ValueT ordering_value_)`
Sets attributes `ident`, `value` and `ordering_value`. Attributes `image_path` and `text` are left unchanged.

### `void set ( const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_)`
Sets attributes  `ident`, `value` and `image_path`. Attribute `ordering_value` gets same value as `value`. Attribute `text` is left unchanged.

### `void set (const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_)`
Sets attributes  `ident`, `value`, `ordering_value` and `image_path`. Attribute `text` is left unchanged.

### `void set (const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_, const std::string& text_)`
Sets Sets attributes  `ident`, `value`, `image_path` and `text`. Attribute `ordering_value` gets same value as `value.

### `void set (const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_, const std::string& text_)`
Sets all attributes.

### `virtual void action ()` 
Actions to be processed when this card is played.  
Does nothing in this base class. To be overridden in inheriting classes if this gets meaning.

### `virtual void draw ()`
Draws this card (CAUTION: this is a drawing action on screen, not a draw from a deck!).  
Does nothing in this base class. To be overridden in inheriting classes if this gets meaning.

### `protected: virtual const std::string _get_object_name() const noexcept override`
Returns the name of the object.  
In this class, just returns the value of attribute `text`. This protected method is overridden from the inherited class `pltr::core::Object` and is internally called by method `pltr::core::Object::repr()` to provide a log string related to this playing card instance.

---
