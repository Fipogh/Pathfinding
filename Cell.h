#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
enum CellType{
    Start,
    End,
    Wall,
    Discovered,
    Unknown
};
class Cell
{
private:
    sf::Vector2<float> pos;
    void CalcValues();
public:
    double g_value, h_value, f_value;
    static inline double max_f = 0;
    CellType type;
    Cell(float x, float y);
    Cell(sf::Vector2<float> pos);
    void Discover();
    static void DiscoverAll();
    const sf::Vector2<float> GetPos() const;
    static std::vector<std::vector<Cell*>> GenerateCells();
};
extern Cell* StartCell;
extern Cell* EndCell;
