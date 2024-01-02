#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include "../include/utils.hpp"
#include "../include/ActivationFunction.hpp"

class Neuron;

class Connection
{
    private:
        double _weight;

    public:
        Neuron *fromNeuron;
        Neuron *toNeuron;
        Connection(Neuron* from, Neuron* to);
        ~Connection();
        void setWeight(double w);
        double getWeight() const;
        double computeConnection();
};

#endif // CONNECTION_HPP
