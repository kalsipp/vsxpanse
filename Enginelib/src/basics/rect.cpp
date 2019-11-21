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

std::ostream & operator <<(std::ostream & stream, const Rect & p) {
	stream << "("
	       << p.x << ","
	       << p.y << ","
	       << p.w << ","
	       << p.h <<  ")";
	return stream;
}