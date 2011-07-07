#include "Rasterization.h"
#include "FrameBuffer.h"
#include <math.h>


#include "Values.h"
void DrawLine(int x0,int y0,int x1,int y1)
{
	bool steep = abs(y1 - y0) > abs(x1 - x0);
	if(steep)
	{
		x0 ^= y0 ^= x0 ^= y0;
		x1 ^= y1 ^= x1 ^= y1;
	}

	if(x0 > x1)
	{
		x0 ^= x1 ^= x0 ^= x1;
		y0 ^= y1 ^= y0 ^= y1;
	}

	int delta_x = x1 - x0;
	int delta_y = abs(y1 - y0);
	int error = delta_x / 2;
	int ystep,y = y0;

	ystep = (y0 < y1) ? 1 : -1;

	for(int x = x0;x <= x1;x++)
	{
		if(steep)
			g_fb.setColor(y,x,g_color[0],g_color[1],g_color[2]);
		else
			g_fb.setColor(x,y,g_color[0],g_color[1],g_color[2]);
		error -= delta_y;
		if(error < 0)
		{
			y += ystep;
			error += delta_x;
		}
	}

	
}

