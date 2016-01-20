#ifndef _STRUCTURES_BMPHEADER_H
#define _STRUCTURES_BMPHEADER_H

#include <string>
#include <fstream>

struct BMPHeader {
	uint16_t type;
	uint32_t fileSize;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t offsetBits;

	void readFromFile(std::ifstream& file) {
		file.read((char*) &type, 2);
		file.read((char*) &fileSize, 4);
		file.read((char*) &reserved1, 2);
		file.read((char*) &reserved2, 2);
		file.read((char*) &offsetBits, 4);
	}
};

struct BMPHeaderInfo {
	uint32_t headerSize;
	uint32_t width;
	uint32_t height;
	uint16_t planesCount;
	uint16_t bitPerPixelCount;
	uint32_t compression;
	uint32_t bitmapSize;
	uint32_t ppmHorizontal;
	uint32_t ppmVertical;
	uint32_t colorsCount;
	uint32_t importantColorsCount;

	void readFromFile(std::ifstream& file) {
		file.read((char*) &headerSize, 4);
		file.read((char*) &width, 4);
		file.read((char*) &height, 4);
		file.read((char*) &planesCount, 2);
		file.read((char*) &bitPerPixelCount, 2);
		file.read((char*) &compression, 4);
		file.read((char*) &bitmapSize, 4);
		file.read((char*) &ppmHorizontal, 4);
		file.read((char*) &ppmVertical, 4);
		file.read((char*) &colorsCount, 4);
		file.read((char*) &importantColorsCount, 4);
	}
};

#endif // !_STRUCTURES_BMPHEADER_H
