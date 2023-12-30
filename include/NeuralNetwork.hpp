#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include "../include/Layer.hpp"
#include "../include/Color.hpp"
#include "../include/Cost.hpp"

class NeuralNetwork
{
    public:
        NeuralNetwork(const std::vector<int>& layerSizes);
        ~NeuralNetwork();
        void createNetwork(std::vector<Data> dataset);
        void displayNetwork();
        void setInputLayer(std::vector<double> inputs);


        void ForwardPropagation();
        void BackwarPropagation();

        void learn();
        void train();
        // Other methods like train, predict, saveModel, loadModel, etc.

    private:
        double _learningRate;
        std::vector<Data> _dataset;
        std::vector<double> _inputs;
        Layer* _inputLayer;
        std::vector<Layer *> _layers;
        std::vector<int> _layerSizes;
};

#endif