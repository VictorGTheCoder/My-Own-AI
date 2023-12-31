#include "../include/Neuron.hpp"
#include "../include/Connection.hpp"
#include "../include/Color.hpp"

Neuron::Neuron() : _output(0.0), _bias(0.0) {/*std::cout << "Neuron constructor called" << std::endl;*/}

Neuron::~Neuron() {/*std::cout << "Neuron destructor called" << std::endl;*/ for (Connection *connection : _connections) delete connection;}

void Neuron::setOutput(double output) {_output = output;}

double Neuron::getOutput() const {return _output;}

std::vector<Connection *> Neuron::getConnections() const {return _connections;}

void Neuron::setConnection(Neuron* neuron) {
	_connections.push_back(new Connection(neuron, this));
}


void Neuron::setBias(double b){
    _bias = b;
}
double Neuron::getBias() const {return _bias;}


void Neuron::displayNeuron() {
	std::cout << COLOR_BRIGHT_YELLOW << "Neuron output : " << COLOR_RED << _output << COLOR_RESET << std::endl;
	for (Connection *connection : _connections) {
		std::cout << COLOR_BRIGHT_YELLOW << "Connection " << COLOR_BLUE << "weight" << COLOR_YELLOW << " / " << COLOR_CYAN << "bias" <<  COLOR_BRIGHT_YELLOW << " : " << COLOR_BLUE << connection->getWeight() << COLOR_BRIGHT_YELLOW <<  " / " << COLOR_CYAN << this->getBias() << COLOR_RESET << std::endl;
	}
}

void Neuron::computeOutput() {
	if (_connections.empty()) {
		std::cout << COLOR_BRIGHT_RED << "Error : " << COLOR_RESET << "No connection for this neuron" << std::endl;
		return;
	}
	double temp = 0.0;
	for (Connection *connection : _connections) {
		temp += connection->computeConnection();
	}
	temp += _bias;
	_output = ActivationFunctionSigmoid(temp);
}