#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include "../include/Layer.hpp"
#include "../include/Data.hpp"
#include "../include/Color.hpp"

class NeuralNetwork
{
    public:
        NeuralNetwork(const std::vector<int>& layerSizes);
        ~NeuralNetwork();
        void createNetwork(std::vector<double> inputs);
        void displayNetwork();
        void setInputLayer(std::vector<double> inputs);


        void ForwardPropagation();
        void BackwarPropagation();

        void train();
        // Other methods like train, predict, saveModel, loadModel, etc.

    private:
        std::vector<double> _inputs;
        Layer* _inputLayer;
        std::vector<Layer *> _layers;
        std::vector<int> _layerSizes;
};

#endif