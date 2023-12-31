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
    const double h = 0.0001;
    std::vector<double> calculatedOutputs;
    ForwardPropagation();
    for (Neuron *neuron2 : _outputLayer->getNeurons())
    {
        calculatedOutputs.push_back(neuron2->getOutput());
    }
    double originalCost = DataCost2(_dataset, calculatedOutputs);
    double deltaCost;
    std::cout << "Original cost : " << originalCost << std::endl;

    double gradientWeightAvg = 0.0;
    double gradientBiasAvg = 0.0;


    for (int i = _layers.size() - 1; i >= 0; i--)
    {
        for (Neuron *neuron : _layers[i]->getNeurons())
        {
            for (Connection *connection : neuron->getConnections())
            {
                double originalWeight = connection->getWeight();
                connection->setWeight(originalWeight + h);
                ForwardPropagation();
                for (Neuron *neuron2 : _outputLayer->getNeurons())
                {
                    calculatedOutputs.push_back(neuron2->getOutput());
                }
                deltaCost = DataCost2(_dataset, calculatedOutputs) - originalCost;
                calculatedOutputs.clear();

                std::cout << "DeltaCost " << deltaCost << std::endl;
                connection->setWeight(originalWeight);
                double gradientWeight = deltaCost / h;



                double originalBias = neuron->getBias();
                neuron->setBias(originalBias + h);
                ForwardPropagation();
                for (Neuron *neuron2 : _outputLayer->getNeurons())
                {
                    calculatedOutputs.push_back(neuron2->getOutput());
                }
                deltaCost = DataCost2(_dataset, calculatedOutputs) - originalCost;
                calculatedOutputs.clear();


                neuron->setBias(originalBias);
                double gradientBias = deltaCost / h;


                //std::cout << "GradientWeight: " << gradientWeight << ", Gradient Bias: " << gradientBias << std::endl;
                gradientWeightAvg += (originalWeight - _learningRate * gradientWeight);
                gradientBiasAvg += (originalBias - _learningRate * gradientBias);

            }
        }
    }
    int i = 0;
    for (Layer *layer : _layers)
    {
        for (Neuron *neuron : layer->getNeurons())
        {
            for (Connection *connection : neuron->getConnections())
            {

                connection->setWeight(connection->getWeight() + gradientWeightAvg);
                neuron->setBias(neuron->getBias() + gradientBiasAvg);
                i++;
            }
        }

    }


}


void NeuralNetwork::updateDataset()
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
}

void NeuralNetwork::train() {
    
    // std::vector<double> calculatedOutputs;
    // for (Neuron *neuron2 : _outputLayer->getNeurons())
    // {
    //     calculatedOutputs.push_back(neuron2->getOutput());
    // }
    // std::cout << "Cost::: " << DataCost2(_dataset, calculatedOutputs) << std::endl;

 //   updateDataset();
    learn();

    

}