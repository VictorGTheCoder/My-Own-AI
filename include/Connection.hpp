#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include "../include/utils.hpp"
#include "../include/ActivationFunction.hpp"

class Neuron;

class Connection
{
    private:
        Neuron *fromNeuron;
        Neuron *toNeuron;
        double _weight;

    public:
        Connection(Neuron* from, Neuron* to);
        ~Connection();
        void setWeight(double w);
        double getWeight() const;
        double computeConnection();
};

#endif // CONNECTION_HPP
