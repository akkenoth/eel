#include "InputManager.h"
#include <iostream>

InputManager::InputManager() {
	for(bool k : keyMap) {
		k = false;
	}
	for(bool k : specialKeyMap) {
		k = false;
	}
}

InputManager::~InputManager() {}

void InputManager::setKeyDown(unsigned char code) {
	if(code >= 'A' && code <= 'Z') {
		code -= ('A' - 'a');
	}
	keyMap[code] = true;
	mouseMovementX = 0;
	mouseMovementY = 0;
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
	std::cout << "adding mouse movement:" << x << " " << y << "\n";
	mouseMovementX += x;
	mouseMovementY += y;
}

void InputManager::clearMouseMovement() {
	mouseMovementX = 0;
	mouseMovementY = 0;
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
