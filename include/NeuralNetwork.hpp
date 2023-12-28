#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
class Layer;

class NeuralNetwork
{
    public:
        NeuralNetwork(const std::vector<int>& layerSizes);
        void createNetwork();
        // Other methods like train, predict, saveModel, loadModel, etc.

    private:
        std::vector<Layer> layers;
        std::vector<int> layerSizes;
};

#endif