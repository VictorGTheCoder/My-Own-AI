#include "../include/Layer.hpp"
#include "../include/Neuron.hpp"
#include <memory>

Layer::Layer(int numberOfNeurons) : _size(numberOfNeurons) {
    for (int i = 0; i < numberOfNeurons; ++i) {
        _Neurons.push_back(new Neuron());
    }
	std::cout << "Layer constructor called and create " << numberOfNeurons << " neurons\n" << std::endl;
}

Layer::~Layer() {
	std::cout << "Layer destructor called" << std::endl;
	for (Neuron *neuron : _Neurons)
		delete neuron;
}


void Layer::setConnections(Layer *previousLayer) {
	for (int i = 0; i < _size; i++) {
		for (int j = 0; j < previousLayer->_size; j++) {
			_Neurons[i]->setConnection(previousLayer->_Neurons[j]);
		}
	}
}

void Layer::displayLayer() {
	std::cout << "Layer size : " << _size << std::endl;
	for (Neuron *neuron : _Neurons)
	{
		neuron->displayNeuron();
		std::cout << "-------------" << std::endl;
	}
}

std::vector<Neuron *> Layer::getNeurons() const {return _Neurons;}

int Layer::getSize() const {return _size;}



void Layer::ComputeOutputs() {
	for (Neuron *neuron : _Neurons)
	{
		neuron->computeOutput();
	}
}

void Layer::updateWeights(double learningRate)
{
	for (Neuron* neuron : _Neurons)
	{
		
		neuron->updateWeights(learningRate);
	}
}

