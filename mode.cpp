#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "mode.h"

int set_mode(int argc, char** argv) {
	if (argc != 3) return 0;

	std::string flag{ argv[1] },
				mode{ argv[2] };

	if (flag != "-mode") return 0;

	if (mode == "FilePointer") return 1;
	if (mode == "FileStream") return 2;

	return 0;
}