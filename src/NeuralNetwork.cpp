#include "../include/NeuralNetwork.hpp"



NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes) : _layerSizes(layerSizes){
    std::cout << "NeuralNetwork constructor called : ";
    _learningRate = 0.05;
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
    ForwardPropagation();
    _outputLayer = _layers[_layers.size() - 1];

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

void NeuralNetwork::displayLastLayer() {
    std::cout << "<=== Last Layer ===>" << std::endl;
    _outputLayer->displayLayer();
    std::cout << "<==================>\n" << std::endl;
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

    setInputLayer(_currentData->input);
    ForwardPropagation();
    double cost = DataCost(_currentData, getOutputValues());
    std::cout << "Cost " << cost << std::endl;
    (void) cost;
    BackwarPropagation();
}


void NeuralNetwork::train() {
    int numBatches = _dataset.size() / BATCH_SIZE;

    for (int epoch = 0; epoch < NUM_EPOCHS; epoch++)
    {
        //ShuffleDataset(_dataset);
        for (int batch = 0; batch < numBatches; batch++)
        {
            std::vector<Data> miniBatch = GetMiniBatch(_dataset, batch, BATCH_SIZE);

            for (Data &data : miniBatch)
            {
                for (double t : data.input)
                    std::cout << t << ", ";
                std::cout << std::endl;
                _currentData = &data;
                learn();
            }
        }
    }


    

}

std::vector<double> NeuralNetwork::getOutputValues()
{
    std::vector<double> result;
    for (Neuron *neuron : _outputLayer->getNeurons())
    {
        result.push_back(neuron->getOutput());
    }
    return result;
}


std::vector<Data> NeuralNetwork::GetMiniBatch(const std::vector<Data>& dataset, int batchNumber, int batchSize) {
    std::vector<Data> miniBatch;
    int startIdx = batchNumber * batchSize;
    int endIdx = std::min(startIdx + batchSize, static_cast<int>(dataset.size()));

    for (int i = startIdx; i < endIdx; ++i) {
        miniBatch.push_back(dataset[i]);
    }

    return miniBatch;
}


void NeuralNetwork::ShuffleDataset(std::vector<Data>& dataset) {
    // Obtain a time-based seed:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Shuffle using the default random engine
    std::shuffle(dataset.begin(), dataset.end(), std::default_random_engine(seed));
}

void NeuralNetwork::updateDataset()
{
    // for (std::size_t i = 0; i < _dataset.size(); ++i)
    // {
    //     setInputLayer(_dataset[i].input);

    //     ForwardPropagation();
    //     Layer *lastLayer = _layers[_layers.size() - 1];
    //     std::vector<double> calculatedOutputs;
    //     for (Neuron *neuron : lastLayer->getNeurons())
    //     {
    //         calculatedOutputs.push_back(neuron->getOutput());
    //     }
    //     _dataset[i].calculatedOutput = calculatedOutputs;
    // }
}