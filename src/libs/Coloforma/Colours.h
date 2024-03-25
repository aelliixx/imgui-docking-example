#pragma once

#include <cstdint>
#include <string>

namespace alx {

struct Colour {

    uint8_t r;
    uint8_t g;
    uint8_t b;

    Colour()
        : r(255)
        , g(0)
        , b(0)
    {
    }
    Colour(uint8_t R, uint8_t G, uint8_t B)
        : r(R)
        , g(G)
        , b(B)
    {
    }

    std::string to_string() const { return std::to_string(r) + " " + std::to_string(g) + " " + std::to_string(b); }

    static Colour Red;
    static Colour Green;
    static Colour Blue;
    static Colour Yellow;
    static Colour Orange;
    static Colour Lime;
    static Colour LightGreen;
    static Colour LightBlue;
    static Colour Purple;
    static Colour Pink;
    static Colour Grey;
    static Colour DarkGrey;
    static Colour LightGrey;
    static Colour White;
    static Colour Black;
};

}
