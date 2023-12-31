#include "../include/NeuralNetwork.hpp"




int main()
{


	std::vector<Data> dataset = createDataSet();

	Data data = {std::vector<double>({1, 1}), std::vector<double>({0,0,1}), std::vector<double>({0, 0, 0})};

	dataset.clear();
	dataset.push_back(data);

	std::vector<int> t({4, 3});
	//std::vector<double> inputs({1, 1});

	NeuralNetwork *NN = new NeuralNetwork(t);



	NN->createNetwork(dataset);


	NN->displayLastLayer();


	NN->train();

	NN->ForwardPropagation();

	//NN->learn();

	NN->displayLastLayer();
	//NN->displayNetwork();

	delete NN;
	return 0;
}
