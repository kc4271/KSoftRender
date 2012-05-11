#include "Rasterization.h"
#include "FrameBuffer.h"
#include <cmath>
#include "Vertex.h"
#include "mathlib.h"
#include "Values.h"

void DrawLine(Point2D p1,Point2D p2)
{
	DrawLine(p1.x,p1.y,p2.x,p2.y);
}

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
			g_fb.setColor(y,x,g_color);
		else
			g_fb.setColor(x,y,g_color);
		error -= delta_y;
		if(error < 0)
		{
			y += ystep;
			error += delta_x;
		}
	}
}

void DrawBezier(Point2D *point_list,int size,Color s,Color e)
{
	int point_sum = max(size,1000);

	Point2D point_draw;
	Point2D *segments[2];
	segments[0] = new Point2D[size * 2];
	segments[1] = segments[0] + size;
	
	Point2D last_point;
	
	for(int z = 0;z <= point_sum;z++)
	{
		for(int i = 0;i < size;i++)
			segments[0][i] = point_list[i];

		double t = double(z) / point_sum;
		for(int i = 0;i < size - 1;i++)
		{
			Point2D *last = segments[i % 2];
			Point2D *cur = segments[(i + 1) % 2];
			for(int j = 0;j < size - i - 1;j++)
			{
				cur[j].x = (1 - t) * last[j].x + t * last[j + 1].x;
				cur[j].y = (1 - t) * last[j].y + t * last[j + 1].y;
			}
		}
		point_draw.x = segments[(size + 1) % 2][0].x;
		point_draw.y = segments[(size + 1) % 2][0].y;

		g_fb.setColor(int(point_draw.x),int(point_draw.y),s * (1 - t) + e * t);
		if(z)
		{
			if(abs(last_point.x - point_draw.x) > 1 || abs(last_point.y - point_draw.y) > 1)
			{
				g_color = s * (1 - t) + e * t;
				DrawLine(last_point,point_draw);
			}
		}

		last_point = point_draw;
	}
	
	delete [](segments[0]);
}