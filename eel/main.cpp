#include <iostream>

#include "Libs/glew/glew.h"
#include "Libs/freeglut/freeglut.h"
#include "ShaderManager.h"
#include "Models.h"

GLuint program;
Models* models;
ShaderManager* manager;

void init() {
	glEnable(GL_DEPTH_TEST);
	models = new Models();
	models->createTriangleModel("testTriangle");

	manager = new ShaderManager();
	manager->createProgram("simpleColorShader", "Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");

	program = ShaderManager::getShader("simpleColorShader");
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

	glutInitContextVersion(4, 1);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutCreateWindow("EEL");

	glewExperimental = true;
	glewInit();
	if(glewIsSupported("GL_VERSION_4_1")) {
		std::cout << "OpenGL version 4.1 supported.\n";
	} else {
		std::cout << "OpenGL version 4.1 NOT supported.\n";
	}

	init();
	glutDisplayFunc(renderScene);
	glutCloseFunc(close);
	glutMainLoop();

	delete models;
	delete manager;
	return 0;
}