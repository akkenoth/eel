#include "ShaderManager.h"

std::map<std::string, GLuint> ShaderManager::programs;

ShaderManager::ShaderManager() {}
ShaderManager::~ShaderManager() {
	for(std::map<std::string, GLuint>::iterator i = programs.begin(); i != programs.end(); ++i) {
		GLuint p = i->second;
		glDeleteProgram(p);
	}
	programs.clear();
}

std::string ShaderManager::readShader(const std::string& filename) {
	std::string shaderCode;
	std::ifstream file(filename, std::ios::in);
	if(!file.good()) {
		std::cout << "ERROR reading shader: " << filename.c_str() << "\n";
		std::terminate();
	}
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

GLuint ShaderManager::createShader(GLenum shaderType, const std::string& source, const std::string& shaderName) {
	const char *codePointer = source.c_str();
	const int codeSize = source.size();
	GLuint shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &codePointer, &codeSize);
	glCompileShader(shader);
	int result = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)	{
		int logLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> log(logLength);
		glGetShaderInfoLog(shader, logLength, NULL, &log[0]);
		std::cout << "ERROR compiling shader: " << shaderName.c_str() << "\n" << &log[0] << "\n";
		return 0;
	}
	return shader;
}

void ShaderManager::createProgram(const std::string& shaderName, const std::string& vertexShaderFilename, const std::string& fragmentShaderFilename) {
	if(programs.find(shaderName) != programs.end()) {
		std::cout << "Shader program named " << shaderName.c_str() << " already exists.\n";
		return;
	}

	std::string vertex_shader_code = readShader(vertexShaderFilename);
	std::string fragment_shader_code = readShader(fragmentShaderFilename);
	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, vertex_shader_code, "vertex shader");
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, fragment_shader_code, "fragment shader");

	//create the program handle, attatch the shaders and link it
	GLuint program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);
	int result = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result  == GL_FALSE) {
		int logLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
		std::vector<char> log(logLength);
		glGetProgramInfoLog(program, logLength, NULL, &log[0]);
		std::cout << "ERROR linking shader.\n" << &log[0] << "\n";
		return;
	}

	programs[shaderName] = program;
}

const GLuint ShaderManager::getProgram(const std::string& shaderName) {
	try {
		return programs.at(shaderName);
	} catch(std::string e) {
		std::cout << "Shader program named " << shaderName.c_str() << " does not exists.\n";
		return GL_FALSE;
	}
}

void ShaderManager::deleteProgram(const std::string& shaderName) {
	std::map<std::string, GLuint>::iterator i;
	i = programs.find(shaderName);
	if(i == programs.end()) {
		return;
	}

	GLuint p = i->second;
	glDeleteProgram(p);
	programs.erase(i);
}