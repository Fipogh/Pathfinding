#include "Cell.h"
#include "GUI.h"
#include<unistd.h>
std::vector<std::vector<Cell*>> Cell::Cells;
Cell* Cell::StartCell;
Cell* Cell::EndCell;
int Cell::Size_X;
int Cell::Size_Y;
double Cell::max_f;
void Cell::CalcValues()
{
    sf::Vector2<int> temp = pos - Cell::StartCell->pos;
    g_value = std::hypot(temp.x, temp.y);
    temp = pos - Cell::EndCell->pos;
    h_value = std::hypot(temp.x, temp.y);
    f_value = g_value + h_value;
    if (f_value > Cell::max_f) Cell::max_f = f_value;
}
Cell::Cell(sf::Vector2<int> pos) : pos(pos) {type = Unknown;}
Cell::Cell(int x, int y)
{
    pos.x = x;
    pos.y = y;
    type = Unknown;
}

void Cell::ExposeNearby(std::vector<Cell*>& exposed)
{
    if (this->pos.x-1 >= 0)
    {
        if (Cells[this->pos.x-1][this->pos.y]->type==CellType::Unknown)
        {
            Cells[this->pos.x - 1][this->pos.y]->Expose();
            exposed.push_back(Cells[this->pos.x - 1][this->pos.y]);
        }
    }
    if (this->pos.x+1 < Cell::Size_X)
    {
        if (Cells[this->pos.x+1][this->pos.y]->type==CellType::Unknown)
        {
            Cells[this->pos.x + 1][this->pos.y]->Expose();
            exposed.push_back(Cells[this->pos.x + 1][this->pos.y]);
        }
    }
    if (this->pos.y-1 >= 0)
    {
        if (Cells[this->pos.x][this->pos.y-1]->type==CellType::Unknown)
        {
            Cells[this->pos.x][this->pos.y - 1]->Expose();
            exposed.push_back(Cells[this->pos.x][this->pos.y - 1]);
        }
    }
    if (this->pos.y+1 < Cell::Size_Y)
    {
        if (Cells[this->pos.x][this->pos.y + 1]->type == CellType::Unknown)
        {
            Cells[this->pos.x][this->pos.y + 1]->Expose();
            exposed.push_back(Cells[this->pos.x][this->pos.y + 1]);
        }
    }
    if (((this->pos.x+1==Cell::EndCell->pos.x)&(this->pos.y==Cell::EndCell->pos.y))||
    ((this->pos.x-1==Cell::EndCell->pos.x)&(this->pos.y==Cell::EndCell->pos.y))||
    ((this->pos.x==Cell::EndCell->pos.x)&(this->pos.y+1==Cell::EndCell->pos.y))||
    ((this->pos.x==Cell::EndCell->pos.x)&(this->pos.y-1==Cell::EndCell->pos.y)))
    {
        Cell::EndCell->type = CellType::End_Discovered;
    }
}

void LogVec(std::vector<Cell*>& arr)
{
    for (auto i = arr.begin(); i != arr.end(); i++)
    {
        std::cout << (*i)->GetPos().x << ", " << (*i)->GetPos().y << std::endl;
    }
}
struct MinCellAndInd
{
    Cell* MinCell;
    int MinInd;
};
MinCellAndInd FindMin(std::vector<Cell*>& arr)
{
    MinCellAndInd buffer;
    buffer.MinCell = arr[0];
    buffer.MinInd = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i]->f_value < buffer.MinCell->f_value) {
            buffer.MinCell = arr[i];
            buffer.MinInd = i;
        }
        else if (arr[i]->f_value == buffer.MinCell->f_value)
        {
            if (arr[i]->h_value < buffer.MinCell->h_value)
            {
                buffer.MinCell = arr[i];
                buffer.MinInd = i;
            }
        }
    }
    return buffer;
}

void Cell::DeployAlgorithm()
{
    std::vector<Cell*> exposed;
    Cell::StartCell->ExposeNearby(exposed);
    MinCellAndInd buffer = FindMin(exposed);
    buffer.MinCell->Discover();
    buffer.MinCell->ExposeNearby(exposed);
    exposed.erase(exposed.begin()+buffer.MinInd);
    while (Cell::EndCell->type!=CellType::End_Discovered)
    {
        buffer = FindMin(exposed);
        buffer.MinCell->Discover();
        buffer.MinCell->ExposeNearby(exposed);
        exposed.erase(exposed.begin()+buffer.MinInd);
    }
}
void Cell::Expose()
{
    CalcValues();
    type = CellType::Exposed;
}
void Cell::Discover()
{
    if (type!=CellType::Exposed) CalcValues();
    type = CellType::Discovered;
}

void Cell::SelectStartEndCells(std::vector<std::vector<Cell *>> &cells)
{
    int rpx = rand() % Cell::Size_X;
    int rpy = rand() % Cell::Size_X;
    cells[rpx][rpy]->type = CellType::Start; //Mark start cell
    Cell::StartCell = cells[rpx][rpy];

    while (true) // Check if  EndCell != StartCell
    {
        srand(time(0));
        if (cells[rand() % Cell::Size_X][rand() % Cell::Size_Y]->type == CellType::Start) continue;
        else
        {
            int rpx = rand() % Cell::Size_X;
            int rpy = rand() % Cell::Size_Y;
            cells[rpx][rpy]->type = CellType::End;
            Cell::EndCell = cells[rpx][rpy];
        }
        break;
    }
}

std::vector<std::vector<Cell*>> Cell::GenerateCells()
{
    Cell::Size_X = GUI::width/(GUI::scale*5);
    Cell::Size_Y = GUI::height/(GUI::scale*5);
    std::vector<std::vector<Cell*>> arr(Cell::Size_X, std::vector<Cell*>(Cell::Size_Y));
    for (int i = 0; i < Cell::Size_X; i++) {
        for (int j = 0; j < Cell::Size_Y; j++) {
            arr[i][j] = new Cell(i, j);
        }
    }
    SelectStartEndCells(arr);
    return arr;
}

void Cell::DiscoverAll()
{
    for (auto i: Cell::Cells) for (Cell* j : i)
    {
        if (j->type==CellType::Unknown) j->Discover();
    }
}

const sf::Vector2<int> Cell::GetPos() const
{
    return pos;
}
