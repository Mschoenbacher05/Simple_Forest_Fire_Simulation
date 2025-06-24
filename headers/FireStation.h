#include <queue>


#ifndef FIRE_STATION_H
#define FIRE_STATION_H
#include "FireTeam.h"

// Forward declaration of region since they depend on on another.
class region;

// FIRESTATION CHANGED TOA STRUCT FOR CLEAN ACCESS
struct FireStation
{   
    // A queue of 3 Fire teams. Each with different effeciency, activated at different times.
    std::queue<FireTeam*> fire_team_north;
    std::queue<FireTeam*> fire_team_south;
    std::queue<FireTeam*> fire_team_east;
    std::queue<FireTeam*> fire_team_west;
    std::queue<FireTeam*> fire_team_home;
    
    // How many teams to create. Does not need to be the 3 listed above.
    int queuesize;
    
    // Constructs a default firestation
    FireStation();
    // Creates a firestation with specific numbers of fire teams in the queues
    FireStation(int teamSize);

    void formQueue(); // Helper function for the constructor. Creates the fire teams.

    ~FireStation();
};


#endif