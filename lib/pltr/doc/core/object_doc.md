# `object_doc.md` - intro

This file documents the implementation of the base class for all types of objects in library **PlayTore**: `pltr::core::Object`. This class is defined within namespace `pltr::core`.

The related header file is `include/pltr/core/object.h`.

It defines what are playing cards and what are the actions that can be applied to them.


## `object.h` header file - table of content <!-- omit in toc -->
- [`object_doc.md` - intro](#object_docmd---intro)
- [class `Object`](#class-object)
  - [Attributes](#attributes)
  - [Constructors / Destructor](#constructors--destructor)
    - [`Object ()`](#object-)
    - [`Object (const Object&)`](#object-const-object)
    - [`Object (Object&&)`](#object-object)
    - [`virtual ~Object ()`](#virtual-object-)
  - [Assignment operators](#assignment-operators)
    - [`Object& operator= (const Object&)`](#object-operator-const-object)
    - [`Object& operator= (Object&&)`](#object-operator-object)
  - [Operations](#operations)
    - [`virtual std::string repr() noexcept`](#virtual-stdstring-repr-noexcept)
    - [`protected: virtual const std::string _get_object_name() const`](#protected-virtual-const-stdstring-_get_object_name-const)


# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of class `pltr::core::Object`.


# class `Object`
Defined in file `include/pltr/core/object.h`.

`pltr::core::Object` is the base class for all objects that are defined in library **PlayTore**. As such, every defined class in library **PlayTore** should inherit from class `pltr::core::Object`. But this might not be the case for some of them.

Up to now, this class is just a helper to get fine logs when debugging applications. Method `repr()` gives informations about the inheriting instance: memory address (hexadecimal form), inheriting class name (`std::string`) and instance name if provided (see protected virtual method `_get_object_name()` which may be overridden in inheriting classes).


## Attributes
*Currently none*.


## Constructors / Destructor

### `Object ()`
The default empty constructor.

### `Object (const Object&)`
Default copy constructor.

### `Object (Object&&)`
Default move constructor.

### `virtual ~Object ()`
Default destructor.


## Assignment operators

### `Object& operator= (const Object&)`
Default copy operator.

### `Object& operator= (Object&&)`
Default move operator.


## Operations

### `virtual std::string repr() noexcept`
Helps logging information related to the inheriting object, when debugging via logs. Internally calls the protected virtual method `_get_object_name()` - see below.

### `protected: virtual const std::string _get_object_name() const`
Returns the name of the object. To be overridden in inheriting classes if this makes sense.  
See `pltr::cards::StandardCard<>` code for an example of an override.
