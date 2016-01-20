#ifndef _STRUCTURES_WINDOWINFO_H
#define _STRUCTURES_WINDOWINFO_H

#include <string>

struct WindowInfo {
	std::string name;
	int width, height;
	int positionX, positionY;
	bool isReshapable;

	WindowInfo() {
		name = "OpenGL tutorial";
		width = 800; height = 600;
		positionX = 300;
		positionY = 300;
		isReshapable = true;
	}

	WindowInfo(std::string name, int startPositionX, int startPositionY, int width, int height, bool startIsReshapable) {
		this->name = name;
		this->positionX = startPositionX;
		this->positionY = startPositionY;
		this->width = width;
		this->height = height;
		this->isReshapable = startIsReshapable;
	}

	WindowInfo(const WindowInfo& w) {
		name = w.name;
		positionX = w.positionX;
		positionY = w.positionY;
		width = w.width;
		height = w.height;
		isReshapable = w.isReshapable;
	}

	void operator=(const WindowInfo& w) {
		name = w.name;
		positionX = w.positionX;
		positionY = w.positionY;
		width = w.width;
		height = w.height;
		isReshapable = w.isReshapable;
	}
};

#endif // !_STRUCTURES_WINDOWINFO_H
