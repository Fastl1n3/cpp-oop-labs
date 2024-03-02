#pragma once

#include <string>
#include <fstream>
#include <array>

class IConverter {
public:
	virtual ~IConverter() = default;
	virtual void run(std::array<short int, 44100>& default_arr, std::array<short int, 44100>& add_arr) = 0;
};
