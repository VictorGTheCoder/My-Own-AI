#include "../include/Connection.hpp"
#include "../include/Neuron.hpp"
#include <cstdint>





Connection::Connection(Neuron* from, Neuron* to) : _weight(generateRandomNumber())
{
    fromNeuron = from;
    toNeuron = to;
}

Connection::~Connection()
{/*std::cout << "Connection destructor called" << std::endl;*/}

void Connection::setWeight(double w){
    _weight = w;
}


double Connection::getWeight() const {return _weight;}

double Connection::computeConnection() {
    double input = fromNeuron->getOutput();
    double output = (input * _weight);
    
    return output;
}
