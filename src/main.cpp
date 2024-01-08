#include "../include/NeuralNetwork.hpp"
#include "../include/Draw.hpp"
#include <fstream>
#include <vector>
// Other necessary includes

void exportForVisualization(NeuralNetwork* NN, const std::vector<Data>& dataset, const std::string& filename) {
    std::ofstream file(filename);

    // Define the range and resolution for the grid
    double x_min = 0;
    double x_max = 6;
    double y_min = 0;
    double y_max = 6;
    double resolution = 0.10;

    // Export grid points and their predicted classes
    for(double x = x_min; x <= x_max; x += resolution) {
        for(double y = y_min; y <= y_max; y += resolution) {
            std::vector<double> point = {x, y};
            int predicted_class = NN->predict(point); // Adjust according to your NN's predict function
            file << x << "," << y << "," << predicted_class << std::endl;
        }
    }

    // Export original dataset points
    for(const auto& data : dataset) {
        double x = data.input[0];
        double y = data.input[1];

        //int actual_class = /* class from data */;
        file << x << "," << y << "," << 1 << ",dataset" << std::endl;
    }

    file.close();
}


int main()
{

	//drawWindow();

	std::vector<Data> dataset = createDataSet();

	// std::vector<Data> dataset2 = createDataSet();

	// Data data = {std::vector<double>({0, 1}), std::vector<double>({0,0,1})};
	// Data data2 = {std::vector<double>({1, 0}), std::vector<double>({0,1,0})};
	// Data data3 = {std::vector<double>({1, 1}), std::vector<double>({0,0,1})};
	// Data data4 = {std::vector<double>({1, 0}), std::vector<double>({0,0,1})};
	// Data data5 = {std::vector<double>({1, 1}), std::vector<double>({0,1,1})};

	// dataset.clear();
	// dataset2.clear();

	// dataset.push_back(data);
	// dataset2.push_back(data2);
	// dataset.push_back(data2);
	// dataset.push_back(data3);
	// dataset.push_back(data4);
	// dataset.push_back(data5);


	// (void ) dataset2;

	std::vector<int> t({3, 10});
	// //std::vector<double> inputs({1, 1});

	NeuralNetwork *NN = new NeuralNetwork(t);

	NN->createNetwork(dataset);


	// NN->displayNetwork();


	// //NN->predictDataSet(dataset);
	// //NN->predictData(data);

	//NN->train();



	//NN->saveModel("PetalModel2.json");
	//NN->displayNetwork();
	NN->loadModel("PetalModel2.json");
	NN->displayNetwork();
	// //NN->predictData(data);
	// //NN->predictDataSet(dataset);
	// exportForVisualization(NN, dataset, "output.csv");
	// //NN->ForwardPropagation();

	// //NN->learn();

	// //NN->displayLastLayer();
	// //NN->displayNetwork();

	delete NN;
	return 0;
}
