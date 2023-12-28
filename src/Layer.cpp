#include "../include/Layer.hpp"
#include "../include/Neuron.hpp"


Layer::Layer(int size) : _size(size) {
	for (int i = 0; i < size; i++) {
		_Neurons.push_back(Neuron());
	}
}

