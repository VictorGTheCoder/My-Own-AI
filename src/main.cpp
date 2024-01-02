#include "../include/NeuralNetwork.hpp"




int main()
{


	std::vector<Data> dataset = createDataSet();

	// Data data = {std::vector<double>({0, 1}), std::vector<double>({0,0,1})};
	// Data data2 = {std::vector<double>({1, 0}), std::vector<double>({0,0,1})};
	// Data data3 = {std::vector<double>({1, 1}), std::vector<double>({0,0,1})};
	// Data data4 = {std::vector<double>({1, 0}), std::vector<double>({0,0,1})};
	// Data data5 = {std::vector<double>({1, 1}), std::vector<double>({0,1,1})};

	// dataset.clear();
	// dataset.push_back(data);
	// dataset.push_back(data2);
	// dataset.push_back(data3);
	// dataset.push_back(data4);
	// dataset.push_back(data5);



	std::vector<int> t({4, 3});
	//std::vector<double> inputs({1, 1});

	NeuralNetwork *NN = new NeuralNetwork(t);



	NN->createNetwork(dataset);


//	NN->displayLastLayer();


	NN->predictDataSet(dataset);

	NN->train();


	NN->predictDataSet(dataset);
	//NN->ForwardPropagation();

	//NN->learn();

	NN->displayLastLayer();
	//NN->displayNetwork();

	delete NN;
	return 0;
}
