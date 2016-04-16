/*
* RetroGB

* Copyright (C) 2016  Michael Kösel

* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.

* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.

* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>
*
*/

#pragma once

#include "Definitions.h"

struct Color
{
    uint8 r, g, b, a;

    Color()
        : r(255), g(255), b(255), a(255) {}
    Color(uint8 r, uint8 g, uint8 b, uint8 a)
        : r(r), g(g), b(b), a(a) {}

    bool operator!=(const Color& c)
    {
        return (r != c.r) && (g != c.g) && (b != c.b) && (a != c.a);
    }

    bool operator==(const Color& c)
    {
        return (r == c.r) && (g == c.g) && (b == c.b) && (a == c.a);
    }

    static const Color WHITE;
    static const Color BLACK;
};