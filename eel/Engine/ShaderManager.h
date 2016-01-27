#ifndef _ENGINE_SHADERMANAGER_H
#define _ENGINE_SHADERMANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdexcept>

#include "../Libs/GLWrapper.h"

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif // !M_PI

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
