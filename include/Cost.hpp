#include "Data.hpp"

double NodeCost(double output, double target);
double DataCost(std::vector<Data> data);
double DataCost2(std::vector<Data> data, std::vector<double> output);
double ActualCost(std::vector<Data> data, std::vector<double> output);