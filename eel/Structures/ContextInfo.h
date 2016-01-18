#pragma once

struct ContextInfo {
	int majorVersion;
	int minorVersion;
	bool core;

	ContextInfo() {
		majorVersion = 4;
		minorVersion = 1;
		core = true;
	}

	ContextInfo(int majorVersion, int minorVersion, bool core) {
		this->majorVersion = majorVersion;
		this->minorVersion = minorVersion;
		this->core = core;
	}

	ContextInfo(const ContextInfo& c) {
		majorVersion = c.majorVersion;
		minorVersion = c.minorVersion;
		core = c.core;
	}

	void operator=(const ContextInfo& c) {
		majorVersion = c.majorVersion;
		minorVersion = c.minorVersion;
		core = c.core;
	}
};