# `playing_cards` package - intro

This package is declared and defined in directory `include/pltr/playing_cards.h`.

This package defines what are playing cards, what are some of their specializations, 
what are decks of cards and some of their specialization too.  
It defines also actions that can be applied to them.

All definitions are embedded in namespace `pltr::cards`.

## `playing_cards` package - table of content <!-- omit in toc -->
- [`playing_cards` package - intro](#playing_cards-package---intro)
- [list of header files](#list-of-header-files)
- [Package documentation](#package-documentation)
  - [class `PlayingCardT<>`](#class-playingcardt)
    - [Attributes](#attributes)
    - [Constructors / Destructor](#constructors--destructor)
      - [PlayingCardT()](#playingcardt)
      - [PlayingCardT(const IdentT ident\_)](#playingcardtconst-identt-ident_)
      - [PlayingCardT(const IdentT ident\_,const ValueT value\_)](#playingcardtconst-identt-ident_const-valuet-value_)
      - [PlayingCardT(const IdentT ident\_, const std::filesystem::path\& image\_path\_)](#playingcardtconst-identt-ident_-const-stdfilesystempath-image_path_)
      - [PlayingCardT(const IdentT ident\_,const std::string\& text\_)](#playingcardtconst-identt-ident_const-stdstring-text_)
      - [PlayingCardT(const IdentT ident\_, const ValueT value\_,const ValueT ordering\_)](#playingcardtconst-identt-ident_-const-valuet-value_const-valuet-ordering_)
      - [PlayingCardT(const IdentT ident\_, const ValueT value\_, const std::string\& text\_)](#playingcardtconst-identt-ident_-const-valuet-value_-const-stdstring-text_)
      - [PlayingCardT(const IdentT ident\_, const std::filesystem::path\& image\_path\_, const std::string\& text\_)](#playingcardtconst-identt-ident_-const-stdfilesystempath-image_path_-const-stdstring-text_)
      - [PlayingCardT(const IdentT ident\_, const ValueT value\_, const ValueT ordering\_, const std::filesystem::path\& image\_path\_)](#playingcardtconst-identt-ident_-const-valuet-value_-const-valuet-ordering_-const-stdfilesystempath-image_path_)
      - [PlayingCardT(const IdentT ident\_, const ValueT value\_, const ValueT ordering\_, const std::string\& text\_)](#playingcardtconst-identt-ident_-const-valuet-value_-const-valuet-ordering_-const-stdstring-text_)
      - [PlayingCardT(const IdentT ident\_, const ValueT value\_, const std::filesystem::path\& image\_path\_, const std::string\& text\_)](#playingcardtconst-identt-ident_-const-valuet-value_-const-stdfilesystempath-image_path_-const-stdstring-text_)
      - [PlayingCardT(const IdentT ident\_, const ValueT value\_, const ValueT ordering\_, const std::filesystem::path\& image\_path\_, const std::string\& text\_)](#playingcardtconst-identt-ident_-const-valuet-value_-const-valuet-ordering_-const-stdfilesystempath-image_path_-const-stdstring-text_)
      - [PlayingCardT(const PlayingCardT\&)](#playingcardtconst-playingcardt)
      - [PlayingCardT(PlayingCardT\&\&)](#playingcardtplayingcardt)
      - [virtual ~PlayingCardT()](#virtual-playingcardt)


# list of header files

About playing cards:
- `playing_cards.h`
- `standard_cards.h`

About decks of playing cards:
- `cards_deck.h`
- `standard_cards_decks.h`
- `unique_standard_cards_deck.h`


# Package documentation

## class `PlayingCardT<>`
Defined in file `include/pltr/playing_cards/playing_cards.h`.

The `PlayingCardsT` is a base class for playing cards and is defined as a template:

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

This class inherits from `pltr::core::Object`.


### Attributes
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


### Constructors / Destructor

#### PlayingCardT()
The default empty constructor. `ident` attibrute gets value 0, as do attributes `value` and `ordering_value`. `image_path` and `text` are left empty.

#### PlayingCardT(const IdentT ident_)
1-arg contructor. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type). `image_path` and `text` are left empty.

#### PlayingCardT(const IdentT ident_,const ValueT value_)
2-args constructor with value. Attribute `ordering_value` gets same value as `value`. `image_path` and `text` are left empty.

#### PlayingCardT(const IdentT ident_, const std::filesystem::path& image_path_) 
2-args constructor with image path. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type). `text` is left empty.

#### PlayingCardT(const IdentT ident_,const std::string& text_)
2-args constructor with text. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type). `image_path` is left empty.

#### PlayingCardT(const IdentT ident_, const ValueT value_,const ValueT ordering_) 
3-args constructor with value and ordering value. `image_path` and `text` are left empty.

#### PlayingCardT(const IdentT ident_, const ValueT value_, const std::string& text_)
3-args constructor with value and text. Attribute `ordering_value` get same value as `value`. `image_path` is left empty.

#### PlayingCardT(const IdentT ident_, const std::filesystem::path& image_path_, const std::string& text_)
3-args constructor with image path and text. Attributes `value` and `ordering_value` get same value as `ident` (which must be of integral type).

#### PlayingCardT(const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::filesystem::path& image_path_)
4-args constructor with value, ordering value and image path. Attribute `text` is left empty.

#### PlayingCardT(const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::string& text_)
4-args constructor with value, ordering value and text. Attribute `image_path` is left empty.

#### PlayingCardT(const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_, const std::string& text_)
4-args constructor with value, image path and text. Attribute `ordering_value` get same value as `value`.

#### PlayingCardT(const IdentT ident_, const ValueT value_, const ValueT ordering_, const std::filesystem::path& image_path_, const std::string& text_)
5-args constructor. Sets all attributes.

#### PlayingCardT(const PlayingCardT&)
Default copy constructor.

#### PlayingCardT(PlayingCardT&&)
Default move constructor.

#### virtual ~PlayingCardT()
Default destructor.

