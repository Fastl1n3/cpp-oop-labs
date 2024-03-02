#include "Parsing.h"

int main(int argc, char** argv) {
	srand(time(0));
	Parsing p;
	Game game;
	std::optional<ParserResult> pars_result = p.parse(argc, argv);
	if (pars_result) {
		game.start(*pars_result);
	}
	return 0;
}