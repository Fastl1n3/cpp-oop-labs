#include "Parsing.h"

#include <climits>
#include <cstring>
#include <iostream>

std::optional<ParserResult> Parsing::parse_input(int argc, char** argv) {
	ParserResult res;
	if (argc == 1) {
		std::cout << "Use [-h] key for help." << std::endl;
		return std::nullopt;
	}
	if (std::string(argv[1]) == "-h") {
		std::cout << "============================================================================================================================" << std::endl;
		std::cout << "For starting use: ./lab3-SoundProcessor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> ...]" << std::endl;
		std::cout << "The program has 3 converters:" << std::endl;
		std::cout << "1) Muting. It mutes the sound in the interval, has 2 parametres: start and end of the time interval (in seconds)." << std::endl;
		std::cout << "   Syntax in the config: mute <start_time(sec)> <end_time(sec)>" << std::endl;
		std::cout << "2) Mixer. Each output sample is the average of the samples of the input streams, has 2 parametres:" << std::endl;
		std::cout << "   additional stream and insertion location (in seconds, 0 by default)." << std::endl;
		std::cout << "   Syntax in the config: mix $<N>(link on inputN.wav) <insertion location(sec)>" << std::endl;
		std::cout << "3) Second-by-second reversal. It revers the seconds in the interval, has 2 parametres: start and end of the time interval (in seconds)." << std::endl;
		std::cout << "   Syntax in the config: rev <start_time(sec)> <end_time(sec)>" << std::endl;
		std::cout << "============================================================================================================================" << std::endl;
		return std::nullopt;
	}
	if (std::string(argv[1]) != "-c") {
		std::cout << "Error. Use the key [-c]" << std::endl;
		return std::nullopt;
	}
	if (argc < 5) {
		std::cout << "Not enough arguments, use the [-h]" << std::endl;
		return std::nullopt;
	}
	std::ifstream cfg;
	cfg.open(argv[2], std::ios::in);
	if (!cfg.is_open()) {
		std::cout << "Cannot open the file \"" << std::string(argv[2]) << "\"" << std::endl;
		return std::nullopt;
	}
	res.cfg_file = std::move(cfg);
	std::ofstream out;
	out.open(argv[3], std::ios::binary);
	res.output_file = std::move(out);
	for (int i = 4; i < argc; i++) {
		std::ifstream tmp;
		tmp.open(argv[i], std::ios::binary);
		if (!tmp.is_open()) {
			std::cout << "Cannot open the file \"" << std::string(argv[i]) << "\"" << std::endl;
			return std::nullopt;
		}
		res.input_files.push_back(std::move(tmp));
	}
	return res;
}

std::optional<std::vector<Action>> Parsing::parse_cfg(std::ifstream& cfg_file, const size_t count_in_files) {
	std::string buff;
	std::vector<Action> res;
	std::string conv_name;
	while (getline(cfg_file, buff)) {
		size_t len = buff.length();
		if (len == 0) {
			std::cout << "Empty line in the config file" << std::endl;
			return std::nullopt;
		}
		Action a;
		if (buff[0] == '#') {
			continue;
		}
		int i = 0;
		while (buff[i] != ' ') {
			a.converter_name.push_back(buff[i]);
			i++;
			if (i == len) {
				std::cout << "Not enough arguments in the config file" << std::endl;
				return std::nullopt;
			}
		}
		i++;
		bool link = false;
		std::string num_str;
		while (buff[i] != ' ') {
			if (buff[i] == '$') {
				if (link == false) {
					link = true;
					i++;
					continue;
				}
				else {
					std::cout << "Invalid syntax in the config file" << std::endl;
					return std::nullopt;
				}
			}
			if (buff[i] < '0' || buff[i] > '9') {
				std::cout << "Invalid syntax in the config file" << std::endl;
				return std::nullopt;
			}
			num_str.push_back(buff[i]);
			i++;
			if (i == len) {
				std::cout << "Not enough arguments in the config file" << std::endl;
				return std::nullopt;
			}
		}
		i++;
		int num = stoi(num_str);
		if (link == true) {
			if (num == 0) {
				std::cout << "Additional stream cannot be 0" << std::endl;
				return std::nullopt;
			}
			if (num > count_in_files) {
				std::cout << "Additional stream cannot be more than the number of all files" << std::endl;
				return std::nullopt;
			}
			a.additional_stream = num;
		}
		else {
			a.begin_time = num;
		}
		num_str.clear();
		num = 0;
		if (i == len) {
			std::cout << "Not enough arguments in the config file" << std::endl;
			return std::nullopt;
		}
		for (i; i < len; i++) {
			if (buff[i] < '0' || buff[i] > '9') {
				std::cout << "Invalid syntax in the config file" << std::endl;
				return std::nullopt;
			}	
			num_str.push_back(buff[i]);
		}
		num = stoi(num_str);
		if (link == true) {
			a.begin_time = num;
			a.end_time = UINT_MAX;
		}
		else {
			a.end_time = num;
			if (a.end_time <= a.begin_time) {
				std::cout << "End time cannot be more than start time" << std::endl;
				return std::nullopt;
			}
		}
		res.push_back(a);
	}
	return res;
}