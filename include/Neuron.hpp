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
		double _bias;
		double _gradients;
		std::vector<Connection*> _connections;
		
	public:
		Neuron();
		~Neuron();


		void setOutput(double value);
		double getOutput() const;

        void setBias(double b);
        double getBias() const;

		void setGradients(double value);
		double getGradients() const;

		std::vector<double> getWeights() const;
		void setWeights(std::vector<double>);

		void updateWeights(double learningRate);
		void setConnection(Neuron* neuron);
		std::vector<Connection *> getConnections() const;
		void displayNeuron();
		void computeOutput();

};

#endif