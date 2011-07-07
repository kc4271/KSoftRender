#include <stdio.h>
#include "OpenGL.h"
#include "Scene.h"
#include "FrameBuffer.h"

Scene scene;
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr,"Usage: MazeViewer <file>\n");
		fprintf(stderr,"argc: %d\n", argc);
		return -1;
	}

	setDefaults();

	initGLUT(argc, argv);
	
	sceneCleanup();

	return 1;
}