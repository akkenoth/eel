#pragma once

class GLUTListener {
public:
	virtual ~GLUTListener() = 0;

	virtual void notifyFrameBegin() = 0;
	virtual void notifyFrameDisplay() = 0;
	virtual void notifyFrameEnd() = 0;
	virtual void notifyReshape(int width, int height, int previousWidth, int previousHeight) = 0;
};

inline GLUTListener::~GLUTListener() {}