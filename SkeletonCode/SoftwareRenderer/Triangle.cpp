#include "Triangle.h"
#include "Values.h"

/* for openGL rendering of the triangle */
void Triangle :: renderOpenGL(void) {
	/* first bind the texture */
	if (tex) {
		tex->bind();
	}

	/* now draw the triangle */
	glBegin(GL_TRIANGLES);
		glTexCoord2fv(coords[0]);
		glColor3fv(c[0]);
		glVertex3f(v[0].x, v[0].y, v[0].z);

		glTexCoord2fv(coords[1]);
		glColor3fv(c[1]);
		glVertex3f(v[1].x, v[1].y, v[1].z);

		glTexCoord2fv(coords[2]);
		glColor3fv(c[2]);
		glVertex3f(v[2].x, v[2].y, v[2].z);
	glEnd();

	/* release the texture */
	if (tex) {
		tex->release();
	}

	return;
}

void Triangle::renderSoft_color()
{
	float Xmin = floor(v[0].x),Xmax = ceil(v[0].x);
	float Ymin = floor(v[0].y),Ymax = ceil(v[0].y);

	if(floor(v[1].x) < Xmin) Xmin = floor(v[1].x);
	if(ceil(v[1].x) > Xmax) Xmax = ceil(v[1].x);
	if(floor(v[1].y) < Ymin) Ymin = floor(v[1].y);
	if(ceil(v[1].y) > Ymax) Ymax = ceil(v[1].y);

	if(floor(v[2].x) < Xmin) Xmin = floor(v[2].x);
	if(ceil(v[2].x) > Xmax) Xmax = ceil(v[2].x);
	if(floor(v[2].y) < Ymin) Ymin = floor(v[2].y);
	if(ceil(v[2].y) > Ymax) Ymax = ceil(v[2].y);

	float fa = f12(v[0].x,v[0].y);
	float fb = f20(v[1].x,v[1].y);
	float fc = f01(v[2].x,v[2].y);

	float neg_fa = f12(-1,-1);
	float neg_fb = f20(-1,-1);
	float neg_fc = f01(-1,-1);
	for(float y = Ymin;y <= Ymax;y += 1.0f)
	{
		for(float x = Xmin;x <= Xmax;x += 1.0f)
		{
			float alpha = f12(x,y) / fa;
			float beta = f20(x,y) / fb;
			float gamma = f01(x,y) / fc;
			if(alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				if((alpha > 0 || fa * neg_fa > 0) 
					&& (beta > 0 || fb * neg_fb > 0)
					&& (gamma > 0 || fc * neg_fc > 0))
				{
					u08 color[3];
					color[0] = u08((alpha * c[0][0] + beta * c[1][0] + gamma * c[2][0]));
					color[1] = u08((alpha * c[0][1] + beta * c[1][1] + gamma * c[2][1]));
					color[2] = u08((alpha * c[0][2] + beta * c[1][2] + gamma * c[2][2]));
					g_fb.setColor(int(x),int(y),color[0],color[1],color[2]);
				}
			}
		}
	}
}

void Triangle::renderSoft_texture()
{
	float Xmin = floor(v[0].x),Xmax = ceil(v[0].x);
	float Ymin = floor(v[0].y),Ymax = ceil(v[0].y);

	if(floor(v[1].x) < Xmin) Xmin = floor(v[1].x);
	if(ceil(v[1].x) > Xmax) Xmax = ceil(v[1].x);
	if(floor(v[1].y) < Ymin) Ymin = floor(v[1].y);
	if(ceil(v[1].y) > Ymax) Ymax = ceil(v[1].y);

	if(floor(v[2].x) < Xmin) Xmin = floor(v[2].x);
	if(ceil(v[2].x) > Xmax) Xmax = ceil(v[2].x);
	if(floor(v[2].y) < Ymin) Ymin = floor(v[2].y);
	if(ceil(v[2].y) > Ymax) Ymax = ceil(v[2].y);

	float fa = f12(v[0].x,v[0].y);
	float fb = f20(v[1].x,v[1].y);
	float fc = f01(v[2].x,v[2].y);

	float neg_fa = f12(-1,-1);
	float neg_fb = f20(-1,-1);
	float neg_fc = f01(-1,-1);
	for(float y = Ymin;y <= Ymax;y += 1.0f)
	{
		for(float x = Xmin;x <= Xmax;x += 1.0f)
		{
			float alpha = f12(x,y) / fa;
			float beta = f20(x,y) / fb;
			float gamma = f01(x,y) / fc;
			float texX,texY;
			if(alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				if((alpha > 0 || fa * neg_fa > 0) 
					&& (beta > 0 || fb * neg_fb > 0)
					&& (gamma > 0 || fc * neg_fc > 0))
				{
					u08 color[3];
					texX = min(alpha * coords[0][0] + beta * coords[1][0] + gamma * coords[2][0],1.0);
					texY = min(alpha * coords[0][1] + beta * coords[1][1] + gamma * coords[2][1],1.0);
					SamplerBilinearity(texX,texY,color);
					g_fb.setColor(int(x),int(y),color[0],color[1],color[2]);
				}
			}
		}
	}
}

void Triangle::SamplerBilinearity(float x,float y,u08 *c)
{
	x *= tex->width;
	y *= tex->height;
	
	x -= min(1.0,x);
	y -= min(1.0,y);

	//if((x >= tex->width - 1) || (y >= tex->height - 1))
	//{
	//	c[0] = 255;
	//	c[1] = c[2] = 0;
	//	return;
	//}
	float four_color[4][3];


	tex->getFloatColor(int(x),int(y),&four_color[0][0]);
	tex->getFloatColor(min(int(x) + 1,tex->width - 1),int(y),&four_color[1][0]);
	tex->getFloatColor(int(x),min(int(y) + 1,tex->height  - 1),&four_color[2][0]); 
	tex->getFloatColor(min(int(x) + 1,tex->width - 1),
		min(int(y) + 1,tex->height  - 1),&four_color[3][0]); 


	x -= floor(x);
	y -= floor(y);


	c[0] = u08(four_color[0][0] * (1 - x) * (1 - y) + four_color[1][0] * x * (1 - y) 
		+ four_color[2][0] * (1 - x) * y + four_color[3][0] * x * y);
	c[1] = u08(four_color[0][1] * (1 - x) * (1 - y) + four_color[1][1] * x * (1 - y) 
		+ four_color[2][1] * (1 - x) * y + four_color[3][1] * x * y);
	c[2] = u08(four_color[0][2] * (1 - x) * (1 - y) + four_color[1][2] * x * (1 - y) 
		+ four_color[2][2] * (1 - x) * y + four_color[3][2] * x * y);
}