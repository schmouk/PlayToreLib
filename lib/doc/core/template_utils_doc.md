# `template_utils_doc.md` - intro

This file documents the template used to declare arrays of chars (i.e. null-terminated C strings) as template constant parameters: `pltr::core::StringTemplateParameter<>`.  
This class is defined within namespace `pltr::core`.

The related header file is `include/pltr/core/template_utils.h`.

See `include/pltr/playing_cards/standard_playing_cards.h` to get an example of use :
```
template<
    const pltr::core::StringTemplateParameter _CARDS_LETTERS = "23456789XJQKAJ",
    const pltr::core::StringTemplateParameter _COLORS_LETTERS = "CDHS",
    const pltr::core::StringTemplateParameter _JOKERS_COLORS = "RB",
    const std::uint32_t _START_VALUE = 2,
    const std::uint32_t _START_INDEX = 0,
    const std::uint32_t _END_INDEX = 54
>
class StandardCard : public ...

```

and to get example of declarations of some specializations, for which an example is:

```
  template<const std::uint32_t START_INDEX = 0, const std::uint32_t LAST_INDEX = 54>
  using StandardCardFr = StandardCard<"23456789XVDR1J", "TKCP", "RN", 2, START_INDEX, LAST_INDEX>;
```

---
