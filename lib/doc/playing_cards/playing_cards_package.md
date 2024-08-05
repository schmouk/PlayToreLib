# `playing_cards` package - intro

This package is declared and defined in directory `include/pltr/playing_cards.h`.

It defines what are playing cards, what are some of their specializations, 
what are decks of cards and some of their specialization too.  
It defines also actions that can be applied to them.

All definitions are embedded in namespace `pltr::cards`.


# list of header files

About playing cards:
- `pltr/playing_cards/playing_cards.h`
- `pltr/playing_cards/standard_cards.h`

About decks of playing cards:
- `pltr/playing_cards/cards_deck.h`
- `pltr/playing_cards/standard_cards_decks.h`
- `pltr/playing_cards/unique_standard_cards_deck.h`

# Package classes and API documentation

The documentation of this package is splitted into next files:
- [playing_cards_doc.md](./playing_cards_doc.md)  
Documents templated class `PlayingCardsT<>`, the base class for every playing cards type;
- [standard_cards_doc.md](./standard_cards_doc.md)  
Documents templated class `StandardCard<>`, the base class of standard playing cards;
- [cards_deck_doc.md](./cards_deck_doc.md)  
Documents templated class `CardsDeck<>`, the base class for all types of cards decks;
- [standard_cards_deck_doc.md](./standard_cards_deck_doc.md)  
Documents templated class `StandardCardsDeck<>`, the class of decks containing standard cards with maybe duplication of same cards in them;
- [unique_standard_cards_deck_doc.h](./unique_standard_cards_deck_doc.h)  
Documents templated class `UniqueStandardCardsDeck<>`, the same types of decks than right above but with no duplication of cards in them.
