#pragma once
#include "Vector2.h"
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
    double g_value, h_value, f_value;
    Vector2<int> pos;
    void CalcValues();
public:
    Cell(int x, int y);
    Cell(Vector2<int> pos) : pos(pos) {CalcValues();}

};

extern Cell* StartCell;
extern Cell* EndCell;