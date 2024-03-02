#include "DefaultStrategy.h"

MoveResult DefaultStrategy::run() {
	return rand() % 2 == 0 ? MoveResult::Cooperate : MoveResult::Deceive;
}

const std::string& DefaultStrategy::get_name() const {
	return name;
}