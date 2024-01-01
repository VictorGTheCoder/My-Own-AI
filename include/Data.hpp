#include <vector>
#include <iostream>

struct Data {
	std::vector<double> input;
	std::vector<double> expectedOutput;
};


std::vector<Data> createDataSet();