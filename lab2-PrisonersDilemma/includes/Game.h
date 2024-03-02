#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "IStrategy.h"
#include "Factory.h"
#include "Parsing.h"

class Game {
	Factory factory;
	int points_s1 = 0;
	int points_s2 = 0;
	int points_s3 = 0;
	std::map<std::string, std::string> points_map = {{ "000", "777" },
													 { "001", "339" },
													 { "010", "393" },
													 { "100", "933" },
													 { "011", "055" },
													 { "101", "505" },
													 { "110", "550" },
													 { "111", "111" }};
	void get_points(const MoveResult s1, const MoveResult s2, const MoveResult s3);
	void add_move(std::shared_ptr<IStrategy> s1, std::shared_ptr<IStrategy> s2, std::shared_ptr<IStrategy> s3, const MoveResult choice1, const MoveResult choice2, const MoveResult choice3);
	void registration();
	void detailed(const std::string& name1, const std::string& name2, const std::string& name3);
	void fast(const std::string& name1, const std::string& name2, const std::string& name3, const int steps);
	void tournament(const std::vector<std::string>& strategies, const int steps);
public:
	Game();
	void start(const struct ParserResult res);
};