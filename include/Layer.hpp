#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <memory>
#include "ActivationFunction.hpp"
#include "../include/Neuron.hpp"
#include "Color.hpp"

using LayerActivationFunction = double(*)(double);
using LayerActivationFunctionDerivative = double(*)(double);

class Layer
{
    private:
        std::vector<Neuron *> _Neurons;
        std::vector<double>  _weights;
        int _size; // Layer size
        LayerActivationFunction _activationFunction;
        LayerActivationFunctionDerivative _activationFunctionDerivative;

    public:
        Layer(int numberOfNeurons);
        ~Layer();
		void ComputeOutputs();
		void setConnections(Layer* previousLayer);
        void displayLayer();


        std::vector<Neuron *> getNeurons() const;
        int getSize() const;

        void setActivationFunction(LayerActivationFunction activationFunction, LayerActivationFunctionDerivative activationFunctionDerivative);

        double ActivationFunction(double input);
        double ActivationFunctionDerivative(double input);




        // void setNeurons(std::vector<Neuron *> neurons);
        // void setSize(int size);

        // Méthodes pour initialiser les nœuds, définir les entrées/sorties, etc.
};


#endif