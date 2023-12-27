#include "Node.hpp"

Node::Node() : _output(0.0) {}

Node::~Node() {}

void Node::setOutput(double output) {_output = output;}

double Node::getOutput() const {return _output;}
