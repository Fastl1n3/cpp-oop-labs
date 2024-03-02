#include "SmartStrategy.h"

#include <iostream>
#include <string>

MoveResult SmartStrategy::run() {
	if (step == 0) {
		return MoveResult::Cooperate;
	}
	MoveResult s2 = history[step - 1].s2;
	MoveResult s3 = history[step - 1].s3;
	if (s2 == MoveResult::Cooperate && s3 == MoveResult::Cooperate) {
		balance--;
		if (step != 1 && -balance / step > koef) {
			//std::cout << -balance / step << " |1|" << std::endl;
			balance = 0;
			koef -= 0.1;
			return MoveResult::Deceive;
		}
		return MoveResult::Cooperate;
	}
	if (s2 == MoveResult::Deceive && s3 == MoveResult::Deceive) {
		balance++;
		return MoveResult::Deceive;
	}
	if (step == 1) {
		balance++;
		return MoveResult::Cooperate;
	}
	if (s2 == MoveResult::Deceive && history[step - 2].s2 == MoveResult::Deceive || s3 == MoveResult::Deceive && history[step - 2].s3 == MoveResult::Deceive) {
		balance++;
		if (balance / step > koef+0.2) {
			//std::cout << balance / step << " |2|" << std::endl;
			balance = 0;
			koef -= 0.1;
			return MoveResult::Cooperate;
		}
		return MoveResult::Deceive;
	}
	if (s2 == MoveResult::Deceive && history[step - 2].s3 == MoveResult::Deceive || s3 == MoveResult::Deceive && history[step - 2].s2 == MoveResult::Deceive) {
		balance++;
		if (balance / step > koef) {
			//std::cout << balance / step << " |3|" << std::endl;
			balance = 0;
			koef -= 0.1;
			return MoveResult::Cooperate;
		}
		return MoveResult::Deceive;
	}
	balance--;
	if (-balance / step > koef) {
		//std::cout << -balance / step << " |4|" << std::endl;
		balance = 0;
		koef -= 0.1;
		return MoveResult::Deceive;
	}
	return MoveResult::Cooperate;
}

void SmartStrategy::add_history(MoveResult s2, MoveResult s3) {
	step++;
	struct RoundHistory round;
	round.s2 = s2;
	round.s3 = s3;
	history.push_back(round);
}

const std::string& SmartStrategy::get_name() const {
	return name;
}