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
#include <format>

#include "playing_cards/standard_cards.h"


//===========================================================================
namespace pltr::cards
{
    //=======================================================================
    template<
        const StringTemplateParameter _CARDS_LETTERS,
        const StringTemplateParameter _COLORS_LETTERS,
        const StringTemplateParameter _JOKERS_COLORS
    >
    void StandardCard<_CARDS_LETTERS, _COLORS_LETTERS, _JOKERS_COLORS>::_set_text() noexcept
    {
        if (!is_joker())
            this->text = std::format(
                "{:c}{:c}",
                _CARDS_LETTERS[this->ident / COLORS_COUNT],
                _COLORS_LETTERS[this->ident % COLORS_COUNT]
            );
        else
            this->text = std::format(
                "{:c}{:c}",
                _CARDS_LETTERS[JOKERS_INDEX],
                (this->ident == JOKERS_FIRST_IDENT) ? _JOKERS_COLORS[0] : _JOKERS_COLORS[1]
            );
    }

}