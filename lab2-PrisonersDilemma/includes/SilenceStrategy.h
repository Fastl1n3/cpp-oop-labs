#pragma once

#include "IStrategy.h"
//Молчать
class SilenceStrategy : public IStrategy
{
	const std::string name = "silence";
public:
	MoveResult run() override;
	void add_history(MoveResult s2, MoveResult s3) override {}
	const std::string& get_name() const  override;
};