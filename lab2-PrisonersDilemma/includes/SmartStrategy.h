#pragma once

#include <vector>

#include "IStrategy.h"

class SmartStrategy : public IStrategy
{
	unsigned int step = 0;
	const std::string name = "smart";
	std::vector<struct RoundHistory> history;
	double balance = 0;
	double koef = 0.5;
public:
	MoveResult run() override;
	void add_history(MoveResult s2, MoveResult s3) override;
	const std::string& get_name() const  override;
};