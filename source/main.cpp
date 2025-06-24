#include "Forest.h"
#include "Region.h"
#include <cstdlib>
#include <ctime>
#include <filesystem>
// remember to set random seed

namespace fs = std::filesystem;

void mainMenu();

int main()
{
    // Set seed
    srand(time(NULL));
    // Create log folder
    std::filesystem::create_directory("./log");

    mainMenu();

    // Delete log folder after user prompt
    char a;
    cout << "enter any key to delete logs: ";
    std::cin >> a;
    std::filesystem::remove_all("./log");

    return 0;
}

void mainMenu()
{
    int x, y;
    cout << "Forest x dimension: ";
    std::cin >> x;
    cout << "Forest y dimension: ";
    std::cin >> y;
    forest whitville_forest(x, y);

    int t, w, s, f;
    cout << "Max timesteps: ";
    std::cin >> t;
    cout << "Wind speed: ";
    std::cin >> w;
    cout << "# of lightning strikes: ";
    std::cin >> s;
    cout << "# of firestations: ";
    std::cin >> f;
    whitville_forest.runSimulation(t, f, w, s);
}