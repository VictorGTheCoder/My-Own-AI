#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>
#include <memory>

#include "../include/Neuron.hpp"

class Layer
{
    private:
        std::vector<Neuron *> _Neurons;
        int _size; // Layer size

    public:
        Layer(int numberOfNeurons);
        ~Layer();
		void ComputeOutputs();
		void setConnections(Layer* previousLayer);
        void displayLayer();


        std::vector<Neuron *> getNeurons() const;
        int getSize() const;

        // void setNeurons(std::vector<Neuron *> neurons);
        // void setSize(int size);

        // Méthodes pour initialiser les nœuds, définir les entrées/sorties, etc.
};


#endif