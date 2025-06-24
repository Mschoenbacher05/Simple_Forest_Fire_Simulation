#include "FireStation.h"
#include "Region.h"

FireStation::FireStation()
{
    queuesize = 0;
}

FireStation::FireStation(int teamSize)
{
    queuesize = teamSize;
    formQueue();
}

// Creates each queue
void FireStation::formQueue()
{
    for (int i = 1; i <= queuesize; i++)
    {
        // The efficiency of a fire team scales with the spot in the queue they are in
        
        FireTeam* north = new FireTeam(rand() % (i * 10),100 - (i * 10)); 
        fire_team_north.push(north); 
        
        FireTeam* south = new FireTeam(rand() % (i * 10),100 - (i * 10)); 
        fire_team_south.push(south); 

        FireTeam* east = new FireTeam(rand() % (i * 10),100 - (i * 10)); 
        fire_team_east.push(east); 

        FireTeam* west = new FireTeam(rand() % (i * 10),100 - (i * 10)); 
        fire_team_west.push(west); 
    }
    
}

// Destructor
FireStation::~FireStation()
{
    while(!fire_team_north.empty())
    {
        delete fire_team_north.front();
         
        fire_team_north.pop();
    }
    
    
    while (!fire_team_south.empty())
    {
        delete fire_team_south.front();
        fire_team_south.pop();
    }

    while (!fire_team_east.empty())
    {
        delete fire_team_east.front();
        fire_team_east.pop();
    }

    while (!fire_team_west.empty())
    {
        delete fire_team_west.front();
        fire_team_west.pop();
    }

}
