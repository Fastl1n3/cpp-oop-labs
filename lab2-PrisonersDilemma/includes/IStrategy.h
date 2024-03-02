#pragma once

#include <string>

enum class MoveResult {
	Cooperate,
	Deceive
};

struct RoundHistory {
	MoveResult s2;
	MoveResult s3;
};

class IStrategy {
public:
	virtual ~IStrategy() = default;

	virtual MoveResult run() = 0;
	virtual void add_history(MoveResult s2, MoveResult s3) = 0;
	virtual const std::string& get_name() const = 0;
};