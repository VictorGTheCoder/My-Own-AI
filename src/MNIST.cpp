#include "../include/MNIST.hpp"
#include "../include/Color.hpp"

using std::cout, std::endl;


int reverseInt(int i) {
    unsigned char c1, c2, c3, c4;
    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;
    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

void read_mnist_images(std::string full_path, std::vector<std::vector<unsigned char>>& images) {
    std::ifstream file(full_path, std::ios::binary);
    if (file.is_open()) {
        int magic_number = 0;
        int number_of_images = 0;
        int rows = 0;
        int cols = 0;
        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images = reverseInt(number_of_images);
        file.read((char*)&rows, sizeof(rows));
        rows = reverseInt(rows);
        file.read((char*)&cols, sizeof(cols));
        cols = reverseInt(cols);
        for(int i = 0; i < number_of_images; ++i) {
            std::vector<unsigned char> tp;
            for(int r = 0; r < rows; ++r) {
                for(int c = 0; c < cols; ++c) {
                    unsigned char temp = 0;
                    file.read((char*)&temp, sizeof(temp));
                    tp.push_back(temp);
                }
            }
            images.push_back(tp);
        }
    }
	else
	{
		cout << "Can't read file: " << full_path << endl;
	}
}

void read_mnist_labels(std::string full_path, std::vector<unsigned char>& labels) {
    std::ifstream file(full_path, std::ios::binary);
    if (file.is_open()) {
        int magic_number = 0;
        int number_of_labels = 0;
        file.read((char*)&magic_number, sizeof(magic_number));
        magic_number = reverseInt(magic_number);
        file.read((char*)&number_of_labels, sizeof(number_of_labels));
        number_of_labels = reverseInt(number_of_labels);
        for (int i = 0; i < number_of_labels; ++i) {
            unsigned char temp = 0;
            file.read((char*)&temp, sizeof(temp));
            labels.push_back(temp);
        }
    }
    else {
        cout << "Can't read file: " << full_path << endl;
    }
}

std::vector<Data> create_mnist_dataset(std::vector<std::vector<unsigned char>> images, std::vector<unsigned char> labels)
{
	std::vector<Data> dataset;
	dataset.reserve(images.size());

	for (std::size_t i = 0; i < images.size(); i++)
	{
		Data current_data;
		current_data.input.reserve(images[i].size()); // Reserve memory for efficiency, if size is known.
		for (unsigned char pixel : images[i])
			current_data.input.push_back(static_cast<double>(pixel));
	
		current_data.expectedOutput = std::vector<double>(10, 0.0); // Initialize with 0.0
		if (labels[i] < 10)
			current_data.expectedOutput[labels[i]] = 1.0;
		else
		{
			cout << COLOR_RED << "[ERROR]" << COLOR_RESET << " Label value out of range" << endl;
			continue; // Skip this data point or handle the error as appropriate
		}

		dataset.push_back(current_data);
	}
	return dataset;
}
