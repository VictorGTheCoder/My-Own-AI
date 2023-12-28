#include "../include/NeuralNetwork.hpp"
#include "../include/Layer.hpp"


NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes) : layerSizes(layerSizes) {
    // Initialize the network with given layer sizes
}

void NeuralNetwork::createNetwork() {
    for (std::size_t i = 0; i < layerSizes.size(); ++i) {
        layers.emplace_back(Layer(layerSizes[i]));
    }

    // Further initialization can go here (e.g., initializing weights and biases)
}