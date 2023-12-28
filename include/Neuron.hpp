#ifndef NEURON_HPP
#define NEURON_HPP


#include <iostream>
#include <vector>
#include <cmath>

#include "../include/Connection.hpp"

class Neuron
{
	private:
		double _output;
		std::vector<Connection> _connections;
		
	public:
		Neuron();
		~Neuron();
		void setOutput(double value);
		double getOutput() const;

};

#endif