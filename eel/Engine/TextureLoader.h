#ifndef _ENGINE_TEXTURELOADER_H
#define _ENGINE_TEXTURELOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include "../Libs/glewWrapper.h"
#include "../Structures/BMPHeader.h"

class TextureLoader {
private:
	void loadBMPTexture(const std::string& filename, unsigned int& width, unsigned int& height, unsigned char*& data);
public:
	TextureLoader();
	~TextureLoader();

	GLuint loadTexture(const std::string& filename, unsigned int width, unsigned int height);
};

#endif // !_ENGINE_TEXTURELOADER_H
