#pragma once

#include "Definitions.h"

struct Color
{
    uint8 r, g, b, a;

    Color() {}
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