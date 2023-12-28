#ifndef CONNECTION_HPP
#define CONNECTION_HPP

class Neuron;

class Connection
{
    private:
        Neuron* fromNeuron;
        Neuron* toNeuron;
        double _weight;
        double _bias;

    public:
        Connection(Neuron* from, Neuron* to);
        void setWeight(double w);
        void setBias(double b);
        void propagate();
};

#endif // CONNECTION_HPP
