#include "SilenceStrategy.h"

MoveResult SilenceStrategy::run() {
	return MoveResult::Cooperate;
}

const std::string& SilenceStrategy::get_name() const {
	return name;
}