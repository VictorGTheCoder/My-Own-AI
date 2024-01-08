#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <algorithm>
#include <random>
#include <chrono> 
#include <fstream>
#include <iostream>
#include "json.hpp"
#include "../include/Layer.hpp"
#include "../include/Color.hpp"
#include "../include/Cost.hpp"
#include "../include/ActivationFunction.hpp"

#define BATCH_SIZE 1
#define NUM_EPOCHS 50

class NeuralNetwork
{
    public:
        NeuralNetwork(const std::vector<int>& layerSizes);
        ~NeuralNetwork();
        
        void createNetwork(std::vector<Data> dataset);
        void setInputLayer(std::vector<double> inputs);

        void forwardPropagation();
        void backwarPropagation();

        void learn();
        void train();

        int predict(std::vector<double> inputs);
        int predictData(Data data);
        void predictDataSet(std::vector<Data> dataset);

        void displayNetwork();
        void displayLastLayer();


        std::vector<Data> GetMiniBatch(const std::vector<Data>& dataset, int batchNumber, int batchSize);

        std::vector<double> getOutputValues();

		void updateWeightsAndBias(Layer *layer, const std::vector<double> &deltaErrors);

        void ShuffleDataset(std::vector<Data> &dataset);
        void updateDataset();

        void saveModel(const std::string& filename);
        void loadModel(const std::string& filename);


    private:
        double _learningRate;
        std::vector<Data> _dataset;
        Data *_currentData;
        std::vector<double> _inputs;
        Layer* _inputLayer;
        Layer* _outputLayer;
        std::vector<Layer *> _layers;
        std::vector<int> _layerSizes;
        int _currentTrainingSuccess;
};

#endif