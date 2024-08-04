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
#include <string.h>


//===========================================================================
namespace pltr::core
{
    //=======================================================================
    /* \brief The base class for every object in PlayTore library. */
    struct Object
    {
        Object() noexcept = default;
        Object(const Object&) noexcept = default;
        Object(Object&&) noexcept = default;
        virtual ~Object() noexcept = default;

        Object& operator= (const Object&) noexcept = default;
        Object& operator= (Object&&) noexcept = default;

        Object(const std::string& inheriting_class_name_) noexcept;
        Object(const std::string& inheriting_class_name_, std::string& object_name_) noexcept;

        virtual std::string repr() noexcept;  //!< helps logging information related to the inheriting object when debugging via logs.

        std::string inheriting_class_name{};
        std::string object_name{};

    };

}