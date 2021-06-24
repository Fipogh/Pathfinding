#include "GUI.h"
#include "Cell.h"
#include <thread>

int main()
{
    srand(time(0));
    std::thread Window(GUI::Start);
    std::cin.get();
    Cell::DeployAlgorithm();
    Window.join();


}
