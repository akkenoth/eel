#include "TextureLoader.h"

TextureLoader::TextureLoader() {}
TextureLoader::~TextureLoader() {}

void TextureLoader::loadBMPTexture(std::ifstream& textureFile, unsigned int & width, unsigned int & height, unsigned char *& data) {
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
			// Reverse BGR[A] from BMP into RGBA
			data[p++] = rowData[byteness * j + 2];
			data[p++] = rowData[byteness * j + 1];
			data[p++] = rowData[byteness * j];
			if(byteness == 4) {
				// If 32bit, read 4 bytes and just reverse order
				data[p++] = rowData[byteness * j + 3];
			} else {
				// If 24bit, read 3 bytes and 255 (max) to alpha channel
				data[p++] = 255;
			}
		}
	}
}

void readPNGData(png_structp png_ptr, png_bytep data, png_size_t length) {
	std::istream* file = (std::istream*) png_get_io_ptr(png_ptr);
	file->read((char*) data, length);
}

void TextureLoader::loadPNGTexture(std::ifstream& textureFile, unsigned int& width, unsigned int& height, unsigned char*& data) {
	// Read and validate header
	png_byte header[8];
	textureFile.read((char*) header, 8);
	if (png_sig_cmp(header, 0, 8)) {
		return;
	}

	// Create PNG structs
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		return;
	}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
		return;
	}
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info) {
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
		return;
	}

	// PNG error handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return;
	}

	// Setup stream read function
	png_set_read_fn(png_ptr, (png_voidp)& textureFile, readPNGData);
	
	// Read PNG info
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);

	png_set_strip_16(png_ptr);
	png_set_expand_gray_1_2_4_to_8(png_ptr);
	png_set_palette_to_rgb(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(png_ptr);
	}
	png_read_update_info(png_ptr, info_ptr);
	
	int channels = png_get_channels(png_ptr, info_ptr);
	if(channels != 4) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return;
	}
	width =  png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);

	// Allocate memory for data
	int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	data = new unsigned char[rowbytes * height];
	png_bytep *row_pointers = new png_bytep[height];
	if (!data || !row_pointers) {
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return;
	}

	// Set up row_pointers to point at the correct offsets of data[]
	for(unsigned int i = 0; i < height; ++i) {
		//row_pointers[height - 1 - i] = data + i * rowbytes; // same thing
		row_pointers[i] = data + (height - 1 - i) * rowbytes;
	}

	// Read the data
	png_read_image(png_ptr, row_pointers);
}

GLuint TextureLoader::loadTexture(const std::string & filename) {
	unsigned char* data = NULL;
	if(filename.length() < 5) {
		return 0;
	}

	std::string extension = filename.substr(filename.length() - 3, 3);
	bool isPNG = false;
	bool isBMP = false;
	if(extension.compare("png") == 0) {
		isPNG = true;
	} else if(extension.compare("bmp") == 0) {
		isBMP = true;
	} else {
		std::cout << "Texture loading error: Bad file extension!\n";
		return 0;
	}

	std::ifstream textureFile(filename.c_str(), std::ios::in | std::ios::binary);
	if(!textureFile.good()) {
		std::cout << "Texture loading error: File not good!\n";
		return 0;
	}

	unsigned int width = 0;
	unsigned int height = 0;
	if(isPNG && !isBMP) {
		loadPNGTexture(textureFile, width, height, data);
	} else if(isBMP && !isPNG) {
		loadBMPTexture(textureFile, width, height, data);
	} else {
		return 0;
	}
	textureFile.close();
	
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
