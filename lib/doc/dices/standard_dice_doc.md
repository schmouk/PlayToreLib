# `standard_dice_doc.md` - intro

This file documents the implementation of the base class for all types of dices: `pltr::dices::StandardDice<>`.  
This class is defined within namespace `pltr::dices`.

The related header file is [`include/pltr/dices/standard_dice.h`](../../include/pltr/dices/dice.h).

It defines what are dices and what are the actions that can be applied to them.


## `standard_dice.h` header file - table of content <!-- omit in toc -->
- [`standard_dice_doc.md` - intro](#standard_dice_docmd---intro)
- [class `StandardDice<>`](#class-standarddice)
  - [Types Wrappers](#types-wrappers)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`StandardDice (const std::int32_t faces_count = 6, const ValueT min_value = 1, const ValueT step_value = 1)`](#standarddice-const-stdint32_t-faces_count--6-const-valuet-min_value--1-const-valuet-step_value--1)
    - [`StandardDice(const StandardDice&) noexcept`](#standarddiceconst-standarddice-noexcept)
    - [`StandardDice(StandardDice&&) noexcept`](#standarddicestandarddice-noexcept)
    - [`virtual ~StandardDice ()`](#virtual-standarddice-)
  - [Assignment operators](#assignment-operators)
    - [`StandardDice& operator= (const StandardDice&)`](#standarddice-operator-const-standarddice)
    - [`StandardDice& operator= (StandardDice&&)`](#standarddice-operator-standarddice)
  - [Comparison operators](#comparison-operators)
    - [`const bool operator< (const StandardDice& other) const`](#const-bool-operator-const-standarddice-other-const)
    - [`const bool operator> (const StandardDice& other) const`](#const-bool-operator-const-standarddice-other-const-1)
    - [`const bool operator<= (const StandardDice& other) const`](#const-bool-operator-const-standarddice-other-const-2)
    - [`const bool operator>= (const StandardDice& other) const`](#const-bool-operator-const-standarddice-other-const-3)
    - [`const bool operator== (const StandardDice& other) const`](#const-bool-operator-const-standarddice-other-const-4)
    - [`const bool operator!= (const StandardDice& other) const`](#const-bool-operator-const-standarddice-other-const-5)
  - [Accessors / Mutators](#accessors--mutators)
    - [`const std::int32_t faces_count() const noexcept`](#const-stdint32_t-faces_count-const-noexcept)
    - [`const float get_last_rotation_angle() const noexcept`](#const-float-get_last_rotation_angle-const-noexcept)
  - [Operations](#operations)
    - [`const ValueT& roll() noexcept`](#const-valuet-roll-noexcept)
    - [`const ValueT& roll_with_angle() noexcept`](#const-valuet-roll_with_angle-noexcept)
    - [`const ValueT& roll_with_angle(float& angle) noexcept`](#const-valuet-roll_with_anglefloat-angle-noexcept)



# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::dices::StandardDice<>`.


---

# class `StandardDice<>`
Defined in file [`include/pltr/dices/standard_dice.h`](../../include/pltr/dices/standard_dice.h).

A *standard dice* in **PlayTore** is a dice with faces that contain numbers. A fair example is a 6-faces dice with its faces numbered from 1 to 6.

`StandardDice<>` is the templated class for all standard dices and is defined as a template:

```
template<typename ValueT = std::int32_t, typename PRNGT = std::mt19937_64>
    requires std::is_integral_v<ValueT>
class StandardDice : public pltr::core::Object
 ```

The template arguments are:
- `ValueT`:  
the integral type used for the numbers on the faces of the dice. Defaults to `std::int32_t`;
- `PRNGT`:  
the type of the pseudo random numbers generators to be used when generating randomness. Defaults to the STL generator `std::mt19937_64` 64 bits Mersenne Twister algorithm.  
Notice: **PlayTore** will eventually use the open source library **CppRandLib** for the generation of randomness. Other PRNGs will then be available. This is not currently the case.

This class inherits from [`pltr::core::Object`](../core/object_doc.md).  
It is defined within namespace `pltr::dices`.

Notice: class `StandardDice<>` **does not** inherit from templated class `pltr::dices::Dice<>`. It is a specific class dedicated to standard dices with numbered faces.


## Types Wrappers
```
using ValueType = ValueT;
```

## Attributes
The only public attribute is:
- `value`:  
  of type `ValueT`. This is the value of the upper face of the dice once rolled.

Class `StandardDice<>` declares also *private* attributes, some of which can be accessed via accessors and mutators as documented in belowing subsections.


## Constructors / Destructor

### `StandardDice (const std::int32_t faces_count = 6, const ValueT min_value = 1, const ValueT step_value = 1)`
The constructor with initialization values. `faces_count` must be set to 2 or more: throws exception [`pltr::dices::InvalidDice`]("./dices_exceptions_doc.md) if not.

Parameters are:
- `faces_count`:  
  The number of faces that compose this dice. Must be greater than 1. Defaults to 6, standing for a 6-faces dice.
- `min_value`:  
  The lowest value figuring on the faces of the dice; of type `ValueT`. Defaults to `1` which is the standard value for 6-faces dices.
- `step_value`:  
  the increment value to be added to each next face on the dice; of type `ValueT`. Defaults to `1`which is the standard value for 6-faces dices.

Examples of other traditional dices:
- `StandardDice(10, 1, 1)`  
  a 10-faces dice with faces numbered from `1` to `10`;
- `StandardDice(10, 0, 10)`
  a 10-faces dice with faces numbered from `00` to `90`.


### `StandardDice(const StandardDice&) noexcept`
Default copy constructor.

### `StandardDice(StandardDice&&) noexcept`
Default move constructor.

### `virtual ~StandardDice ()`
Default destructor.


## Assignment operators

### `StandardDice& operator= (const StandardDice&)`
Default copy operator.

### `StandardDice& operator= (StandardDice&&)`
Default move operator.


## Comparison operators

### `const bool operator< (const StandardDice& other) const`
less-than operator. Operates on the value of current up-face of the dice.

### `const bool operator> (const StandardDice& other) const`
greater-than operator. Operates on the value of current up-face of the dice.

### `const bool operator<= (const StandardDice& other) const`
less-than-or-equal operator. Operates on the value of current up-face of the dice.

### `const bool operator>= (const StandardDice& other) const`
greater-than-or-equal operator. Operates on the value of current up-face of the dice.

### `const bool operator== (const StandardDice& other) const`
equality operator. Operates on the value of current up-face of the dice.

### `const bool operator!= (const StandardDice& other) const`
non-equality operator. Operates on the value of current up-face of the dice.


## Accessors / Mutators

### `const std::int32_t faces_count() const noexcept`
Returns the number of faces for this dice. Not mutable.

### `const float get_last_rotation_angle() const noexcept`
Returns the rotation angle of the dice got on last roll_with_angle call (degrees, [0.0, 360.0]). Not mutable.


## Operations

### `const ValueT& roll() noexcept`
Rolls this dice and returns the new upper face value. Attribute `value` contains also this value.

### `const ValueT& roll_with_angle() noexcept`
Rolls this dice, returns the new upper face value and sets a rotation angle. Attribute `value` contains also the upper face value.  
Notice: the rotation angle may be used as a value of importance in some games (this is the case for Warhammer 40k with some dice). It may also be used to draw the dice on a graphical display.

### `const ValueT& roll_with_angle(float& angle) noexcept` 
Rolls this dice, returns the new upper face value and gets back a rotation angle. Attribute `value` contains also the upper face value.  
Notice: the rotation angle may be used as a value of importance in some games (this is the case for Warhammer 40k with some dice). It may also be used to draw the dice on a graphical display.


---
