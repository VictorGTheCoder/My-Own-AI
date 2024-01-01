#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 
#include "../include/Layer.hpp"
#include "../include/Color.hpp"
#include "../include/Cost.hpp"

#define BATCH_SIZE 5
#define NUM_EPOCHS 1

class NeuralNetwork
{
    public:
        NeuralNetwork(const std::vector<int>& layerSizes);
        ~NeuralNetwork();
        
        void createNetwork(std::vector<Data> dataset);
        void setInputLayer(std::vector<double> inputs);

        void ForwardPropagation();
        void BackwarPropagation();

        void learn();
        void train();


        void displayNetwork();
        void displayLastLayer();


        std::vector<Data> GetMiniBatch(const std::vector<Data>& dataset, int batchNumber, int batchSize);


        std::vector<double> getOutputValues();



        void ShuffleDataset(std::vector<Data> &dataset);
        void updateDataset();


    private:
        double _learningRate;
        std::vector<Data> _dataset;
        Data *_currentData;
        std::vector<double> _inputs;
        Layer* _inputLayer;
        Layer* _outputLayer;
        std::vector<Layer *> _layers;
        std::vector<int> _layerSizes;
};

#endif