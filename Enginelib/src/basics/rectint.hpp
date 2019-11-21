#pragma once

class Rect;
class RectInt
{
public:
    RectInt(int _x = 0,
            int _y = 0,
            int _w = 0,
            int _h = 0);
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

	RectInt(const Rect&);
};