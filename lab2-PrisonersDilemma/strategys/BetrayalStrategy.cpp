#include "BetrayalStrategy.h"
//Предать
MoveResult BetrayalStrategy::run() {
	return MoveResult::Deceive;
}

const std::string& BetrayalStrategy::get_name() const {
	return name;
}