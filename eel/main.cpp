#include <iostream>

#include "Libs/glew/glew.h"
#include "Libs/freeglut/freeglut.h"
#include "ShaderLoader.h"
#include "Models.h"

GLuint program;
Models* models;

void init() {
	glEnable(GL_DEPTH_TEST);
	models = new Models();
	models->createTriangleModel("testTriangle");

	ShaderLoader loader;
	program = loader.createProgram("Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void close() {
	glutLeaveMainLoop();
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);
	glBindVertexArray(models->getModel("testTriangle"));

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500); //optional
	glutInitWindowSize(800, 800); //optional
	glutCreateWindow("EEL");

	glewInit();
	if(glewIsSupported("GL_VERSION_4_1")) {
		std::cout << "OpenGL version 4.1 supported.\n";
	} else {
		std::cout << "OpenGL version 4.1 NOT supported.\n";
	}
	std::cout << "offset of color in VF:" << offsetof(VertexFormat, VertexFormat::color) << "\n";

	init();
	glutDisplayFunc(renderScene);
	glutCloseFunc(close);
	glutMainLoop();

	delete models;
	glDeleteProgram(program);
	return 0;
}