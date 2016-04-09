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