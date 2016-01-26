#ifndef _ENGINE_INPUTMANAGER_H
#define _ENGINE_INPUTMANAGER_H

#include "../Libs/glutWrapper.h"
#include "../Structures/WindowInfo.h"

class InputManager {
private:
	bool keyMap[256];
	bool specialKeyMap[32];
	int mouseMovementX;
	int mouseMovementY;
	bool mouseCapture;
	WindowInfo* window;
public:
	InputManager();
	~InputManager();

	void setWindowInfo(WindowInfo* info);

	void setKeyDown(unsigned char code);
	void setKeyUp(unsigned char code);
	void setSpecialKeyDown(int code);
	void setSpecialKeyUp(int code);

	void addMouseMovement(int x, int y);
	void clearMouseMovement();
	void toggleMouseCapture();

	bool getKeyState(unsigned char code) const;
	bool getSpecialKeyState(int code) const;
	int getMouseMovementX() const;
	int getMouseMovementY() const;
};

#endif