#pragma once
#include <vector>
#include <cmath>
#include <iostream>
#include <SFML/System/Vector2.hpp>
enum CellType{
    Start,
    End,
    End_Discovered,
    Wall,
    Discovered,
    Unknown,
    Exposed
};
class Cell
{
private:
    sf::Vector2<int> pos;
    void CalcValues();
    static void SelectStartEndCells(std::vector<std::vector<Cell*>>& cells);
public:
    static Cell* StartCell, *EndCell;
    static std::vector<std::vector<Cell*>> Cells;
    static int Size_X, Size_Y;
    double g_value, h_value, f_value;
    static double max_f;
    CellType type;
    Cell(int x, int y);
    Cell(sf::Vector2<int> pos);
    void Discover();
    void Expose();
    void ExposeNearby(std::vector<Cell*>& discovered);
    static void DiscoverAll();
    static void DeployAlgorithm();
    const sf::Vector2<int> GetPos() const;
    static std::vector<std::vector<Cell*>> GenerateCells();
};