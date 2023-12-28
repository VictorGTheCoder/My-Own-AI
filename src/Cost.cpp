#include "../include/Cost.hpp"
#include "../include/Data.hpp"


double NodeCost(double output, double target) {
    double error = output - target;
    return (error) * (error);
}

double DataCost(std::vector<Data> data) {
	double cost = 0.0;
	for (long unsigned int i = 0; i < data.size(); i++) {
		for (long unsigned int j = 0; j < data[i].expectedOutput.size(); j++) {
			cost += NodeCost(data[i].calculatedOutput[j], data[i].expectedOutput[j]);
		}
	}
	return cost / data.size();
}

