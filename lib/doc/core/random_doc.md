# `random_doc.md` - intro

This file documents the implementation of randomness in library **PlayTore**. It is part of namespace `pltr::core`.

The related header file is [`include/pltr/core/random.h`](../../include/pltr/core/random.h).


## `random.h` header file - table of content <!-- omit in toc -->
- [`random_doc.md` - intro](#random_docmd---intro)
- [class `BaseRandom<>`](#class-baserandom)
  - [Attributes](#attributes)
    - [`protected static inline PRNGT _rand_generator`](#protected-static-inline-prngt-_rand_generator)
    - [`protected static inline bool _already_inited`](#protected-static-inline-bool-_already_inited)
  - [Constructors / Destructor](#constructors--destructor)
    - [`BaseRandom ()`](#baserandom-)
    - [`BaseRandom (const BaseRandom&) = delete`](#baserandom-const-baserandom--delete)
    - [`BaseRandom (BaseRandom&&) = delete`](#baserandom-baserandom--delete)
    - [`virtual ~BaseRandom ()`](#virtual-baserandom-)
  - [Operations](#operations)
    - [`protected: inline static void _check_init()`](#protected-inline-static-void-_check_init)
- [class `Random<>`](#class-random)
  - [Types wrappers](#types-wrappers)
  - [Constructors / Destructor](#constructors--destructor-1)
    - [`Random ()`](#random-)
    - [`virtual ~Random ()`](#virtual-random-)
  - [Operators](#operators)
    - [templated `operator()`](#templated-operator)
  - [Operations](#operations-1)
    - [`template<typename IntType>` `static const IntType urand (const IntType min, const IntType max)`](#templatetypename-inttype-static-const-inttype-urand-const-inttype-min-const-inttype-max)
    - [`template<typename FloatType>` `static const FloatType urand(const FloatType min, const FloatType max)`](#templatetypename-floattype-static-const-floattype-urandconst-floattype-min-const-floattype-max)
    - [`template<typename FloatType>` `static const FloatType urand()`](#templatetypename-floattype-static-const-floattype-urand)
    - [`static const double urand ()`](#static-const-double-urand-)
- [class `RandomThreadSafe<>`](#class-randomthreadsafe)
  - [Constructors / Destructor](#constructors--destructor-2)
    - [`RandomThreadSafe ()`](#randomthreadsafe-)
    - [`virtual ~RandomThreadSafe ()`](#virtual-randomthreadsafe-)
  - [Operators](#operators-1)
    - [templated `operator()`](#templated-operator-1)
  - [Operations](#operations-2)
    - [`template<typename IntType>` `static const IntType urand (const IntType min, const IntType max)`](#templatetypename-inttype-static-const-inttype-urand-const-inttype-min-const-inttype-max-1)
    - [`template<typename FloatType>` `static const FloatType urand(const FloatType min, const FloatType max)`](#templatetypename-floattype-static-const-floattype-urandconst-floattype-min-const-floattype-max-1)
    - [`template<typename FloatType>` `static const FloatType urand()`](#templatetypename-floattype-static-const-floattype-urand-1)
    - [`static const double urand ()`](#static-const-double-urand--1)


# Code documentation <!-- omit in toc -->
Next subsections document the public and protected APIs of templated class `pltr::core::BaseRandom<>` and its inheriting subclasses, `pltr::core::Random` and `pltr::core::RandomThreadSafe`.


---

# class `BaseRandom<>`
Defined in file [`include/pltr/core/random.h`](../../include/pltr/core/random.h).

`pltr::core::BaseRandom<>` is the base class for all randomness objects that are defined in library **PlayTore**. 

It is declared as:
```
template<typename PRNGT = std::mt19937_64>
class BaseRandom : public pltr::core::Object
```

The template argument is:
- `PRNGT`:  
the type of the Pseudo Random Numbers Generator that is internally set and used to generate pseudo random suites of numbers. It defaults to the STL PRNG `std::mt19937_64`, the 64-bits Mersenne-Twister algorithm.

Templated class `BaseRandom<>` inherits from class [`pltr::core::Object`](./object_doc.md).

Notice: The Mersenne-Twister algorithm is the mostly and widely used generator in most programming languages. It gets a very long period and is known to be a very good pseudo-ransom numbers generators.  
It gets a few drawbacks nevertheless. First, its internal states needs a memory storage of about 5 kBytes. Second, it is relatively slow because of all the bits shifts computations done on numbers. Third, it fails two main tests in the famous testing suite [TestU01](https://simul.iro.umontreal.ca/testu01/tu01.html) from P. L'Ecuyer and R. Simard - see also the freely avaiable PDF version of the paper [here](https://simul.iro.umontreal.ca/testu01/guideshorttestu01.pdf). Finally, it may take up to 700,000 draws before ensuring the escape from zero-land.  
So, **PlayTore** will soon replace this default algorithm, and maybe the whole content of file [`plt::core::random.h`](../../include/pltr/core/random.h) either, with the help of library **CppRandLib** which provides the implementation of better PRNGs, notably the WELLs ones which currently are not available with the c++ STL.


## Attributes

### `protected static inline PRNGT _rand_generator`
This is a singleton implementation of one and only one instance of the PRNG for the whole library of **PlayTore**. This way, whatever the size of its internal state (e.g. about 5 kBytes for the Mersenne-Twister 64-bits version), it will be instantiated only once.  
Its internal state is set at the very first call of any random method or operator of inheriting classes, not at application launch. See next attribute.

### `protected static inline bool _already_inited`
This belongs also to the singleton implementation of one and only one instance of the PRNG for the whole library of **PlayTore**. It is set to `false` at application launch time. At any call to random method or operator of any inheriting class, it is checked and, if false, it randomly sets the internal state of the PRNG and is then switched to `true`.  
See protected method `_check_init()`.


## Constructors / Destructor

### `BaseRandom ()`
The default empty constructor.

### `BaseRandom (const BaseRandom&) = delete`
Copy constructor is not allowed. So, copy assignment operator is not allowed as well.

### `BaseRandom (BaseRandom&&) = delete`
Move constructor is not allowed. So, move assignment operator is not allowed as well.

### `virtual ~BaseRandom ()`
Default destructor.


## Operations

### `protected: inline static void _check_init()`
To be called in every random generation method or operator defined in inheriting classes, before each of them generating any pseudo random number.  
This protected method internally checks the inited status of the internal PRNG singleton and initializes its internal state, only once, if needed.


---

# class `Random<>`
Defined in file [`include/pltr/core/random.h`](../../include/pltr/core/random.h).

`pltr::core::Random<>` is a not thread safe class for randomness objects that are used in conjunction with distribution functions, in library **PlayTore**.  
If your application uses randomness generation in one and only one thread (for instance, the main thread of the application) then this class is the one to use.  
If your application generates randomness in multiple threads, use class `pltr::core::RandomThreadSafe<>` instead.

Class `pltr::core::Random<>` is declared as:
```
template<typename PRNGT = std::mt19937_64>
struct Random : protected pltr::core::BaseRandom<PRNGT>
```

The template argument is:
- `PRNGT`:  
the type of the Pseudo Random Numbers Generator that is internally set and used to generate pseudo random suites of numbers. It defaults to the STL PRNG `std::mt19937_64`, the 64-bits Mersenne-Twister algorithm.

Templated class `Random<>` inherits from class `pltr::core::BaseRandom` and, as such, from class [`pltr::core::Object`](./object_doc.md) also.

Notice: The Mersenne-Twister algorithm is the mostly and widely used generator in most programming languages. It gets a very long period and is known to be a very good pseudo-ransom numbers generators.  
It gets a few drawbacks nevertheless. First, its internal states needs a memory storage of about 5 kBytes. Second, it is relatively slow because of all the bits shifts computations done on numbers. Third, it fails two main tests in the famous testing suite [TestU01](https://simul.iro.umontreal.ca/testu01/tu01.html) from P. L'Ecuyer and R. Simard - see also the freely avaiable PDF version of the paper [here](https://simul.iro.umontreal.ca/testu01/guideshorttestu01.pdf). Finally, it may take up to 700,000 draws before ensuring the escape from zero-land.  
So, **PlayTore** will soon replace this default algorithm, and maybe the whole content of file `plt::core::random.h` either, with the help of library **CppRandLib** which provides the implementation of better PRNGs, notably the WELLs ones which currently are not available with the c++ STL.


## Types wrappers
```
using MyBaseClass = pltr::core::BaseRandom<PRNGT>;
```
(used internally).


## Constructors / Destructor

### `Random ()`
The default empty constructor.

Notice: Copy constructor is not allowed. So, copy assignment operator is not allowed as well.

Notice: Move constructor is not allowed. So, move assignment operator is not allowed as well.

### `virtual ~Random ()`
Default destructor.


## Operators

### templated `operator()`
Returns a random value according to a specified distribution function.

It is declared as
```
template<typename DistributionFunctionT>
inline const DistributionFunctionT::result_type operator() (DistributionFunctionT& distribution_function)
```

Template parameter `DistributionFunctionT` is the type of a distribution function as defined in the STL `<random>` header file - e.g. `std::uniform_real_distribution`, see the [cpp reference .com](https://en.cppreference.com/w/cpp/header/random) related documentation page for an overview of STL distribution functions, and more.

Each STL distribution function declares `result_type`, the type of their results value: this is also the result of `operator()` computation.

Operator `()` declares one parameter, a mutable reference to an instance of the distribution function to be used with the next pseudo random number that is generated in the PRNG suite.  
Reminder: the PRNG suite is evaluated by a random generator of type `PRNGT` and that is declared and initialized within base class `BaseRandom<PRNGT>`. 


## Operations

### `template<typename IntType>` `static const IntType urand (const IntType min, const IntType max)`
Returns a random integer in range [min, max] with uniform distribution: each value from `min` to `max`, both included, gets equal probability to be generated.

Notice: `IntType` is required to be of an integer type. This is automatically checked at compile time.

### `template<typename FloatType>` `static const FloatType urand(const FloatType min, const FloatType max)`
Returns a random float value in range [min, max] with uniform distribution: each value from `min` to `max`, both included, gets equal probability to be generated.

Notice: `FloatType` is required to be of a floating value type. This is automatically checked at compile time.

### `template<typename FloatType>` `static const FloatType urand()`
Returns a random float value in range [0.0, 1.0] with uniform distribution: each value from `0.0` to `1.0`, both included, gets equal probability to be generated.

Notice: `FloatType` is required to be of a floating value type. This is automatically checked at compile time.

### `static const double urand ()`
Shortcut to return a double value in range [0.0, 1.0] with uniform distribution: each value from `0.0` to `1.0`, both included, gets equal probability to be generated.


---

# class `RandomThreadSafe<>`
Defined in file [`include/pltr/core/random.h`](../../include/pltr/core/random.h).

`pltr::core::RandomThreadSafe<>` is the thread safe version of class `pltr::core::Random`. 
If your application generates randomness in multiple threads, this is the class to use to generate random values according to specified distribution functions.
If your application uses randomness generation in one and only one thread (for instance, the main thread of the application) then you should use class `pltr::core::Random<>` instead, since `Random<>`is 15% to 20% faster than `RandomThreadSafe<>`.  

Class `pltr::core::RandomThreadSafe<>` is declared as:
```
template<typename PRNGT = std::mt19937_64>
class RandomThreadSafe
```

The template argument is:
- `PRNGT`:  
the type of the Pseudo Random Numbers Generator that is internally set and used to generate pseudo random suites of numbers. It defaults to the STL PRNG `std::mt19937_64`, the 64-bits Mersenne-Twister algorithm.

Templated class `RandomThreadSafe<>` inherits from class `pltr::core::Object` and inherits of class `pltr::core::Random<PRNGT>` behavior by composition.

Notice: The Mersenne-Twister algorithm is the mostly and widely used generator in most programming languages. It gets a very long period and is known to be a very good pseudo-ransom numbers generators.  
It gets a few drawbacks nevertheless. First, its internal states needs a memory storage of about 5 kBytes. Second, it is relatively slow because of all the bits shifts computations done on numbers. Third, it fails two main tests in the famous testing suite [TestU01](https://simul.iro.umontreal.ca/testu01/tu01.html) from P. L'Ecuyer and R. Simard - see also the freely avaiable PDF version of the paper [here](https://simul.iro.umontreal.ca/testu01/guideshorttestu01.pdf). Finally, it may take up to 700,000 draws before ensuring the escape from zero-land.  
So, **PlayTore** will soon replace this default algorithm, and maybe the whole content of file `plt::core::random.h` either, with the help of library **CppRandLib** which provides the implementation of better PRNGs, notably the WELLs ones which currently are not available with the c++ STL.


## Constructors / Destructor

### `RandomThreadSafe ()`
The default empty constructor.

Notice: Copy constructor is not allowed. So, copy assignment operator is not allowed as well.

Notice: Move constructor is not allowed. So, move assignment operator is not allowed as well.

### `virtual ~RandomThreadSafe ()`
Default destructor.


## Operators

### templated `operator()`
Returns a random value according to a specified distribution function. The operations of this operator are *guarded* by an internal private mutex.

The operator is declared as
```
template<typename DistributionFunctionT>
inline const DistributionFunctionT::result_type operator() (DistributionFunctionT& distribution_function)
```

Template parameter `DistributionFunctionT` is the type of a distribution function as defined in the STL `<random>` header file - e.g. `std::uniform_real_distribution`, see the [cpp reference .com](https://en.cppreference.com/w/cpp/header/random) related documentation page for an overview of STL distribution functions, and more.

Each STL distribution function declares `result_type`, the type of their results value: this is also the result of `operator()` computation.

Operator `()` declares one parameter, a mutable reference to an instance of the distribution function to be used with the next pseudo random number that is generated in the PRNG suite.  
Reminder: the PRNG suite is evaluated by a random generator of type `PRNGT` and that is declared and initialized within base class `BaseRandom<PRNGT>`. 


## Operations

All operations are *guarded* by a private internal mutex.

### `template<typename IntType>` `static const IntType urand (const IntType min, const IntType max)`
Returns a random integer in range [min, max] with uniform distribution: each value from `min` to `max`, both included, gets equal probability to be generated.

Notice: `IntType` is required to be of an integer type. This is automatically checked at compile time.

### `template<typename FloatType>` `static const FloatType urand(const FloatType min, const FloatType max)`
Returns a random float value in range [min, max] with uniform distribution: each value from `min` to `max`, both included, gets equal probability to be generated.

Notice: `FloatType` is required to be of a floating value type. This is automatically checked at compile time.

### `template<typename FloatType>` `static const FloatType urand()`
Returns a random float value in range [0.0, 1.0] with uniform distribution: each value from `0.0` to `1.0`, both included, gets equal probability to be generated.

Notice: `FloatType` is required to be of a floating value type. This is automatically checked at compile time.

### `static const double urand ()`
Shortcut to return a double value in range [0.0, 1.0] with uniform distribution: each value from `0.0` to `1.0`, both included, gets equal probability to be generated.

---
