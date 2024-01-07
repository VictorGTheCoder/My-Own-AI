#include "../include/ActivationFunction.hpp"

double ActivationFunctionSigmoid(double x) {
	return 1.0 / (1.0 + exp(-x));
}

double ActivationFunctionSigmoidDerivative(double x) {
	double activation = ActivationFunctionSigmoid(x);
	return activation * (1.0 - activation);
}

double ActivationFunctionTanh(double x) {
	return (exp(x) - exp(-x)) / (exp(x) + exp(-x));
}

double ActivationFunctionTanhDerivative(double x) {
	double activation = ActivationFunctionTanh(x);
	return (1 - (activation * activation));
}

