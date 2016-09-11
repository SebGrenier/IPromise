#include "Promise.hpp"
#include <string>
#include <ctime>

void main(void)
{
	srand(time(nullptr));
	auto dummy = rand() % 100;

	std::function<void(std::function<void(int)>, std::function<void(std::string)>)> func = [dummy](std::function<void(int)> &resolve, std::function<void(std::string)> &reject) -> void
	{
		if (dummy > 50) {
			resolve(dummy);
		}
		else {
			reject("Dummy failed!");
		}
	};

	Promise p(func);
}