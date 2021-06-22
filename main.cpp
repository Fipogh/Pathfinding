#include "GUI.h"
#include "Cell.h"
#include <thread>
Cell* StartCell;
Cell* EndCell;


int main()
{
    srand(time(0));
    std::thread Window(GUI::Start);
    std::cin.get();

    Cell::DiscoverAll();

    Window.join();


}
