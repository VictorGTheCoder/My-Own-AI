#include "../include/NeuralNetwork.hpp"



NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes) : _layerSizes(layerSizes) {
    std::cout << "NeuralNetwork constructor called : ";
    for (int t : _layerSizes)
        std::cout << t << " ";
    std::cout << std::endl;
}

NeuralNetwork::~NeuralNetwork() {
    for (Layer *layer : _layers)
        delete layer;
    delete _inputLayer;
    std::cout << "NeuralNetwork destructor called" << std::endl;
}

void NeuralNetwork::createNetwork(std::vector<double> _inputs) {
    setInputLayer(_inputs);
    for (std::size_t i = 0; i < _layerSizes.size(); ++i) {
        _layers.emplace_back(new Layer(_layerSizes[i]));
        if (i > 0)
            _layers[i]->setConnections(_layers[i - 1]);
        else
            _layers[i]->setConnections(_inputLayer);
    }


    // Further initialization can go here (e.g., initializing weights and biases)
}

void NeuralNetwork::setInputLayer(std::vector<double> inputs)
{
    (void) inputs;
    _inputs = inputs;
    _inputLayer = new Layer(inputs.size());
    for (std::size_t i = 0; i < inputs.size(); ++i)
    {
        _inputLayer->getNeurons()[i]->setOutput(inputs[i]);
    }
}

void NeuralNetwork::displayNetwork() {
    for (Layer *layer : _layers)
        layer->displayLayer();
}


void NeuralNetwork::ForwardPropagation() {

    std::cout << "\n\nForward propagation\n\n" << std::endl;
    for (Layer *layer : _layers)
    {
        //layer->displayLayer();
        layer->ComputeOutputs();
    }

}

void NeuralNetwork::BackwarPropagation() {
    // Backward propagation code goes here
}

void NeuralNetwork::train() {
    // Training code goes here
}