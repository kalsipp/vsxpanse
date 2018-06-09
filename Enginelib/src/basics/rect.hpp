#pragma once
#include <SDL.h>
#include <iostream>
class Rect {
public:
	Rect(double _x = 0,
		 double _y = 0,
		 double _w = 0,
		 double _h = 0);
	Rect(const SDL_Rect &);
	SDL_Rect get_sdl_rect()const;
	double x = 0;
	double y = 0;
	double w = 0;
	double h = 0;
	friend std::ostream & operator <<(std::ostream & stream, const Rect &);
private:
};