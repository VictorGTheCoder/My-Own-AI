#include <fstream>
#include <vector>
#include <iostream>
#include "Data.hpp"

void read_mnist_images(std::string full_path, std::vector<std::vector<unsigned char>>& images);
void read_mnist_labels(std::string full_path, std::vector<unsigned char>& labels);

std::vector<Data> create_mnist_dataset(std::vector<std::vector<unsigned char>> images, std::vector<unsigned char> labels);