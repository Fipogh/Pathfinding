#include "Cell.h"

void Cell::CalcValues()
{
    g_value = Vector2<int>::Distance(pos, StartCell->pos);
    h_value = Vector2<int>::Distance(pos, EndCell->pos);
    f_value = g_value + h_value;
}

Cell::Cell(int x, int y)
{
    pos.x = x;
    pos.y = y;
    CalcValues();
}
