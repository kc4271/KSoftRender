#pragma once
#include "Vertex.h"
#include "Values.h"
void DrawLine(Point2D p1,Point2D p2);
void DrawLine(int x1,int y1,int x2,int y2);
void DrawBezier(Point2D *point_list,int size,Color s = g_color,Color e = g_color);
