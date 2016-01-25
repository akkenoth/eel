#ifndef _ENGINE_INPUTMANAGER_H
#define _ENGINE_INPUTMANAGER_H

class InputManager {
private:
	bool keyMap[256];
	bool specialKeyMap[32];
	int mouseMovementX;
	int mouseMovementY;
public:
	InputManager();
	~InputManager();

	void setKeyDown(unsigned char code);
	void setKeyUp(unsigned char code);
	void setSpecialKeyDown(int code);
	void setSpecialKeyUp(int code);

	void addMouseMovement(int x, int y);
	void clearMouseMovement();

	bool getKeyState(unsigned char code) const;
	bool getSpecialKeyState(int code) const;
	int getMouseMovementX() const;
	int getMouseMovementY() const;
};

#endif