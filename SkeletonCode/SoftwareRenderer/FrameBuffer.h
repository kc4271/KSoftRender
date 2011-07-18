#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdlib.h>
#include <atlimage.h>
#include "globals.h"

/* implements the framebuffer. you might want to modify it to add depth buffering and other capabilities */
class FrameBuffer {
	private:
		int width, height;

		/* all the buffers are defined from the lower left corner of the screen */
		u08 *color_buffer;		/* color buffer is unsigned bytes buffer size 3*w*h */

	public:
		/* constructor */
		FrameBuffer(int _w, int _h) {
			width = _w;		height = _h;

			/* allocate the buffer */
			color_buffer = (u08 *)malloc(sizeof(u08) * width * height * 3);			 
		};

		/* destructor */
		~FrameBuffer() {
			if (color_buffer)
				free(color_buffer);
		};

		/* get color ptr */
		inline u08 *getColorPtr(int x, int y) {
			return (color_buffer + ((y * width + x)*3));
		};

		inline void setColor(int x,int y,u08 r = 255,u08 g = 255,u08 b = 255)
		{
			color_buffer[(y * width + x)*3] = r;
			color_buffer[(y * width + x)*3 + 1] = g;
			color_buffer[(y * width + x)*3 + 2] = b;
		}

		inline void clearBuffer()
		{
			memset(color_buffer,0,sizeof(u08) * width * height * 3);
		}

		inline void clearBuffer(u08 r,u08 g,u08 b)
		{
			for(int i = 0;i < height;i++)
			{
				for(int j = 0;j < width;j++)
				{
					color_buffer[(i * width + j) * 3] = r;
					color_buffer[(i * width + j) * 3 + 1] = g;
					color_buffer[(i * width + j) * 3 + 2] = b;
				}
			}
		}

		void copyColorBuffer(CImage *image);
		void dumpColorBufferToFile(char *name);
		void dumpToScreen(void);
};

#endif		/* FRAMEBUFFER_H */
