#include "rectint.hpp"
#include "rect.hpp"
#include "helpers.hpp"
RectInt::RectInt(int _x,
                 int _y,
                 int _w,
                 int _h) : x(_x), y(_y), w(_w), h(_h)
{
}

RectInt::RectInt(const Rect& other)
{
    x = helpers::round_to_int(other.x);
    y = helpers::round_to_int(other.y);
    w = helpers::round_to_int(other.w);
    h = helpers::round_to_int(other.h);
}
