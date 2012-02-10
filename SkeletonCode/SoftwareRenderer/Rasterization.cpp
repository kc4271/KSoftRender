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


//size must less than 60 because of the length of type long long in function GetCnj(n,j)
void DrawBezier(Point2D *point_list,int size,Color s,Color e)
{
	int point_sum = 0;
	for(int i = 1;i < size;i++)
	{
		point_sum += (int)sqrt(double(square(point_list[i].x - point_list[i-1].x) +  
			square(point_list[i].y - point_list[i - 1].y)));
	}
	point_sum *= 1;

	Point2D point_draw;
//  printf("%d\n",size);
//  for(int i = 0;i < size - 1;i++)
//  	printf("%lld ",GetCnj(size - 1,i));
//  puts("\n");
	for(double t = 0.0;t < 1.0;t += 1.0 / point_sum)
	{
		point_draw.x = point_draw.y = 0;
		int dim = size - 1;
		for(int i = 0;i <= dim;i++)
		{
			point_draw.x += abs(GetCnj(dim,i) * pow(t,i) * pow(1 - t,dim - i) * point_list[i].x);
			point_draw.y += abs(GetCnj(dim,i) * pow(t,i) * pow(1 - t,dim - i) * point_list[i].y);
		}
		g_fb.setColor(int(point_draw.x),int(point_draw.y),s * (1 - t) + e * t);
	}
}
