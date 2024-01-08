#include "../include/NeuralNetwork.hpp"



NeuralNetwork::NeuralNetwork(const std::vector<int>& layerSizes) : _layerSizes(layerSizes){
    std::cout << "NeuralNetwork constructor called : ";
    _learningRate = 0.1;
    for (int t : _layerSizes)
        std::cout << t << " ";
    std::cout << std::endl;
}

NeuralNetwork::~NeuralNetwork() {
    for (Layer *layer : _layers)
        delete layer;
    delete _inputLayer;
    //std::cout << "NeuralNetwork destructor called" << std::endl;
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
	std::cout << COLOR_RED << "INPUT LAYER - " << COLOR_RESET;
	_inputLayer->displayLayer();
	std::cout << std::endl;
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

void NeuralNetwork::updateWeightsAndBias(Layer *layer, const std::vector<double> &deltaErrors) {
    std::cout << COLOR_BLUE << "NEW LAYER UPDATE" << COLOR_RESET << " ";
	for (std::size_t i = 0; i < layer->getNeurons().size(); i++) {
		std::cout << "	Update Neuron Weights ";
        Neuron *neuron = layer->getNeurons()[i];
        double deltaError = deltaErrors[i];

        // Update weights
		for (Connection *connection : neuron->getConnections())
		{
			double oldWeight = connection->getWeight();
			double input = connection->fromNeuron->getOutput();
			double newWeight = oldWeight - _learningRate * input * deltaError;
			if (newWeight > oldWeight)
				std::cout << COLOR_GREEN << "+" << newWeight - oldWeight << COLOR_RESET;
			else
				std::cout << COLOR_RED << newWeight - oldWeight << COLOR_RESET;
			std::cout << " ";

			connection->setWeight(newWeight);
		}

        // Update bias
        double oldBias = neuron->getBias();
        double newBias = oldBias - _learningRate * deltaError;
        neuron->setBias(newBias);
    }
	std::cout << std::endl;
}


void NeuralNetwork::backwarPropagation() {

	std::vector<double> expectedOutput = _currentData->expectedOutput;
	Layer *currentLayer = _layers.back();
	std::vector<double> deltaOutputErrors(_outputLayer->getNeurons().size());

	// Handle the output layer
	for (std::size_t i = 0; i < currentLayer->getNeurons().size(); i++)
	{
		Neuron *currentNeuron = currentLayer->getNeurons()[i];
		double currentNeuronOutput = currentNeuron->getOutput();
		double ActivationFunctionDerivative = ActivationFunctionSigmoidDerivative(currentNeuronOutput);
		deltaOutputErrors[i] = currentNeuronOutput - expectedOutput[i];
		deltaOutputErrors[i] *= ActivationFunctionDerivative;
	}
	updateWeightsAndBias(currentLayer, deltaOutputErrors);

	// Loop over all hidden layer backward
	for (int layerIndex = _layers.size() - 2; layerIndex >= 0; layerIndex--)
	{
		currentLayer = _layers[layerIndex];
		std::vector<double> deltaHiddenErrors(currentLayer->getNeurons().size());
		for (std::size_t i = 0; i < currentLayer->getNeurons().size(); i++)
		{
			Neuron *currentNeuron = currentLayer->getNeurons()[i];
			double currentNeuronOutput = currentNeuron->getOutput();
			double ActivationFunctionDerivative = ActivationFunctionSigmoidDerivative(currentNeuronOutput);
			double sumDeltaWeight = 0.0;
			// Sum over all weights between the current neuron and all neuron in the next layer
			for (std::size_t j = 0; j < _layers[layerIndex + 1]->getNeurons().size(); j++)
				sumDeltaWeight += _layers[layerIndex + 1]->getNeurons()[j]->getWeights()[i] * deltaOutputErrors[j];
			deltaHiddenErrors[i] = sumDeltaWeight * ActivationFunctionDerivative;
		}
		updateWeightsAndBias(currentLayer, deltaHiddenErrors);
		deltaOutputErrors = deltaHiddenErrors;
	}
}

void NeuralNetwork::learn() {
    forwardPropagation();

    backwarPropagation();
}


void NeuralNetwork::train() {
	// _currentData = &(_dataset[0]);
	// setInputLayer(_currentData->input);
	// _inputLayer->displayLayer();
	// learn();
	for (int epoch = 0; epoch < 1; epoch++)
	{
		ShuffleDataset(_dataset);
		for (Data &data : _dataset)
		{
			_currentData = &(data);
			setInputLayer(_currentData->input);
			learn();		
		}
		predictDataSet(_dataset);
	}

	forwardPropagation();

    //_currentTrainingSuccess = 0;
    //int numBatches = _dataset.size() / BATCH_SIZE;

    // for (int epoch = 0; epoch < NUM_EPOCHS; epoch++)
    // {
	// 	totalCost = 0;
    // // while (true)
    // // {
    //     ShuffleDataset(_dataset);
    //     // for (int batch = 0; batch < numBatches; batch++)
    //     // {
    //     //     std::vector<Data> miniBatch = GetMiniBatch(_dataset, batch, BATCH_SIZE);

    //     //     for (Data &data : miniBatch)
    //     //     {
    //     //         // for (double t : data.input)
    //     //         //     std::cout << t << ", ";
    //     //         // std::cout << std::endl;
    //     //         _currentData = &data;
    //     //         setInputLayer(_currentData->input);
    //     //         learn();
    //     //     }

    //     //     // for (Layer *layer : _layers)
    //     //     // {
    //     //     //     layer->updateWeights(-_learningRate / miniBatch.size());
    //     //     // }

	// 	for (Data &data : _dataset)
	// 	{
	// 		_currentData = &data;
	// 		setInputLayer(_currentData->input);
	// 		learn();
	// 	}

	// 	std::cout << "Cost : " << totalCost / 100 << std::endl;
    //     // if (_currentTrainingSuccess == (int)_dataset.size())
    //     // {
    //     //     std::cout << "Success : " << _currentTrainingSuccess << "/" << _dataset.size() << std::endl;
    //     //     break;
    //     // }
    // }
}


int NeuralNetwork::predict(std::vector<double> inputs) {
    setInputLayer(inputs);
    forwardPropagation();
    std::vector<double> calculatedOutputs;
    for (Neuron *neuron : _outputLayer->getNeurons())
    {
        calculatedOutputs.push_back(neuron->getOutput());
    }
    // for (double t : calculatedOutputs)
    //     std::cout << t << ", ";
    // std::cout << std::endl;
    if (calculatedOutputs[0] > calculatedOutputs[1])
        return (1);
    else 
        return (2);
    // else if (calculatedOutputs[1] > calculatedOutputs[0] && calculatedOutputs[1] > calculatedOutputs[2])
    //     return (2);
    // else
    //     return (3);
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
    // for (double t : calculatedOutputs)
    //     std::cout << t << ", ";
    

    if (calculatedOutputs[0] > calculatedOutputs[1])
        return (1);
    else 
        return (2);
    // else if (calculatedOutputs[1] > calculatedOutputs[0] && calculatedOutputs[1] > calculatedOutputs[2])
    //     return (2);
    // else
    //     return (3);

}

void NeuralNetwork::predictDataSet(std::vector<Data> dataset)
{
	double totalCost = 0.0;

    int success = 0;
    for (Data data : dataset)
    {
    	double cost = DataCost(&data, getOutputValues());
		totalCost += cost;
        int r = predictData(data);
        int rr = 0;
        if (data.expectedOutput[0] == 1)
            rr = 1;
        else if (data.expectedOutput[1] == 1)
            rr = 2;
        else
            rr = 3;
        if (r != rr)
            continue;
            //std::cout << "Expected : " << rr << " Predicted : " << r << " " << COLOR_RED << "KO" << COLOR_RESET << std::endl;
        else
        {
            //std::cout << "Expected : " << rr << " Predicted : " << r << " " << COLOR_GREEN << "OK" << COLOR_RESET << std::endl;
            success++;
        }
    }
    std::cout << "Success : " << success << "/" << dataset.size() << std::endl;
	std::cout << "Avg Cost : " << totalCost / dataset.size() << std::endl;
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

void NeuralNetwork::saveModel(const std::string& filename) {
    nlohmann::json modelJson;

    // Save layer sizes
    modelJson["layerSizes"] = _layerSizes;

    // Save connections (weights and biases)
    std::vector<nlohmann::json> connections;
    for (Layer* layer : _layers) {
        for (Neuron *neuron : layer->getNeurons()) {
            nlohmann::json neuronJson;
            neuronJson["weights"] = neuron->getWeights();
            neuronJson["bias"] = neuron->getBias();
            connections.push_back(neuronJson);
        }
    }
    
    modelJson["connections"] = connections;

    // Write JSON to file
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    
    file << modelJson.dump(4); // 4 is for pretty printing
    
    file.close();
}


void NeuralNetwork::loadModel(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }

    nlohmann::json modelJson;
    file >> modelJson;
    file.close();


    // Assuming the layer sizes are consistent with the existing network
    std::size_t neuronIndex = 0;
    for (Layer* layer : _layers) {
        for (Neuron* neuron : layer->getNeurons()) {
            if (neuronIndex < modelJson["connections"].size()) {
                nlohmann::json neuronJson = modelJson["connections"][neuronIndex];
                neuron->setWeights(neuronJson["weights"].get<std::vector<double>>());
                neuron->setBias(neuronJson["bias"].get<double>());
                neuronIndex++;
            }
        }
    }
}


