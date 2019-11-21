#pragma once
#include <iostream>
class Rect {
public:
	Rect(double _x = 0,
		 double _y = 0,
		 double _w = 0,
		 double _h = 0);
	double x = 0;
	double y = 0;
	double w = 0;
	double h = 0;
	friend std::ostream & operator <<(std::ostream & stream, const Rect &);
private:
};