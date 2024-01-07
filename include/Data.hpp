#include <vector>
#include <iostream>
#include <cstdint>

struct Data {
	std::vector<double> input;
	std::vector<double> expectedOutput;
};


std::vector<Data> createDataSet();