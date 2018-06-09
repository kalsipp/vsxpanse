#include "rect.hpp"

Rect::Rect(
	double _x,
	double _y,
	double _w,
	double _h):
	x(_x),
	y(_y),
	w(_w),
	h(_h) {}

Rect::Rect(const SDL_Rect & new_rect) {
	x = new_rect.x;
	y = new_rect.y;
	w = new_rect.w;
	h = new_rect.h;
}

SDL_Rect Rect::get_sdl_rect() const {
	return SDL_Rect{
		int(round(x)),
		int(round(y)),
		int(round(w)),
		int(round(h))};
}

std::ostream & operator <<(std::ostream & stream, const Rect & p) {
	stream << "("
	       << p.x << ","
	       << p.y << ","
	       << p.w << ","
	       << p.h <<  ")";
	return stream;
}