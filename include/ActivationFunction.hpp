#include <cmath>
#include <cstdint>
#include <vector>

double ActivationFunctionSigmoid(double x);
double ActivationFunctionSigmoidDerivative(double x);

double ActivationFunctionTanh(double x);
double ActivationFunctionTanhDerivative(double x);

double ActivationFunctionReLU(double x);
double ActivationFunctionReLUDerivative(double x);

double ActivationFunctionSoftmax(std::vector<double> inputs, int index);
double ActivationFunctionSoftmaxDerivative(std::vector<double> inputs, int index);

