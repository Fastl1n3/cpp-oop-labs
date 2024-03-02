#include "ReverseSecConverter.h"

void ReverseSecConverter::run(std::array<short int, 44100>& default_arr, std::array<short int, 44100>& add_arr) {
	const int n = 22050;
	for (int i = 0; i < n; i++) {
		short int tmp = default_arr[i];
		default_arr[i] = default_arr[n - 1 - i];
		default_arr[n - 1 - i] = tmp;
	}
}