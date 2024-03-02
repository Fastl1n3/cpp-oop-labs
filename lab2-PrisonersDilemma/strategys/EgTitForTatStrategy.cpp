#include "EgTitForTatStrategy.h"

MoveResult EgTitForTatStrategy::run() {
	if (step == 0) {
		return MoveResult::Cooperate;
	}
	MoveResult s2 = history[step - 1].s2;
	MoveResult s3 = history[step - 1].s3;
	if (s2 == MoveResult::Cooperate && s3 == MoveResult::Cooperate) {
		return MoveResult::Cooperate;
	}
	return MoveResult::Deceive;
}

void EgTitForTatStrategy::add_history(MoveResult s2, MoveResult s3) {
	step++;
	struct RoundHistory round;
	round.s2 = s2;
	round.s3 = s3;
	history.push_back(round);
}

const std::string& EgTitForTatStrategy::get_name() const {
	return name;
}