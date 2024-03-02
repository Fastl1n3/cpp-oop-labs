#pragma once

#include "IConverter.h"

class MutingConverter : public IConverter {

public:
	void run(std::array<short int, 44100>& default_arr, std::array<short int, 44100>& add_arr) override;
};