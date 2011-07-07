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

void Triangle::renderSoft_raster()
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

	for(float y = Ymin;y <= Ymax;y += 1.0f)
	{
		for(float x = Xmin;x <= Xmax;x += 1.0f)
		{
			float alpha = f12(x,y) / fa;
			float beta = f20(x,y) / fb;
			float gamma = f01(x,y) / fc;
			if(alpha >= 0 && beta >= 0 && gamma >= 0)
			{
				if((alpha > 0 || fa * f12(-1,-1) > 0) 
					&& (beta > 0 || fb * f20(-1,-1) > 0)
					&& (gamma > 0 || fc * f01(-1,-1) > 0))
				{
					u08 color[3];
					color[0] = u08((alpha * c[0][0] + beta * c[1][0] + gamma * c[2][0]) * 255);
					color[1] = u08((alpha * c[0][1] + beta * c[1][1] + gamma * c[2][1]) * 255);
					color[2] = u08((alpha * c[0][2] + beta * c[1][2] + gamma * c[2][2]) * 255);
					g_fb.setColor(int(x),int(y),color[0],color[1],color[2]);
				}
			}
		}
	}
}