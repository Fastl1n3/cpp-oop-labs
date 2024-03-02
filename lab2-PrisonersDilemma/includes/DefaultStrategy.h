#pragma once

#include "IStrategy.h"

class DefaultStrategy : public IStrategy
{
	const std::string name = "default";
public:
	MoveResult run() override;
	void add_history(MoveResult s2, MoveResult s3) override {}
	const std::string& get_name() const  override;
};