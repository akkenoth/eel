#include "InputManager.h"

InputManager::InputManager() {
	mouseCapture = false;
	mouseMovementX = 0;
	mouseMovementY = 0;
}

InputManager::~InputManager() {}

void InputManager::setWindowInfo(WindowInfo * info) {
	window = info;
}

void InputManager::setKeyDown(unsigned char code) {
	if(code >= 'A' && code <= 'Z') {
		code -= ('A' - 'a');
	}
	keyMap[code] = true;
}

void InputManager::setKeyUp(unsigned char code) {
	if(code >= 'A' && code <= 'Z') {
		code -= ('A' - 'a');
	}
	keyMap[code] = false;
}

void InputManager::setSpecialKeyDown(int code) {
	specialKeyMap[code] = true;
}

void InputManager::setSpecialKeyUp(int code) {
	specialKeyMap[code] = false;
}

void InputManager::addMouseMovement(int x, int y) {
	if(!mouseCapture) {
		return;
	}

	int halfX = window->width / 2;
	int halfY = window->height / 2;
	int deltaX = x - halfX;
	int deltaY = y - halfY;
	mouseMovementX += deltaX;
	mouseMovementY += deltaY;

	if(deltaX != 0 || deltaY != 0) {
		glutWarpPointer(halfX, halfY);
	}
}

void InputManager::clearMouseMovement() {
	mouseMovementX = 0;
	mouseMovementY = 0;
}

void InputManager::toggleMouseCapture() {
	if(mouseCapture) {
		mouseCapture = false;
		glutSetCursor(GLUT_CURSOR_INHERIT);
	} else {
		mouseCapture = true;
		glutSetCursor(GLUT_CURSOR_NONE);
		glutWarpPointer(window->width / 2, window->height / 2);
	}
	clearMouseMovement();
}

bool InputManager::getKeyState(unsigned char code) {
	try {
		return keyMap.at(code);
	} catch(const std::out_of_range& e) {
		keyMap[code] = false;
		return false;
	}
}

bool InputManager::getSpecialKeyState(int code) {
	try {
		return specialKeyMap.at(code);
	} catch(const std::out_of_range& e) {
		specialKeyMap[code] = false;
		return false;
	}
}

int InputManager::getMouseMovementX() const {
	return mouseMovementX;
}

int InputManager::getMouseMovementY() const {
	return mouseMovementY;
}
