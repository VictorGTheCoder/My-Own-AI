#include "../include/Draw.hpp"
#include "../include/NeuralNetwork.hpp"

const int WINDOW_SIZE = 784;
const int GRID_SIZE = 28;
const int PIXEL_SIZE = WINDOW_SIZE / GRID_SIZE; // Each "pixel" is a 40x40 block

// Represents the drawing grid
std::vector<std::vector<double>> drawingGrid(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));


void DrawGridPixel(sf::RenderWindow& window, int gridX, int gridY, double intensity) {
    // Check if the coordinates are within the grid bounds
    if (gridX < 0 || gridX >= GRID_SIZE || gridY < 0 || gridY >= GRID_SIZE) {
        return;
    }

    // Calculate the actual pixel coordinates
    int x = gridX * PIXEL_SIZE;
    int y = gridY * PIXEL_SIZE;

    // Create a rectangle shape to represent the "pixel"
    sf::RectangleShape rect(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
    rect.setPosition(x, y);
    int colorValue = static_cast<int>(intensity * 255);
    rect.setFillColor(sf::Color(colorValue, colorValue, colorValue));

    // Draw the rectangle to the window
    window.draw(rect);

    drawingGrid[gridX][gridY] = true;
}


void GetGridState() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            std::cout << drawingGrid[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

void preProcessEvaluatingDigit(NeuralNetwork *NN)
{
    std::vector<double> image;
    for (std::vector<double> v : drawingGrid)
    {
        for (bool p : v)
        {
            if (p)
                image.push_back(1.0);
            else
                image.push_back(0.0);
        }
    }
    // std::vector<int> t({20,10});
    
    // NeuralNetwork *NN = new NeuralNetwork();

	//std::vector<double> inputlayer = {2,3};

	//NN->setInputLayer(inputlayer);
	//NN->createNetwork(t);

    // NN->createNetwork(t);

    NN->predict(image);

}

void ApplyBlur(std::vector<std::vector<double>>& grid, double blendFactor) {
    std::vector<std::vector<double>> tempGrid = grid;

    for (int x = 1; x < GRID_SIZE - 1; ++x) {
        for (int y = 1; y < GRID_SIZE - 1; ++y) {
            double sum = 0.0;
            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    sum += tempGrid[x + dx][y + dy];
                }
            }
            double average = sum / 9.0;
            grid[x][y] = grid[x][y] * (1 - blendFactor) + average * blendFactor;
        }
    }
}



int drawWindow(NeuralNetwork *NN) {
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML Drawing App");

    bool mouseButtonDown = false;
    bool modif = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                modif = true;
                mouseButtonDown = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                DrawGridPixel(window, mousePos.x / PIXEL_SIZE, mousePos.y / PIXEL_SIZE, 1.0);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mouseButtonDown = false;
                modif = true;
                ApplyBlur(drawingGrid, 0.5); // Apply blur effect
                GetGridState();
                std::thread nnThread(preProcessEvaluatingDigit, NN);
                nnThread.detach();
            }
            if (event.type == sf::Event::MouseMoved && mouseButtonDown) {
                modif = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                DrawGridPixel(window, mousePos.x / PIXEL_SIZE, mousePos.y / PIXEL_SIZE, 1.0);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                for (int i = 0; i < GRID_SIZE; ++i)
                    for (int j = 0; j < GRID_SIZE; ++j)
                        drawingGrid[i][j] = 0;
                modif = true;
            }
        }

        if (modif)
        {


            window.clear(sf::Color::Black); // Clear the screen with black
            //

            for (int i = 0; i < GRID_SIZE; ++i) {
                for (int j = 0; j < GRID_SIZE; ++j) {
                    if (drawingGrid[i][j]) {
                        DrawGridPixel(window, i, j, drawingGrid[i][j]);
                    }
                }
            }
            window.display();
            modif = false;
        }
    }

    return 0;
}
