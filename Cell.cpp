#include "Cell.h"
#include "GUI.h"
void Cell::CalcValues()
{
    sf::Vector2<float> temp = pos - StartCell->pos;
    g_value = std::hypot(temp.x, temp.y);
    temp = pos - EndCell->pos;
    h_value = std::hypot(temp.x, temp.y);
    f_value = g_value + h_value;
    if (f_value > Cell::max_f) Cell::max_f = f_value;
}
Cell::Cell(sf::Vector2<float> pos) : pos(pos) {type = Unknown;}
Cell::Cell(float x, float y)
{
    pos.x = x;
    pos.y = y;
    type = Unknown;
}

void Cell::Discover()
{
    CalcValues();
    type = CellType::Discovered;
}

std::vector<std::vector<Cell*>> Cell::GenerateCells()
{
    int x = GUI::width/(GUI::scale*5);
    int y = GUI::height/(GUI::scale*5);
    std::vector<std::vector<Cell*>> arr(x, std::vector<Cell*>(y));
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            Cell *cell = new Cell(i * GUI::CellSize, j * GUI::CellSize);
            arr[i][j] = cell;
        }
    }
    int rpx = rand() % x;
    int rpy = rand() % y;

    arr[rpx][rpy]->type = CellType::Start;
    StartCell = arr[rpx][rpy];
    while (true)
    {
        srand(time(0));
        if (arr[rand() % x][rand() % y]->type == CellType::Start) continue;
        else
        {
            int rpx = rand() % x;
            int rpy = rand() % y;
            arr[rpx][rpy]->type = CellType::End;
            EndCell = arr[rpx][rpy];
        }
        break;
    }
    return arr;
}

void Cell::DiscoverAll()
{
    for (auto i: GUI::Cells) for (Cell* j : i)
    {
        if (j->type==CellType::Unknown) j->Discover();
    }
}

const sf::Vector2<float> Cell::GetPos() const
{
    return pos;
}
