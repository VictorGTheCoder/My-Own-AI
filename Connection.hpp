#include "Node.hpp"

class Connection
{
    private:
        Node* fromNode;
        Node* toNode;
        double _weight;
        double _bias;

    public:
        Connection(Node* from, Node* to);
        void setWeight(double w);
        void setBias(double b);
        void propagate();
};

Connection::Connection(Node* from, Node* to) : fromNode(from), toNode(to), _weight(0.0), _bias(0.0) {}

void Connection::setWeight(double w) {
    _weight = w;
}

void Connection::setBias(double b) {
    _bias = b;
}

void Connection::propagate() {
    double input = fromNode->getOutput();
    double output = (input * _weight) + _bias;
    // Ici, vous pouvez appliquer une fonction d'activation si nécessaire
    toNode->setOutput(output);
}
