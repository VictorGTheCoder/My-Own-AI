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


// ReLU Activation Function
double ActivationFunctionReLU(double x) {
    return std::max(0.0, x);
}

// ReLU Derivative
double ActivationFunctionReLUDerivative(double x) {
    return x > 0 ? 1.0 : 0.0;
}



double ActivationFunctionSoftmax(std::vector<double> inputs, int index)
{
	double expSum = 0;
	for (std::size_t i = 0; i < inputs.size(); i++)
	{
		expSum += std::exp(inputs[i]);
	}
	return (std::exp(inputs[index]) / expSum);
}


double ActivationFunctionSoftmaxDerivative(std::vector<double> inputs, int index)
{
		double expSum = 0;
		for (std::size_t i = 0; i < inputs.size(); i++)
		{
			expSum += std::exp(inputs[i]);
		}
		double ex = std::exp(inputs[index]);
		return (ex * expSum - ex * ex) / (expSum * expSum);
}