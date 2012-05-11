#include "Scene.h"
#include "Rasterization.h"

#include "Values.h"
#include "glm\glm.hpp"

/* set the perspective projection matrix given the following values */
void setPerspectiveProjection(float eye_fov, float aspect_ratio, float near, float far) {
	glm::dmat4 Mat0(
		glm::dvec4(0.6f, 0.2f, 0.3f, 0.4f),
		glm::dvec4(0.2f, 0.7f, 0.5f, 0.3f),
		glm::dvec4(0.3f, 0.5f, 0.7f, 0.2f),
		glm::dvec4(0.4f, 0.3f, 0.2f, 0.6f));
	glm::dmat4 Inv0 = glm::inverse(Mat0);
	glm::dmat4 Res0 = Mat0 * Inv0;
}


/* set the modelview matrix with the given parameters */
void setModelviewMatrix(float *eye_pos, float eye_theta, float eye_phi) {

}

/* this implements the software rendering of the scene */ 
void Scene :: renderSceneSoftware(void) {

	/* this is the function you will write */


	return;
}