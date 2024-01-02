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
    forwardPropagation();
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


void NeuralNetwork::forwardPropagation() {
    for (Layer *layer : _layers)
    {
        //layer->displayLayer();
        layer->ComputeOutputs();
    }

}

void NeuralNetwork::backwarPropagation() {

    std::vector<double> delta_errors;
    for (std::size_t i = 0; i < _outputLayer->getNeurons().size(); ++i)
    {
        double output = _outputLayer->getNeurons()[i]->getOutput();
        double target = _currentData->expectedOutput[i];
        double error = output - target;
        double delta = error * ActivationFunctionSigmoidDerivative(output);

        delta_errors.push_back(delta);
        _outputLayer->getNeurons()[i]->setDelta(delta);
    }

    for (int i = _layers.size() - 2; i >= 0; i--) // start from the last hidden layer
    {
        Layer *layer = _layers[i];
        Layer *nextLayer = _layers[i + 1];

        for (std::size_t j = 0; j < layer->getNeurons().size(); j++)
        {
            double sum = 0.0;
            for (std::size_t k = 0; k < nextLayer->getNeurons().size(); k++)
            {
                sum += nextLayer->getNeurons()[k]->getWeights()[j] * nextLayer->getNeurons()[k]->getDelta();
            }

            double output = layer->getNeurons()[j]->getOutput();
            double delta = sum * ActivationFunctionSigmoidDerivative(output);
            layer->getNeurons()[j]->setDelta(delta);
        }
    }

    for (Layer *layer : _layers)
    {
        layer->updateWeights(_learningRate);
    }
    // std::vector<double> delta_errors;
    // for (std::size_t i = 0; i < _outputLayer->getNeurons().size(); ++i)
    // {
    //     delta_errors.push_back(_outputLayer->getNeurons()[i]->getOutput() - _currentData->expectedOutput[i]);
    // }
    
    // for (std::size_t i = _layers.size() - 1; i >= 0; i--)
    // {
    //     for (std::size_t j = 0; j < _layers[i]->getNeurons().size(); j++)
    //     {
             
    //     }
    // }
}


void NeuralNetwork::learn() {
    forwardPropagation();
    // double cost = DataCost(_currentData, getOutputValues());
    // std::cout << "Cost " << cost << std::endl;
    backwarPropagation();
}


void NeuralNetwork::train() {
    int numBatches = _dataset.size() / BATCH_SIZE;

    for (int epoch = 0; epoch < NUM_EPOCHS; epoch++)
    {
        ShuffleDataset(_dataset);
        for (int batch = 0; batch < numBatches; batch++)
        {
            std::vector<Data> miniBatch = GetMiniBatch(_dataset, batch, BATCH_SIZE);

            for (Data &data : miniBatch)
            {
                // for (double t : data.input)
                //     std::cout << t << ", ";
                // std::cout << std::endl;
                _currentData = &data;
                setInputLayer(_currentData->input);
                learn();
            }
        }
    }
}


int NeuralNetwork::predictData(Data data)
{
    setInputLayer(data.input);
    
    forwardPropagation();
    std::vector<double> calculatedOutputs;
    for (Neuron *neuron : _outputLayer->getNeurons())
    {
        calculatedOutputs.push_back(neuron->getOutput());
    }
    for (double t : calculatedOutputs)
        std::cout << t << ", ";
    

    if (calculatedOutputs[0] > calculatedOutputs[1] && calculatedOutputs[0] > calculatedOutputs[2])
        return (1);
    else if (calculatedOutputs[1] > calculatedOutputs[0] && calculatedOutputs[1] > calculatedOutputs[2])
        return (2);
    else
        return (3);

}

void NeuralNetwork::predictDataSet(std::vector<Data> dataset)
{
    int success = 0;
    for (Data data : dataset)
    {
    
        int r = predictData(data);
        int rr = 0;
        if (data.expectedOutput[0] == 1)
            rr = 1;
        else if (data.expectedOutput[1] == 1)
            rr = 2;
        else
            rr = 3;
        if (r != rr)
            std::cout << "Expected : " << rr << " Predicted : " << r << " " << COLOR_RED << "KO" << COLOR_RESET << std::endl;
        else
        {
            std::cout << "Expected : " << rr << " Predicted : " << r << " " << COLOR_GREEN << "OK" << COLOR_RESET << std::endl;
            success++;
        }
    }
    std::cout << "Success : " << success << "/" << dataset.size() << std::endl;
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