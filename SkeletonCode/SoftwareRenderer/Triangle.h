#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <stdlib.h>
#include <math.h>

#include "Vertex.h"
#include "FrameBuffer.h"
#include "Texture.h"

/* implements the triangle class */
class Triangle {
	private:
		Vertex v[3];		/* the original vertices of the triangle */

		/* per-vertex values */
		float c[3][3];		/* color at each vertex */
		float coords[3][2];

		/* point to the texture that is bound, if any */
		Texture *tex;

		inline float f01(float x,float y){
			return (v[0].y - v[1].y) * x + (v[1].x - v[0].x) * y + v[0].x * v[1].y - v[1].x * v[0].y;
		}

		inline float f12(float x,float y){
			return (v[1].y - v[2].y) * x + (v[2].x - v[1].x) * y + v[1].x * v[2].y - v[2].x * v[1].y;
		}
		inline float f20(float x,float y){
			return (v[2].y - v[0].y) * x + (v[0].x - v[2].x) * y + v[2].x * v[0].y - v[0].x * v[2].y;
		}

		void SamplerBilinearity(float x,float y,u08 *c);

	public:
		/* constructors */
		Triangle() {
			v[0].set(0, 0, 0);
			v[1].set(0, 0, 0);
			v[2].set(0, 0, 0);

			c[0][0] = 0.0;	c[0][1] = 0.0;	c[0][2] = 0.0;
			c[1][0] = 0.0;	c[1][1] = 0.0;	c[1][2] = 0.0;
			c[2][0] = 0.0;	c[2][1] = 0.0;	c[2][2] = 0.0;

			coords[0][0] = 0.0;		coords[0][1] = 0.0;	
			coords[1][0] = 0.0;		coords[1][1] = 0.0;	
			coords[2][0] = 0.0;		coords[2][1] = 0.0;

			tex = NULL;
		};

		Triangle(Vertex *v0, Vertex *v1, Vertex *v2) {
			v[0] = (*v0);
			v[1] = (*v1);
			v[2] = (*v2);

			c[0][0] = 0.0;	c[0][1] = 0.0;	c[0][2] = 0.0;
			c[1][0] = 0.0;	c[1][1] = 0.0;	c[1][2] = 0.0;
			c[2][0] = 0.0;	c[2][1] = 0.0;	c[2][2] = 0.0;
			
			coords[0][0] = 0.0;		coords[0][1] = 0.0;		coords[0][2] = 0.0;
			coords[1][0] = 0.0;		coords[1][1] = 0.0;		coords[1][2] = 0.0;
			coords[2][0] = 0.0;		coords[2][1] = 0.0;		coords[2][2] = 0.0;

			tex = NULL;
		};


		/* sets the color of vertex v of the triangle to (r,g,b) */
		void setColor(int v, int r, int g, int b) {
			if ((r < 0) || (r > 255) ||
				(g < 0) || (g > 255) ||
				(b < 0) || (b > 255)) {
				fprintf(stderr,"ERROR! Invalid color set in triangle\n");
				fflush(stderr);
				exit(-1);
			}

			c[v][0] = (float)r;
			c[v][1] = (float)g;	
			c[v][2] = (float)b;
	
			return;
		};

		void setCoords(int v, int s, int t) {
			coords[v][0] = s;
			coords[v][1] = t;

			return;
		};

		void setPosition(Vertex *v0, Vertex *v1, Vertex *v2)
		{
			v[0] = (*v0);
			v[1] = (*v1);
			v[2] = (*v2);
		}

		void setTexture(Texture *t) {
			tex = t;
			return;
		}

		/* openGL rendering of the triangle */
		void renderOpenGL(void);


		/* for debugging */
		void print(void) {
			fprintf(stderr,"Triangle:\n");
			v[0].print();
			v[1].print();
			v[2].print();
			return;
		};

		void renderSoft_color();
		void renderSoft_texture();
		
};

#endif		/* TRIANGLE_H */