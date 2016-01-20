#ifndef _ENGINE_SHADERMANAGER_H
#define _ENGINE_SHADERMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#include "../Libs/GLWrapper.h"

class ShaderManager {
private:
	static std::map<std::string, GLuint> programs;

	std::string readShader(const std::string& filename);
	GLuint createShader(GLenum shaderType, const std::string& source, const std::string& shaderName);
public:
	ShaderManager();
	~ShaderManager();
	void createProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename);
	static const GLuint getProgram(const std::string&);
	void deleteProgram(const std::string& shaderName);
};

#endif // !_ENGINE_SHADERMANAGER_H
