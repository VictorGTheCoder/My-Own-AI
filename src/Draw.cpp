#include "../include/Draw.hpp"
#include "../include/NeuralNetwork.hpp"

const int WINDOW_SIZE = 625;
const int GRID_SIZE = 25;
const int PIXEL_SIZE = WINDOW_SIZE / GRID_SIZE; // Each "pixel" is a 40x40 block

// Represents the drawing grid
std::vector<std::vector<bool>> drawingGrid(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));

void DrawGridPixel(sf::RenderWindow& window, int gridX, int gridY) {
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
    rect.setFillColor(sf::Color::White);

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

void preProcessEvaluatingDigit()
{
    std::vector<double> image;
    for (std::vector<bool> v : drawingGrid)
    {
        for (bool p : v)
        {
            if (p)
                image.push_back(1.0);
            else
                image.push_back(0.0);
        }
    }
    std::vector<int> t({20,10});
    
    NeuralNetwork *NN = new NeuralNetwork(t);

    std::vector<Data> d;
    Data data;
    data.input = image;
    d.push_back(data);

    NN->createNetwork(d);

    NN->predict(image);
}

int drawWindow() {
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
                DrawGridPixel(window, mousePos.x / PIXEL_SIZE, mousePos.y / PIXEL_SIZE);
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                mouseButtonDown = false;
                modif = true;
                GetGridState();
                std::thread nnThread(preProcessEvaluatingDigit);
                nnThread.detach();
            }
            if (event.type == sf::Event::MouseMoved && mouseButtonDown) {
                modif = true;
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                DrawGridPixel(window, mousePos.x / PIXEL_SIZE, mousePos.y / PIXEL_SIZE);
            }
        }

        if (modif)
        {
            window.clear(sf::Color::Black); // Clear the screen with black

            for (int i = 0; i < GRID_SIZE; ++i) {
                for (int j = 0; j < GRID_SIZE; ++j) {
                    if (drawingGrid[i][j]) {
                        DrawGridPixel(window, i, j);
                    }
                }
            }
            window.display();
            modif = false;
        }
    }

    return 0;
}
