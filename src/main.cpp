#include "../include/NeuralNetwork.hpp"




int main()
{


	std::vector<Data> dataset = createDataSet();


	std::vector<int> t({4, 3});
	std::vector<double> inputs({1, 1});

	NeuralNetwork *NN = new NeuralNetwork(t);



	NN->createNetwork(inputs);


	NN->displayNetwork();

	NN->ForwardPropagation();

	NN->displayNetwork();

	delete NN;
	return 0;
}
