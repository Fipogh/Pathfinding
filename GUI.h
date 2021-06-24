#include "SFML/Graphics.hpp"
#include "Cell.h"
#pragma once
class GUI {
private:
    static void ProcessEvents(sf::RenderWindow& window);
public:
    static const int WindowScale = 2; // 1 for fullscreen; 2 for windowed;
    static const int scale = 5;  // 1 for 5, 2 for 10, 3 for 15, and so on;
    static const int CellSize = scale*5;  // 1 for 5, 2 for 10, 3 for 15, and so on;
    static const int width = 1920/WindowScale/CellSize*CellSize;
    static const int height = (width/16*9)/CellSize*CellSize;
    static void Draw(sf::RenderWindow& window);
    static void Start();
};