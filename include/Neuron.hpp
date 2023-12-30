#ifndef NEURON_HPP
#define NEURON_HPP


#include <iostream>
#include <vector>
#include <cmath>
#include <memory>

#include "../include/Connection.hpp"

class Neuron
{
	private:
		double _output;
		std::vector<Connection*> _connections;
		
	public:
		Neuron();
		~Neuron();
		void setOutput(double value);
		double getOutput() const;
		void setConnection(Neuron* neuron);
		std::vector<Connection *> getConnections() const;
		void displayNeuron();
		void computeOutput();

};

#endif