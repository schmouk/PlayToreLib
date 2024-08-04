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
#include <format>
#include <string>

#include "core/object.h"


//===========================================================================
namespace pltr::core
{
    //-----------------------------------------------------------------------
    Object::Object(const std::string& inheriting_class_name_) noexcept
        : inheriting_class_name(inheriting_class_name_)
        , object_name()
    {}


    //-----------------------------------------------------------------------
    Object::Object(const std::string& inheriting_class_name_, std::string& object_name_) noexcept
        : inheriting_class_name(inheriting_class_name_)
        , object_name(object_name_)
    {}


    //-----------------------------------------------------------------------
    std::string Object::repr() noexcept
    {
        // reminder: helps logging information related to the inheriting object when debugging via logs.
        // Use it and add your own logs text when debugging the code of your inheriting objects.
        return std::format("{:08x} (class '{:s}' - instance name '{:s}')",
            std::size_t(this),
            this->inheriting_class_name,
            this->object_name
        );
    }

}