#include "../include/Neuron.hpp"

Neuron::Neuron() : _output(0.0) {}

Neuron::~Neuron() {}

void Neuron::setOutput(double output) {_output = output;}

double Neuron::getOutput() const {return _output;}