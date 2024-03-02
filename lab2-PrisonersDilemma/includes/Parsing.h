#pragma once

#include <vector>
#include <string>
#include <optional>

#include "Game.h"

enum class Mode {
	Fast,
	Detailed,
	Tournament,
};

struct ParserResult {
	std::vector<std::string> strategies;
	unsigned int steps = 10;
	Mode mode;
};

class Parsing {
public:
	std::optional<ParserResult> parse(int argc, char** argv);
};


