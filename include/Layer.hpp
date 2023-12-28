#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

#include "../include/Neuron.hpp"

class Layer
{
    private:
        std::vector<Neuron> _Neurons;
        int _size; // Layer size

    public:
        Layer(int numberOfNeurons);
		void ComputeOutputs(Neuron *Neuron);
		
        // Méthodes pour initialiser les nœuds, définir les entrées/sorties, etc.
};


#endif