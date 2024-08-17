#pragma once
/*
    GNU GENERAL PUBLIC LICENSE
    Version 3, 29 June 2007

    This is part of library PlayToreLib, a c++ generic library for coding games applications.

    Copyright (C) 2024 Philippe Schmouker, ph.schmouker (at) gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


//===========================================================================
#include "pltr/playing_cards/standard_cards.h"
#include "pltr/playing_cards/unique_standard_cards_decks.h"


//===========================================================================
using BatailleCards = pltr::cards::StandardCardFr<>;  //!< playing cards are of French localization type, with default template parameters (remember: Bataille is a French game)
using BatailleDeck = pltr::cards::UniqueStandardCardsDeck32<BatailleCards>;  //!< the used deck is a 32-cards one, with unique cards in it.
