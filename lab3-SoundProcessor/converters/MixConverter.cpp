#include "MixConverter.h"

void MixConverter::run(std::array<short int, 44100> &default_arr, std::array<short int, 44100>& add_arr) {
	const int n = 44100;
	for (int i = 0; i < n; i++) {
		default_arr[i] = (default_arr[i] + add_arr[i]) / 2;
	}
}