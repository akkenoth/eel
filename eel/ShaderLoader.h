#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "Libs/glew/glew.h"
#include "Libs/freeglut/freeglut.h"

class ShaderLoader {
private:
	std::string readShader(char* filename);
	GLuint createShader(GLenum shaderType, std::string source, char* shaderName);
public:
	ShaderLoader();
	~ShaderLoader();
	GLuint createProgram(char* vertexShaderFilename, char* fragmentShaderFilename);
};