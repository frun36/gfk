#include "Config.hpp"

void Config::_prepareFunctionData() {
	std::vector<std::array<double, 3>> functionData;
	double x, y;
	switch (_function) {
	case Function::F1:
		for (size_t i = 0; i < 20; i++) {
			x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			
			functionData.push_back({ x, y, 200 * (float(rand()) / RAND_MAX) });
		}
		break;
	case Function::F2:
		for (size_t i = 0; i < 100; i++) {
			x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			functionData.push_back({ x, y, x * (2 * x - 7) * (2 * y + 1) + 2 * y });
		}
		break;
	case Function::F3:
		for (size_t i = 0; i < 10; i++) {
			x = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			y = 4.8 * (float(rand()) / RAND_MAX) - 2.4;
			functionData.push_back({ x, y, x * sin(2 * y)});
		}
		break;
	case Function::F4:
		for (size_t i = 0; i < 100; i++) {
			x = 2 * (float(rand()) / RAND_MAX) - 1;
			y = 2 * (float(rand()) / RAND_MAX) - 1;
			functionData.push_back({ x, y, sin(8 * (x * x + y * y)) });
		}
		break;
	}

	_functionData = functionData;
}
