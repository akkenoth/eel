#ifndef _ENGINE_DEBUGOUTPUT_H
#define _ENGINE_DEBUGOUTPUT_H

#include <iostream>
#include <assert.h>
#include "../Libs/GLWrapper.h"

class DebugOutput {
private:
	static std::string getTypeString(GLenum type);
	static std::string getSourceString(GLenum source);
	static std::string getSeverityString(GLenum severity);
public:
	DebugOutput();
	~DebugOutput();
	static void printDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *msg, const void* userParam);
};

#endif // !_ENGINE_DEBUGOUTPUT_H
