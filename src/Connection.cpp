#include "../include/Connection.hpp"
#include "../include/Neuron.hpp"

Connection::Connection(Neuron* from, Neuron* to) : fromNeuron(from), toNeuron(to), _weight(0.0), _bias(0.0) {}

void Connection::setWeight(double w) {
    _weight = w;
}

void Connection::setBias(double b) {
    _bias = b;
}

void Connection::propagate() {
    double input = fromNeuron->getOutput();
    double output = (input * _weight) + _bias;
    // Ici, vous pouvez appliquer une fonction d'activation si nécessaire
    toNeuron->setOutput(output);
}
