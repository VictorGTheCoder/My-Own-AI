#include <random>


double generateRandomNumber() {
    // Random number generator
    std::random_device rd;  // Obtain a random number from hardware
    std::mt19937 gen(rd()); // Seed the generator
    std::uniform_real_distribution<> distr(-1, 1); // Define the range

    // Generate and output a random number
    double random_number = distr(gen);
    (void ) random_number;
    return 0.45;
}