#include "InputManager.h"

InputManager::InputManager() {
	for(int i = 0; i < 256; i++) {
		keyMap[i] = false;
	}
	for(int i = 0; i < 32; i++) {
		specialKeyMap[i] = false;
	}
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
	}
	clearMouseMovement();
}

bool InputManager::getKeyState(unsigned char code) const {
	return keyMap[code];
}

bool InputManager::getSpecialKeyState(int code) const {
	if(code < 0 || code > 32) {
		return false;
	}
	return specialKeyMap[code];
}

int InputManager::getMouseMovementX() const {
	return mouseMovementX;
}

int InputManager::getMouseMovementY() const {
	return mouseMovementY;
}
