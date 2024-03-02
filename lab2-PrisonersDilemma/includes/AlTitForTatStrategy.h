#pragma once

#include <vector>

#include "IStrategy.h"

class AlTitForTatStrategy : public IStrategy
{
	unsigned int step = 0;
	const std::string name = "a_titfortat";
	std::vector<struct RoundHistory> history;
public:
	MoveResult run() override;
	void add_history(MoveResult s2, MoveResult s3) override;
	const std::string& get_name() const  override;
};