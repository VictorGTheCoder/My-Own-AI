#include "../include/NeuralNetwork.hpp"



NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes) : _layerSizes(layerSizes){
    std::cout << "NeuralNetwork constructor called : ";
    _learningRate = 0.25;
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

void NeuralNetwork::createNetwork(std::vector<Data> dataset) {
    _dataset = dataset;
    std::vector<double> inputs = _dataset[0].input;
    _inputs = inputs;
    _inputLayer = new Layer(inputs.size());
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
    for (Layer *layer : _layers)
    {
        //layer->displayLayer();
        layer->ComputeOutputs();
    }

}

void NeuralNetwork::BackwarPropagation() {
    // Backward propagation code goes here
}


void NeuralNetwork::learn() {
    const double h = 0.0001;
    double originalCost = DataCost(_dataset);
    std::cout << "Original cost : " << originalCost << std::endl;

    for (Layer *layer : _layers)
    {
        for (Neuron *neuron : layer->getNeurons())
        {
            for (Connection *connection : neuron->getConnections())
            {
                double originalWeight = connection->getWeight();
                connection->setWeight(originalWeight + h);
                ForwardPropagation();
                std::vector<double> calculatedOutputs;
                Layer *lastLayer = _layers[_layers.size() - 1];
                for (Neuron *neuron : lastLayer->getNeurons())
                {
                    calculatedOutputs.push_back(neuron->getOutput());
                }
                //_dataset[0].calculatedOutput = calculatedOutputs;
                double newCost = DataCost(_dataset);
                double gradientWeight = (newCost - originalCost) / h;
                std::cout << "DeltaCost" << newCost - originalCost << std::endl;

                double originalBias = connection->getBias();
                connection->setBias(originalBias + h);
                newCost = DataCost(_dataset);
                double gradientBias = (newCost - originalCost) / h;


                connection->setWeight(originalWeight - _learningRate * gradientWeight);
                connection->setBias(originalBias - _learningRate * gradientBias);

                
            }
        }
    }
}

void NeuralNetwork::train() {

    for (int i = 0; i < 5; ++i)
    {

        for (std::size_t i = 0; i < _dataset.size(); ++i)
        {
            setInputLayer(_dataset[i].input);

            ForwardPropagation();
            Layer *lastLayer = _layers[_layers.size() - 1];
            std::vector<double> calculatedOutputs;
            for (Neuron *neuron : lastLayer->getNeurons())
            {
                calculatedOutputs.push_back(neuron->getOutput());
            }
            _dataset[i].calculatedOutput = calculatedOutputs;
        }
        learn();
    }
    double avgCost = DataCost(_dataset);
    std::cout << "Average cost : " << avgCost << std::endl;
}