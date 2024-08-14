# `core` package - intro

This package is declared and defined in directory `include/pltr/core`.

It defines core objects and classes for library **PlayTore**. Those are available 

All definitions are embedded in namespace `pltr::core`.

---
# list of header files

- `pltr/core/object.h`
- `pltr/core/random.h`
- `pltr/core/template_utils.h`


---

# Package classes and API documentation

The documentation of this package is splitted into next files:
- [object_doc.md](./object_doc.md)  
Documents base class `Object`, the base class for all type of objects defined in **PlayTore**;
- [random_doc.md](./random_doc.md)  
Documents base class `RandomBase`, the base class for randomness generation and two inheriting classes that generate pseudo random numbers according to a specified distribution function: `Random` which is not thread safe, and `RandomThreadSafe` which is thread safe but a little bit slower also;
- [template_utils_doc.md](./template_utils_doc.md)  
Documents utilities that can be used for template declarations and definitions.

---
