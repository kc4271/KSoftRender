#pragma once

#include <windows.h>
#include <atlimage.h>

#include <cstdio>
#include <cmath>

#include <gl/glut.h>

/* implements the texture mapping class so that the triangles
   can be textured in our software renderer */
class Texture {
	public:
		int width, height;	/* width and height for the texture */
		u08 *data;			/* contains the color data for the texture */

		/* for opengl only */
		GLuint	tex;		/* handle to opengl texture (only used by opengl) */
		void copyTextureData(CImage *image); 

		void getFloatColor(int u, int v, float *color) {
			u08 *ptr = data + (((v * width) + u) * 3); 
			color[0] = (float) *(ptr);
			color[1] = (float) *(ptr + 1);
			color[2] = (float) *(ptr + 2);
		}

	
		/* constructor takes the name of the file to use as a texture */
		Texture(char *name);

		/* destructor */
		~Texture() {
			if (data)
				free(data);
		};

		
		/* switches between nearest neighbor and bilinear interpolation */
		void switchTextureFiltering(bool flag);


		/* for opengl only */
		void bind(void) {
			glBindTexture(GL_TEXTURE_2D, tex);
			glEnable(GL_TEXTURE_2D);
		};

		void release(void) {
			glDisable(GL_TEXTURE_2D);
		};

};

