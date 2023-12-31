#include "../include/Connection.hpp"
#include "../include/Neuron.hpp"




Connection::Connection(Neuron* from, Neuron* to) : fromNeuron(from), toNeuron(to), _weight(generateRandomNumber())
{/*std::cout << "Connection constructor called" << std::endl;*/}

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
