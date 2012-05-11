#ifndef VERTEX_H
#define VERTEX_H

#include <cstdio>
#include <cstdlib>
//#include "globals.h"

typedef unsigned char u08;
struct Point2D
{
	double x,y;

	Point2D(int _x = 0,int _y = 0):x(_x),y(_y) {}
};

struct Color
{
	u08 r,g,b,a;

	Color(u08 _r = 255,u08 _g = 0,u08 _b = 0,u08 _a = 0):r(_r),g(_g),b(_b),a(_a) {}
	void set(u08 _r = 255,u08 _g = 0,u08 _b = 0,u08 _a = 0)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	Color operator +(const Color &t) const
	{
		return Color(r + t.r,g + t.g,b + t.b,a + t.a);
	}

	Color operator *(float factor) const
	{
		return Color(r * factor,g * factor,b * factor,a * factor);
	}

	void set_rand_color()
	{
		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
	}

};

/* represents a vertex in homogenous coordinates */
class Vertex {
	public:
		float x, y, z, w;

		Vertex() {
			set(0, 0, 0);
		};

		Vertex(float _x, float _y, float _z) {
			set(_x, _y, _z);
		};

		Vertex(float _x, float _y, float _z, float _w) {
			x = _x;		y = _y;		z = _z;		w = _w;
		};

		void set(float _x, float _y, float _z) {
			x = _x;		y = _y;		z = _z;		w = 1;
		};

		/* for debugging */
		void print(void) {
			fprintf(stderr,"[%f %f %f %f]\n", x, y, z, w);
		}
};

#endif		/* VERTEX_H */