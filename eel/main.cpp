#include <iostream>

#include "Libs/glew/glew.h"
#include "Libs/freeglut/freeglut.h"
#include "ShaderLoader.h"

GLuint program;

void init() {
	glEnable(GL_DEPTH_TEST);
	ShaderLoader loader;
	program = loader.createProgram("Shaders\\VertexShader.glsl", "Shaders\\FragmentShader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void renderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0, 0.0, 0.0, 1.0);

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawArrays(GL_TRIANGLES, 3, 3);
	glDrawArrays(GL_TRIANGLES, 6, 3);
	glDrawArrays(GL_TRIANGLES, 9, 3);

	glutSwapBuffers();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500); //optional
	glutInitWindowSize(800, 800); //optional
	glutCreateWindow("EEL");

	glewInit();

	init();

	glutDisplayFunc(renderScene);
	glutMainLoop();

	glDeleteProgram(program);

	return 0;
}