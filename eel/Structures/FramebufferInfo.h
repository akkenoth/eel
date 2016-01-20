#ifndef _STRUCTURES_FRAMEBUFFERINFO_H
#define _STRUCTURES_FRAMEBUFFERINFO_H

#include "../Libs/GLWrapper.h"

struct FramebufferInfo {
	GLuint flags;
	bool msaa;

	FramebufferInfo() {
		flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
		msaa = false;
	}

	FramebufferInfo(bool color, bool depth, bool stencil, bool msaa) {
		flags = GLUT_DOUBLE;
		if(color) {
			flags |= GLUT_RGBA | GLUT_ALPHA;
		}
		if(depth) {
			flags |= GLUT_DEPTH;
		}
		if(stencil) {
			flags |= GLUT_STENCIL;
		}
		if(msaa) {
			flags |= GLUT_MULTISAMPLE;
		}

		this->msaa = msaa;
	}

	FramebufferInfo(const FramebufferInfo& f) {
		flags = f.flags;
		msaa = f.msaa;
	}

	void operator=(const FramebufferInfo& f) {
		flags = f.flags;
		msaa = f.msaa;
	}
};

#endif // !_STRUCTURES_FRAMEBUFFERINFO_H
