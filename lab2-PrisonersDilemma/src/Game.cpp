#include "Game.h"
#include "SilenceStrategy.h"
#include "DefaultStrategy.h"
#include "BetrayalStrategy.h"
#include "AlTitForTatStrategy.h"
#include "EgTitForTatStrategy.h"
#include "SmartStrategy.h"

Game::Game() {
	registration();
}

void Game::start(const struct ParserResult res) {
	switch (res.mode) {
	case Mode::Detailed:
		detailed(res.strategies[0], res.strategies[1], res.strategies[2]);
		break;
	case Mode::Fast:
		fast(res.strategies[0], res.strategies[1], res.strategies[2], res.steps);
		break;
	case Mode::Tournament:
		tournament(res.strategies, res.steps);
		break;
	}
}

void Game::get_points(const MoveResult choice1, const MoveResult choice2, const MoveResult choice3) {
	char c1 = static_cast<char>(choice1) + '0';
	char c2 = static_cast<char>(choice2) + '0';
	char c3 = static_cast<char>(choice3) + '0';
	std::string str = {c1, c2, c3};
	auto it = points_map.find(str);
	points_s1 += it->second[0] - '0';
	points_s2 += it->second[1] - '0';
	points_s3 += it->second[2] - '0';
}

void Game::add_move(std::shared_ptr<IStrategy> s1, std::shared_ptr<IStrategy> s2, std::shared_ptr<IStrategy> s3,const MoveResult choice1, const MoveResult choice2, const MoveResult choice3) {
	s1->add_history(choice2, choice3);
	s2->add_history(choice1, choice3);
	s3->add_history(choice1, choice2);
	get_points(choice1, choice2, choice3);
}

void Game::registration() {
	factory.register_creator("default", std::make_shared<Creator<DefaultStrategy>>());
	factory.register_creator("silence", std::make_shared<Creator<SilenceStrategy>>());
	factory.register_creator("betrayal", std::make_shared<Creator<BetrayalStrategy>>());
	factory.register_creator("a_titfortat", std::make_shared<Creator<AlTitForTatStrategy>>());
	factory.register_creator("e_titfortat", std::make_shared<Creator<EgTitForTatStrategy>>());
	factory.register_creator("smart", std::make_shared<Creator<SmartStrategy>>());
}

void Game::detailed(const std::string& name1, const std::string& name2, const std::string& name3) {
	try {
		auto s1 = factory.create(name1);
		auto s2 = factory.create(name2);
		auto s3 = factory.create(name3);
		if (s1 == nullptr || s2 == nullptr || s3 == nullptr) {
			throw std::invalid_argument("Invalid argyment of strategies");
		}
		std::string input("a");
		while (input != "quit") {
			int points_s1_before = points_s1;
			int points_s2_before = points_s2; 
			int points_s3_before = points_s3;
			MoveResult choice1 = s1->run();
			MoveResult choice2 = s2->run();
			MoveResult choice3 = s3->run();
			add_move(s1, s2, s3, choice1, choice2, choice3);
			std::cout << "=====================================================" << std::endl;
			std::cout << "Choice for round:" << std::endl;
			std::cout << s1->get_name() << " = " << (choice1 == MoveResult::Cooperate ? "C" : "D") << " ";
			std::cout << s2->get_name() << " = " << (choice2 == MoveResult::Cooperate ? "C" : "D") << " ";
			std::cout << s3->get_name() << " = " << (choice3 == MoveResult::Cooperate ? "C" : "D") << std::endl;
			std::cout << "Points for round: " << std::endl;
			std::cout << s1->get_name() << " = " << points_s1 - points_s1_before << " ";
			std::cout << s2->get_name() << " = " << points_s2 - points_s2_before << " ";
			std::cout << s3->get_name() << " = " << points_s3 - points_s3_before << std::endl;
			std::cout << "Points all: " << std::endl;
			std::cout << s1->get_name() << " = " << points_s1 << " ";
			std::cout << s2->get_name() << " = " << points_s2 << " ";
			std::cout << s3->get_name() << " = " << points_s3 << std::endl;
			std::cout << "=====================================================" << std::endl;
			std::cout << "Press any key to continue or enter \"quit\" to exit" << std::endl;
			std::cin >> input;
		}
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << std::endl;
	}
}

void Game::fast(const std::string& name1, const std::string& name2, const std::string& name3, const int steps) {
	try {
		auto s1 = factory.create(name1);
		auto s2 = factory.create(name2);
		auto s3 = factory.create(name3);
		if (s1 == nullptr || s2 == nullptr || s3 == nullptr) {
			throw std::invalid_argument("Invalid argument of strategies");
		}
		for (int i = 0; i < steps; i++) {
			MoveResult choice1 = s1->run();
			MoveResult choice2 = s2->run();
			MoveResult choice3 = s3->run();
			add_move(s1, s2, s3, choice1, choice2, choice3);
		}
		std::cout << "=====================================================" << std::endl;
		std::cout << "Game results:" << std::endl;
		std::cout << s1->get_name() << " = " << points_s1 << " ";
		std::cout << s2->get_name() << " = " << points_s2 << " ";
		std::cout << s3->get_name() << " = " << points_s3 << std::endl;
		std::cout << "=====================================================\n" << std::endl;
	}
	catch (std::invalid_argument e) {
		std::cout << e.what() << std::endl;
	}
}

void Game::tournament(const std::vector<std::string>& strategies, const int steps) {
	size_t len = strategies.size();
	std::vector<int> strategys_points(len, 0);
	int points_win = 0;
	std::string name_win;
	for (int i = 0; i < len - 2; i++) {
		for (int j = i + 1; j < len - 1; j++) {
			for (int k = j + 1; k < len; k++) {
				auto s1 = strategies[i];
				auto s2 = strategies[j];
				auto s3 = strategies[k];
				points_s1 = 0;
				points_s2 = 0;
				points_s3 = 0;
				fast(s1, s2, s3, steps);
				strategys_points[i] += points_s1;
				strategys_points[j] += points_s2;
				strategys_points[k] += points_s3;
				if (strategys_points[i] > points_win) {
					points_win = strategys_points[i];
					name_win = s1;
				}
				if (strategys_points[j] > points_win) {
					points_win = strategys_points[j];
					name_win = s2;
				}
				if (strategys_points[k] > points_win) {
					points_win = strategys_points[k];
					name_win = s3;
				}
			}
		}
	}
	std::cout << "=====================================================" << std::endl;
	std::cout << "Tournament results" << std::endl;
	std::cout << "Winner: " << name_win << std::endl;
	std::cout << "Points: " << points_win << std::endl;
	std::cout << "=====================================================\n" << std::endl;
}