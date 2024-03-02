#include "Parsing.h"

std::optional<ParserResult> Parsing::parse(int argc, char** argv) {
	ParserResult res;
	if (argc < 4) {
		if (argc == 1 || std::string(argv[1]) == "--help") {
			std::cout << "============================================================================================================================" << std::endl;
			std::cout << "For starting use: ./lab2-PrisonersDilemma <NameStrategy1> ... <NameStrategyN> --mode=[detailed|fast|tournament] --steps=<n>" << std::endl;
			std::cout << "If mode = fast or detailed, the number of strategies should be equal 3,\nfor tournament - be equal >= 3" << std::endl;
			std::cout << "You don't need a key \"--steps\" for a \"detailed\" mode" << std::endl;
			std::cout << "Available strategies: \"default\", \"silence\", \"betrayal\", \"a_titfortat\", \"e_titfortat\", \"smart\"." << std::endl;
			std::cout << "============================================================================================================================" << std::endl;
			return std::nullopt;
		}
		std::cout << "Not enough arguments, use the --help" << std::endl;
		return std::nullopt;
	}
	int i = 1;
	while (i != argc && argv[i][0] != '-') {
		res.strategies.push_back(argv[i]);
		i++;
	}
	if (i == argc) {
		if (argc == 4) {
			std::cout << "Load detailed game by default" << std::endl;
			res.mode = Mode::Detailed;
		}
		else {
			std::cout << "Load tournament with 10 steps by default" << std::endl;
			res.mode = Mode::Tournament;
		}
	}
	else {
		if (std::string(argv[i]) == "--mode=detailed") {
			if (res.strategies.size() != 3) {
				std::cout << "The number of strategies should be equal 3." << std::endl;
				return std::nullopt;
			}
			res.mode = Mode::Detailed;
		}
		else if (std::string(argv[i]) == "--mode=fast") {
			try {
				if (i + 1 == argc) {
					throw std::invalid_argument("Not argument of steps");
				}
				std::string num = std::string(argv[i + 1]).substr(8);
				res.steps = stoi(num);
				res.mode = Mode::Fast;
			}
			catch (std::invalid_argument e) {
				std::cout << "Invalid argument of steps" << std::endl;
			}
		}
		else if (std::string(argv[i]) == "--mode=tournament") {
			try {
				if (i + 1 == argc) {
					throw std::invalid_argument("Not argument of steps");
				}
				std::string num = std::string(argv[i + 1]).substr(8);
				res.steps = stoi(num);
				res.mode = Mode::Tournament;
			}
			catch (std::invalid_argument e) {
				std::cout << "Invalid argument of steps" << std::endl;
			}
		}
		else {
			std::cout << "Invalid argument of mode" << std::endl;
			return std::nullopt;
		}
	}
	return res;
}