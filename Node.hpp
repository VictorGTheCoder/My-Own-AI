#include <iostream>
#include <vector>
#include <cmath>


class Node
{
	private:
		double _output;
		
	public:
		Node();
		~Node();
		void setOutput(double value);
		double getOutput() const;

};
