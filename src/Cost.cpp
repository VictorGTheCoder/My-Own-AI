#include "../include/Cost.hpp"


double NodeCost(double output, double target) {
    double error = output - target;
    return (error) * (error);
}

double DataCost(std::vector<Data> data) {
	double cost = 0.0;
	for (long unsigned int i = 0; i < data.size(); i++) {
		for (long unsigned int j = 0; j < data[i].expectedOutput.size(); j++) {
			cost += NodeCost(data[i].calculatedOutput[j], data[i].expectedOutput[j]);
			//std::cout << "Cost calculated: " << data[i].calculatedOutput[j] << " Expected " << data[i].expectedOutput[j] << std::endl;
		}
	}
	return cost / data.size();
}


double ActualCost(std::vector<Data> data, std::vector<double> output) {
	double cost = 0.0;
	for (long unsigned int i = 0; i < data.size(); i++) {
		for (long unsigned int j = 0; j < output.size(); j++) {
			cost += NodeCost(data[i].calculatedOutput[j], output[j]);
			//std::cout << "Cost calculated: " << data[i].calculatedOutput[j] << " Expected " << data[i].expectedOutput[j] << std::endl;
		}
	}
	return cost / data.size();
}



