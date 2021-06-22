#include "GUI.h"
std::vector<std::vector<Cell*>> GUI::Cells = Cell::GenerateCells();
void GUI::Start()
{
    GUI::Cells = Cell::GenerateCells();
    sf::RenderWindow window(sf::VideoMode(width, height), "Pathfinding");
    while (window.isOpen())
    {
        ProcessEvents(window);
        Draw(window);
    }
}


void GUI::Draw(sf::RenderWindow& window)
{
    window.clear();
    for (auto i: GUI::Cells) for (Cell* j: i)
    {
        sf::RectangleShape rct(sf::Vector2f(CellSize,CellSize));
        rct.setPosition(j->GetPos());
        rct.setOutlineColor(sf::Color::Black);
        switch (j->type)
        {
            case CellType::Start:
                rct.setFillColor(sf::Color::Green);
                break;
            case CellType::End:
                rct.setFillColor(sf::Color::Red);
                break;
            case CellType::Discovered:
                rct.setFillColor(sf::Color(255, 255, 0, (j->f_value/Cell::max_f)*255));
                break;
            default:
                rct.setFillColor(sf::Color::White);
                break;
        }
        rct.setOutlineThickness(1);
        window.draw(rct);
    }
    window.display();
}


void GUI::ProcessEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}