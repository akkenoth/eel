#include "TextureLoader.h"

TextureLoader::TextureLoader() {}
TextureLoader::~TextureLoader() {}

void TextureLoader::loadBMPTexture(const std::string & filename, unsigned int & width, unsigned int & height, unsigned char *& data) {
	std::ifstream textureFile(filename.c_str(), std::ios::in | std::ios::binary);
	if(!textureFile.good()) {
		std::cout << "File not good!\n";
		width = 0;
		height = 0;
		data = NULL;
		return;
	}

	BMPHeader header;
	BMPHeaderInfo headerInfo;
	header.readFromFile(textureFile);
	headerInfo.readFromFile(textureFile);

	if(headerInfo.bitPerPixelCount != 24 && headerInfo.bitPerPixelCount != 32) {
		std::cout << "Texture not 24bpp but " << headerInfo.bitPerPixelCount << "\n";
		width = 0;
		height = 0;
		data = NULL;
		return;
	}

	width = headerInfo.width;
	height = headerInfo.height;
	unsigned int byteness = headerInfo.bitPerPixelCount / 8;

	// Reserve data for RGBA
	data = new unsigned char[width * height * 4];
	unsigned long linePadding = (4 - (width * byteness % 4))%4;
	unsigned long rowWidth = width * byteness + linePadding;
	unsigned char* rowData = new unsigned char[rowWidth];
	for(unsigned int i = 0; i < height; i++) {
		textureFile.read((char*) rowData, rowWidth);
		unsigned long p = i * width * 4;
		for(unsigned int j = 0; j < width; j++) {
			// Reverse [A]BGR from BMP into RGBA
			if(byteness == 4) {
				// If 32bit, read 4 bytes and just reverse order
				data[p++] = rowData[byteness * j + 3];
			}
			data[p++] = rowData[byteness * j + 2];
			data[p++] = rowData[byteness * j + 1];
			data[p++] = rowData[byteness * j];
			if(byteness == 3) {
				// If 24bit, read 3 bytes and 255 (max) to alpha channel
				data[p++] = 255;
			}
		}
	}

	textureFile.close();
}

GLuint TextureLoader::loadTexture(const std::string & filename, unsigned int width, unsigned int height) {
	unsigned char* data;
	loadBMPTexture(filename, width, height, data);
	if(data == NULL) {
		return 0;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	GLfloat maxAnisotropy = 1.0;
	glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropy);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAnisotropy);

	// Not needed after adding alpha byte - natural alignment to 4 bytes
	// glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	delete data;
	return texture;
}
