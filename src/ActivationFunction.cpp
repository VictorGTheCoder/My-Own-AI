#include "../include/ActivationFunction.hpp"

double ActivationFunctionSigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}