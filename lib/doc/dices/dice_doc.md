# `dice_doc.md` - intro

This file documents the implementation of the base class for all types of dices: `pltr::dices::Dice<>`.  
This class is defined within namespace `pltr::dices`.

The related header file is [`include/pltr/dices/dice.h`](../../include/pltr/dices/dice.h).

It defines what are dices and what are the actions that can be applied to them.


## `dice.h` header file - table of content <!-- omit in toc -->
- [`dice_doc.md` - intro](#dice_docmd---intro)
- [class `Dice<>`](#class-dice)
  - [Types Wrappers](#types-wrappers)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`Dice () noexcept`](#dice--noexcept)
    - [`Dice(const std::vector<FaceT>& faces)`](#diceconst-stdvectorfacet-faces)
    - [`template<typename... RestT> Dice(const FaceT& first, const RestT&... rest)`](#templatetypename-restt-diceconst-facet-first-const-restt-rest)
    - [`Dice(const Dice&) noexcept`](#diceconst-dice-noexcept)
    - [`Dice(Dice&&) noexcept`](#dicedice-noexcept)
    - [`virtual ~Dice ()`](#virtual-dice-)
  - [Assignment operators](#assignment-operators)
    - [`Dice& operator= (const Dice&)`](#dice-operator-const-dice)
    - [`Dice& operator= (Dice&&)`](#dice-operator-dice)
  - [Indexing operator](#indexing-operator)
    - [`ValueType& operator[] (const std::uint32_t num_face)`](#valuetype-operator-const-stduint32_t-num_face)
  - [Comparison operators](#comparison-operators)
    - [`const bool operator< (const Dice& other) const`](#const-bool-operator-const-dice-other-const)
    - [`const bool operator> (const Dice& other) const`](#const-bool-operator-const-dice-other-const-1)
    - [`const bool operator<= (const Dice& other) const`](#const-bool-operator-const-dice-other-const-2)
    - [`const bool operator>= (const Dice& other) const`](#const-bool-operator-const-dice-other-const-3)
    - [`const bool operator== (const Dice& other) const`](#const-bool-operator-const-dice-other-const-4)
    - [`const bool operator!= (const Dice& other) const`](#const-bool-operator-const-dice-other-const-5)
  - [Accessors / Mutators](#accessors--mutators)
    - [`const std::uint32_t faces_count() const noexcept`](#const-stduint32_t-faces_count-const-noexcept)
    - [`const FaceT& force_upper_face(const std::uint32_t num_face)`](#const-facet-force_upper_faceconst-stduint32_t-num_face)
    - [`const float get_last_rotation_angle() const noexcept`](#const-float-get_last_rotation_angle-const-noexcept)
    - [`const FaceT& get_upper_face() const noexcept`](#const-facet-get_upper_face-const-noexcept)
  - [Operations](#operations)
    - [`const FaceT& roll()`](#const-facet-roll)
    - [`const FaceT& roll_with_angle()`](#const-facet-roll_with_angle)
    - [`const FaceT& roll_with_angle(float& angle)`](#const-facet-roll_with_anglefloat-angle)
    - [`void set(const std::vector<FaceT>& faces)`](#void-setconst-stdvectorfacet-faces)



# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::dices::Dice<>`.


---

# class `Dice<>`
Defined in file [`include/pltr/dices/dice.h`](../../include/pltr/dices/dice.h).

`Dice<>` is the base class for all dices and is defined as a template:

```
template<
    typename FaceT = pltr::dices::Face<>,
    typename PRNGT = std::mt19937_64
>
class Dice : public pltr::core::Object
 ```

The template arguments are:
- `FaceT`:  
the type of faces that compose this dice. Defaults to [`pltr::dices::Face<>`](./face_doc.md);
- `PRNGT`:  
the type of the pseudo random numbers generators to be used when generating randomness. Defaults to the STL generator `std::mt19937_64` 64 bits Mersenne Twister algorithm.  
Notice: **PlayTore** will eventually use the open source library **CppRandLib** for the generation of randomness. Other PRNGs will then be available. This is not currently the case.

This class inherits from [`pltr::core::Object`](../core/object_doc.md).  
It is defined within namespace `pltr::dices`.

## Types Wrappers
```
using FaceType = FaceT;
using ValueType = typename FaceType::value_type;
```

## Attributes
Class `Dice<>` declares only *private* attributes, some of which can be accessed via accessors and mutators documented in belowing subsections.


## Constructors / Destructor

### `Dice () noexcept`
The default empty constructor.

### `Dice(const std::vector<FaceT>& faces)`
Initialization constructor. Vector `faces` is used to set the faces of this dice. Throws exception if vector size is less than 2.

### `template<typename... RestT> Dice(const FaceT& first, const RestT&... rest)`
Constructor with variable arguments length. Throws exception if size of `rest` is 0.

### `Dice(const Dice&) noexcept`
Default copy constructor.

### `Dice(Dice&&) noexcept`
Default move constructor.

### `virtual ~Dice ()`
Default destructor.


## Assignment operators

### `Dice& operator= (const Dice&)`
Default copy operator.

### `Dice& operator= (Dice&&)`
Default move operator.


## Indexing operator

### `ValueType& operator[] (const std::uint32_t num_face)`
Mutable indexing operator. Face numbers start at 0. Throws exception [`pltr::dices::InvalidFaceIndex`](./dices_exceptions_doc.md) exception if `num_face` is out of range (starts at 0).


## Comparison operators

### `const bool operator< (const Dice& other) const`
less-than operator. Operates on the value of current up-face of the dice.

### `const bool operator> (const Dice& other) const`
greater-than operator. Operates on the value of current up-face of the dice.

### `const bool operator<= (const Dice& other) const`
less-than-or-equal operator. Operates on the value of current up-face of the dice.

### `const bool operator>= (const Dice& other) const`
greater-than-or-equal operator. Operates on the value of current up-face of the dice.

### `const bool operator== (const Dice& other) const`
equality operator. Operates on the value of current up-face of the dice.

### `const bool operator!= (const Dice& other) const`
non-equality operator. Operates on the value of current up-face of the dice.


## Accessors / Mutators

### `const std::uint32_t faces_count() const noexcept`
Returns the number of faces for this dice.

### `const FaceT& force_upper_face(const std::uint32_t num_face)`
Forces the upper face of this dice.  Throws exception [`pltr::dices::InvalidDiceValue`](./dices_exceptions_doc.md) if `num_face` is out of range (starts at 0).

### `const float get_last_rotation_angle() const noexcept`
Returns the rotation angle of the dice got on last roll_with_angle call (degrees, [0.0, 360.0]).

### `const FaceT& get_upper_face() const noexcept`
Returns the current upper face of this dice.


## Operations

### `const FaceT& roll()`
Rolls this dice and returns the new upper face. Throws exception [`pltr::dices::InvalidDice`](./dices_exceptions_doc.md) if dice is not initialized (i.e. instantiated with empty default constructor and not initialized then via method `set()`).

### `const FaceT& roll_with_angle()`
Rolls this dice, returns the new upper face and sets a rotation angle. Throws exception [`pltr::dices::InvalidDice`](./dices_exceptions_doc.md) if dice is not initialized (i.e. instantiated with empty default constructor and not initialized then via method `set()`).  
Notice: the rotation angle may be used as a value of importance in some games (this is the case for Warhammer 40k with some dice). It may also be used to draw the dice on a graphical display.

### `const FaceT& roll_with_angle(float& angle)` 
Rolls this dice, returns the new upper face and gets back a rotation angle. Throws exception [`pltr::dices::InvalidDice`](./dices_exceptions_doc.md) if dice is not initialized (i.e. instantiated with empty default constructor and not initialized then via method `set()`).  
Notice: the rotation angle may be used as a value of importance in some games (this is the case for Warhammer 40k with some dice). It may also be used to draw the dice on a graphical display.

### `void set(const std::vector<FaceT>& faces)`
Sets this dice faces with an initialization vector. Throws exception if less than 2 faces.  
Notice: when a dice has been instantiated with the empty constructor, this method must be called BEFORE calling any rolling method. An exception [`pltr::dices::InvalidDice`](./dices_exceptions_doc.md) is thrown otherwise.

---
