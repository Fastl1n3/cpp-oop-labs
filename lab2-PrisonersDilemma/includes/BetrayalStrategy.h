#pragma once

#include "IStrategy.h"

class BetrayalStrategy : public IStrategy
{
	const std::string name = "betrayal";
public:
	MoveResult run() override;
	void add_history(MoveResult s2, MoveResult s3)  override {}
	const std::string& get_name() const  override;
};