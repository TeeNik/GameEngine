#pragma once
#include <string>

class Utils {

public:
	static std::string ContructPath(std::string name) {
		return "../Solution/Assets/" + name;
	}
};