#include "AlTitForTatStrategy.h"

MoveResult AlTitForTatStrategy::run() {
	if (step == 0) {
		return MoveResult::Cooperate;
	}
	MoveResult s2 = history[step - 1].s2;
	MoveResult s3 = history[step - 1].s3;
	if (s2 == MoveResult::Cooperate && s3 == MoveResult::Cooperate) {
		return MoveResult::Cooperate;
	}
	if (s2 == MoveResult::Deceive && s3 == MoveResult::Deceive) {
		return MoveResult::Deceive;
	}
	if (step == 1) {
		return MoveResult::Cooperate;
	}
	if (s2 == MoveResult::Deceive && history[step - 2].s2 == MoveResult::Deceive || s3 == MoveResult::Deceive && history[step - 2].s3 == MoveResult::Deceive) {
		return MoveResult::Deceive;
	}
	if (s2 == MoveResult::Deceive && history[step - 2].s3 == MoveResult::Deceive || s3 == MoveResult::Deceive && history[step - 2].s2 == MoveResult::Deceive) {
		return MoveResult::Deceive;
	}
	return MoveResult::Cooperate;
}

void AlTitForTatStrategy::add_history(MoveResult s2, MoveResult s3) {
	step++;
	struct RoundHistory round;
	round.s2 = s2;
	round.s3 = s3;
	history.push_back(round);
}

const std::string& AlTitForTatStrategy::get_name() const {
	return name;
}