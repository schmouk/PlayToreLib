# `standard_cards_doc.md` - intro

This file documents the implementation of the class of standard playing cards: `pltr::cards::StandardCards<>`. This class is defined within namespace `pltr::cards`.

The related header file is `include/pltr/playing_cards/standard_cards.h`.

Standard cards are the one that are used for playing Poker, for instance, plus both red and black jokers.


## `standard_cards.h` header file - table of content <!-- omit in toc -->
- [`standard_cards_doc.md` - intro](#standard_cards_docmd---intro)
- [enum class `EColor` : std::uint8\_t](#enum-class-ecolor--stduint8_t)
- [Exception(s)](#exceptions)
  - [`struct StandardInvalidIdent : public std::exception`](#struct-standardinvalidident--public-stdexception)
- [class `StandardCard<>`](#class-standardcard)
  - [Types Wrappers](#types-wrappers)
  - [Constants](#constants)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`StandardCard()`](#standardcard)
    - [`StandardCard(const IdentT ident_)`](#standardcardconst-identt-ident_)
    - [`StandardCard(const IdentT ident_, const ValueT value_)`](#standardcardconst-identt-ident_-const-valuet-value_)
    - [`StandardCard(const IdentT ident_, const std::filesystem::path& image_path_)`](#standardcardconst-identt-ident_-const-stdfilesystempath-image_path_)
    - [`StandardCard(const IdentT ident_, const ValueT value_, const ValueT ordering_value_)`](#standardcardconst-identt-ident_-const-valuet-value_-const-valuet-ordering_value_)
    - [`StandardCard(const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_)`](#standardcardconst-identt-ident_-const-valuet-value_-const-stdfilesystempath-image_path_)
    - [`StandardCard(const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_)`](#standardcardconst-identt-ident_-const-valuet-value_-const-valuet-ordering_value_-const-stdfilesystempath-image_path_)
    - [`StandardCard(const StandardCard&)`](#standardcardconst-standardcard)
    - [`StandardCard(StandardCard&&)`](#standardcardstandardcard)
    - [`virtual ~StandardCard()`](#virtual-standardcard)
  - [Assignment operators](#assignment-operators)
    - [`StandardCard& operator= (const StandardCard&)`](#standardcard-operator-const-standardcard)
    - [`StandardCard& operator= (StandardCard&&)`](#standardcard-operator-standardcard)
  - [Comparison operators](#comparison-operators)
    - [`const bool operator< (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const)
    - [`const bool operator> (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-1)
    - [`const bool operator<= (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-2)
    - [`const bool operator>= (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-3)
    - [`const bool operator== (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-4)
    - [`const bool operator!= (const PlayingCardT& other) const`](#const-bool-operator-const-playingcardt-other-const-5)
  - [Operations](#operations)
    - [`const EColor get_color() const`](#const-ecolor-get_color-const)
    - [`const bool is_joker() const`](#const-bool-is_joker-const)
    - [`void set(const IdentT ident_)`](#void-setconst-identt-ident_)
    - [`void set(const IdentT ident_, const ValueT value_)`](#void-setconst-identt-ident_-const-valuet-value_)
    - [`void set(const IdentT ident_, const ValueT value_, const ValueT ordering_value_)`](#void-setconst-identt-ident_-const-valuet-value_-const-valuet-ordering_value_)
    - [`void set(const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_)`](#void-setconst-identt-ident_-const-valuet-value_-const-stdfilesystempath-image_path_)
    - [`void set(const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_)`](#void-setconst-identt-ident_-const-valuet-value_-const-valuet-ordering_value_-const-stdfilesystempath-image_path_)
    - [`void _set_text()`](#void-_set_text)
    - [`virtual const std::string _get_object_name() const noexcept override`](#virtual-const-stdstring-_get_object_name-const-noexcept-override)
- [Template Specializations](#template-specializations)
  - [`using StandardCardDe = StandardCard<"23456789XBDK1J", "RAHP", "RS">`](#using-standardcardde--standardcard23456789xbdk1j-rahp-rs)
  - [`using StandardClassEn = StandardCard<>`](#using-standardclassen--standardcard)
  - [`StandardCardEs = StandardCard<"23456789XJAR1J", "TDCE", "RN">`](#standardcardes--standardcard23456789xjar1j-tdce-rn)
  - [`StandardCardFr = StandardCard<"23456789XVDR1J", "TKCP", "RN">`](#standardcardfr--standardcard23456789xvdr1j-tkcp-rn)
  - [`using StandardCardIt = StandardCard<"23456789XJAR1J", "MQCP", "RN">`](#using-standardcardit--standardcard23456789xjar1j-mqcp-rn)
  - [`using StandardWindowsConsoleCard = StandardCard<"23456789XJQKAJ", "\005\004\003\006", "RB">`](#using-standardwindowsconsolecard--standardcard23456789xjqkaj-005004003006-rb)
  - [`using StandardWindowsConsoleCardDe = StandardCard<"23456789XBDK1J", "\005\004\003\006", "RS">`](#using-standardwindowsconsolecardde--standardcard23456789xbdk1j-005004003006-rs)
  - [`using StandardWindowsConsoleClassEn = StandardWindowsConsoleCard`](#using-standardwindowsconsoleclassen--standardwindowsconsolecard)
  - [`using StandardWindowsConsoleCardEs = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN">`](#using-standardwindowsconsolecardes--standardcard23456789xjar1j-005004003006-rn)
  - [`using StandardWindowsConsoleCardFr = StandardCard<"23456789XVDR1J", "\005\004\003\006", "RN">`](#using-standardwindowsconsolecardfr--standardcard23456789xvdr1j-005004003006-rn)
  - [`using StandardWindowsConsoleCardIt = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN">`](#using-standardwindowsconsolecardit--standardcard23456789xjar1j-005004003006-rn)
- [Type traits](#type-traits)
  - [`template<typename T> struct is_standard_card`](#templatetypename-t-struct-is_standard_card)
  - [\`template inline constexpr bool is\_standard\_card\_v = is\_standard\_card::value](#template-inline-constexpr-bool-is_standard_card_v--is_standard_cardvalue)


# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::cards::StandardCard<>`.


# enum class `EColor` : std::uint8_t
Defined in file `include/pltr/playing_cards/standard_cards.h`.  
The standard colors for standard playing cards. These are named (in their ordered declaration): `E_CLUB`, `E_DIAMOND`, `E_HEART`, `E_SPADE`, `E_RED` and `E_BLACK`.


# Exception(s)

## `struct StandardInvalidIdent : public std::exception`
The StandardInvalidIdent exception for standard cards. Raised every time an ident value (used for the setting of standard cards identifiers) is out of bounds [0, 53]. Method `what()` returns an `std::string` which contains a message error that shows the invalid indentifier.


# class `StandardCard<>`
Defined in file `include/pltr/playing_cards/standard_cards.h`.

`StandardCard<>` is the base class for all standard playing cards and is defined as a template:

```
template<
    const pltr::core::StringTemplateParameter _CARDS_LETTERS = "23456789XJQKAJ",
    const pltr::core::StringTemplateParameter _COLORS_LETTERS = "CDHS",
    const pltr::core::StringTemplateParameter _JOKERS_COLORS = "RB",
    const std::uint32_t _START_VALUE = 2
>
class StandardCard : public pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>
 ```

The template arguments are:
- `_CARDS_LETTERS`:  
the letters associated with each valued card, in their ascending order (i.e. from 2 to Ace) plus the letter associated with Jokers at upper rank. Defaults to the English names of cards: `"23456789XJQKAJ"`;
- `_COLORS_LETTERS`:  
the letters associated with each color of cards, in their ascending order according to Bridge convention . Defaults to the English names of card colors: `"CDHS"` for Club; Diamond, Heart and Spade;
- `_JOKERS_COLORS`:  
the letters associated with each color of jokers, red first, black then. Defaults to the English names of card colors: `"RB"`;
- `_START_VALUE`:  
the starting value to be associated with cards. Defaults to the `2` as associated with cards "2". Value is then increased per one: `3` for cards "3", ..., `10` for cards "10", `11` for cards "Jack", ..., `14` for Aces and `15` for Jokers.

This class inherits from `pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>`. As such, it inherits also from `pltr::core::Object`.

## Types Wrappers
```
    using MyBaseClass = pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>;
    using IdentT = MyBaseClass::ident_type;
    using ValueT = MyBaseClass::value_type;

    using MyClassType = StandardCard<_CARDS_LETTERS, _COLORS_LETTERS, _JOKERS_COLORS>;
```

## Constants
to be accessible outside of the class.
```
    static inline constexpr ValueT START_VALUE{ _START_VALUE };
    
    static inline constexpr IdentT CARDS_PER_COLOR{ 13 };
    static inline constexpr IdentT COLORS_COUNT{ 4 };

    static inline constexpr IdentT JOKERS_FIRST_IDENT{ COLORS_COUNT * CARDS_PER_COLOR };
    static inline constexpr IdentT JOKERS_INDEX{ CARDS_PER_COLOR };

```

## Attributes
Standard cards have next attributes, all of them being inherited from base class `pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>`:
- `ident` :  
of type `IdentT`.  
The identifier of this card. Must be contained in intervall [0, 53];
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

### `StandardCard()`
The empty constructor.  
Attribute `ident` is set to `0`, Attributes `value` and `ordering value` are set to template constant `_START_VALUE`. Attribute `image_path` is left empty. Attribute `text` is set to the two letters that define the 2 of Club.

### `StandardCard(const IdentT ident_)`
1-valued constructor.  
Attribute `ident` is set to `ident_`, Attributes `value` and `ordering value` are set to  `ident / 4 + _START_VALUE`. Attribute `image_path` is left empty. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `StandardCard(const IdentT ident_, const ValueT value_)`
2-valued constructor (1/2).  
Attribute `ident` is set to `ident_`, Attributes `value` and `ordering value` are set to  `value_`. Attribute `image_path` is left empty. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `StandardCard(const IdentT ident_, const std::filesystem::path& image_path_)`
2-valued constructor (2/2).  
Attribute `ident` is set to `ident_`, Attributes `value` and `ordering value` are set to  `ident / 4 + _START_VALUE`. Attribute `image_path` is set to the passed argument `image_path_`. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `StandardCard(const IdentT ident_, const ValueT value_, const ValueT ordering_value_)`
3-valued constructor (1/2).  
Attribute `ident` is set to `ident_`, Attribute `value` is set to `value_`. Attribute `ordering value` is set to  `ordering_value_`. Attribute `image_path` is left empty. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `StandardCard(const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_)`
3-valued constructor (2/2).
Attribute `ident` is set to `ident_`, Attributes `value` and `ordering value` are set to  `value_`. Attribute `image_path` is set to the passed argument `image_path_`. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `StandardCard(const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_)`
4-valued constructor.
Attribute `ident` is set to `ident_`, Attribute `value` is set to `value_`. Attribute `ordering value` is set to  `ordering_value_`. Attribute `image_path` is set to the passed argument `image_path_`. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `StandardCard(const StandardCard&)`
The default copy constructor.

### `StandardCard(StandardCard&&)`
The default move constructor.

### `virtual ~StandardCard()`
The default destructor.


## Assignment operators

### `StandardCard& operator= (const StandardCard&)`
The default copy operator.

### `StandardCard& operator= (StandardCard&&)`
The default move operator.


## Comparison operators

All these comparison operators are inherited from base class `pltr::cards::PlayingCardT<std::uint8_t, std::uint32_t>`

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

### `const EColor get_color() const`
Returns the enum color of this card. Returns `Ecolor::E_RED` for red Joker (ident 52), `EColor::E_BLACK` for black Joker (ident 53), or `Ecolor(card.ident % 4)` for any other card.

### `const bool is_joker() const`
Returns true if this card is a Joker one.

### `void set(const IdentT ident_)`
Sets data - 1 arg.  
Attribute `ident` is set to `ident_`, Attributes `value` and `ordering value` are set to  `ident / 4 + _START_VALUE`. Attribute `image_path` is left empty. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `void set(const IdentT ident_, const ValueT value_)`
Sets data - 2 args.  
Attribute `ident` is set to `ident_`, Attributes `value` and `ordering value` are set to  `value_`. Attribute `image_path` is left empty. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `void set(const IdentT ident_, const ValueT value_, const ValueT ordering_value_)`
Sets data (3 args, 1/2).  
Attribute `ident` is set to `ident_`, Attribute `value` is set to `value_`. Attribute `ordering value` is set to  `ordering_value_`. Attribute `image_path` is left empty. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `void set(const IdentT ident_, const ValueT value_, const std::filesystem::path& image_path_)`
Sets data (3 args, 2/2).
Attribute `ident` is set to `ident_`, Attributes `value` and `ordering value` are set to  `value_`. Attribute `image_path` is set to the passed argument `image_path_`. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `void set(const IdentT ident_, const ValueT value_, const ValueT ordering_value_, const std::filesystem::path& image_path_)`
Sets data (4 args).
Attribute `ident` is set to `ident_`, Attribute `value` is set to `value_`. Attribute `ordering value` is set to  `ordering_value_`. Attribute `image_path` is set to the passed argument `image_path_`. Attribute `text` is set to the two letters that define the card and its color (see protected method `_set_text()` for the choosen letter for the color).

### `void _set_text()`
Protected method. Internally sets the text of this card according to its known `ident`: the letter associated with this card face is set to `_CARDS_LETTERS[this->ident / COLORS_COUNT]`; the letter associated to its color relates to the returned value of method `get_color()`.  
Notice: the attributes of base class `pltr::core::Object` are set also with class name `StandardCard<>` and with attribute `text` content as the instance name.

### `virtual const std::string _get_object_name() const noexcept override`
Protected method. Returns the name of the object.  
As inherited from base class `PlayingCardT<>`, just returns the value of attribute `text`. This protected method is overridden from the inherited class `pltr::core::Object` and is internally called by method `pltr::core::Object::repr()` to provide a log string related to this playing card instance.


# Template Specializations
Defined in file `include/pltr/playing_cards/standard_cards.h`.

A few specialization are provided for help. They each relate to a localization specialization.

## `using StandardCardDe = StandardCard<"23456789XBDK1J", "RAHP", "RS">`
German specialization. Notice: RAHP für kReuz, kAro, Herz, Pik

## `using StandardClassEn = StandardCard<>`
English specialization. Notice: same as generic template,  that's all!

## `StandardCardEs = StandardCard<"23456789XJAR1J", "TDCE", "RN">`
Spanish specialization. Notice: JARJ para Jota, reinA, Rey, Joker ; TDCE para Tréboles, Diamantes; Corazón, Espadas.

## `StandardCardFr = StandardCard<"23456789XVDR1J", "TKCP", "RN">`
French specialization. Notice: TKCP pour Trèfle, (K)arreau, Coeur, Pique.

## `using StandardCardIt = StandardCard<"23456789XJAR1J", "MQCP", "RN">`
Italian specialization. Notice: JARJ per Jack, reginA, Re, Joker ; MQCP per Mazze, Quadri, Cuore, Picche.

## `using StandardWindowsConsoleCard = StandardCard<"23456789XJQKAJ", "\005\004\003\006", "RB">`
Specialization with Windows Console characters for resp. Club, Diamond, Heart and Spike. Defaults to English facet and color letters.

## `using StandardWindowsConsoleCardDe = StandardCard<"23456789XBDK1J", "\005\004\003\006", "RS">`
German specialization with Windows Console characters for resp. Club, Diamond, Heart and Spike.

## `using StandardWindowsConsoleClassEn = StandardWindowsConsoleCard`
English specialization with Windows Console characters for resp. Club, Diamond, Heart and Spike.

## `using StandardWindowsConsoleCardEs = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN">`
Spanish specialization with Windows Console characters for resp. Club, Diamond, Heart and Spike.

## `using StandardWindowsConsoleCardFr = StandardCard<"23456789XVDR1J", "\005\004\003\006", "RN">`
French specialization with Windows Console characters for resp. Club, Diamond, Heart and Spike.

## `using StandardWindowsConsoleCardIt = StandardCard<"23456789XJAR1J", "\005\004\003\006", "RN">`
Italian specialization with Windows Console characters for resp. Club, Diamond, Heart and Spike.


# Type traits
Defined in file `include/pltr/playing_cards/standard_cards.h`.

## `template<typename T> struct is_standard_card`
This *UnaryTypeTrait* checks whether type `T` is a `StandardCard` type.  
It provides the member contant value `value` which is equal to `true` if `T` is of `StandardCard` type or `false` otherwise. Notice: returns true for all template specializations defined in here.

## `template<typename T> inline constexpr bool is_standard_card_v = is_standard_card<T>::value
This is the related helper variable template. It provides direct access to the value of the above *UnaryTypeTrait* checker.
