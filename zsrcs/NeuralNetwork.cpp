#include <vector>
#include "../include/Layer.hpp"

class NeuralNetwork {
public:
    NeuralNetwork(const std::vector<int>& layerSizes);
    void createNetwork();
    // Other methods like train, predict, saveModel, loadModel, etc.

private:
    std::vector<Layer> layers;
    std::vector<int> layerSizes;
};

NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes) : layerSizes(layerSizes) {
    // Initialize the network with given layer sizes
}

void NeuralNetwork::createNetwork() {
    for (int i = 0; i < layerSizes.size(); ++i) {
        layers.emplace_back(Layer(layerSizes[i]));
    }

    // Further initialization can go here (e.g., initializing weights and biases)
}