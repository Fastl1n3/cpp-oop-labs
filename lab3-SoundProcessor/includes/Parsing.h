#pragma once

#include <vector>
#include <string>
#include <optional>
#include <fstream>

struct Action {
	std::string converter_name;
	unsigned int begin_time;
	unsigned int end_time;
	unsigned int additional_stream = 0;
};

struct ParserResult {
	std::ifstream cfg_file;
	std::ofstream output_file;
	std::vector<std::ifstream> input_files;
};

namespace Parsing {
	std::optional<ParserResult> parse_input(int argc, char** argv);
	std::optional<std::vector<Action>> parse_cfg(std::ifstream& cfg_file, const size_t count_in_files);
};

