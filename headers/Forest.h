#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include<Region.h>

#ifndef FOREST_H
#define FOREST_H

namespace forest_class
{
    using std::map,std::cout,std::endl,std::pair,std::string,std::ofstream;
}

using namespace forest_class;

struct forest
{ 
    // The grid which contains the regions of the forest
    map<pair<int,int>,region*> regions;
       int x_dim;   // X dimension of the forest
       int y_dim;   // y dimensino fo the forest
       int timesteps;  // Timesteps of the simulation in hours
    
    // Construct a forest of x and y dimension. MUST BE USER SPECIFIED
    forest(int x, int y);
    ~forest();
    
    // Helper function for the constructor, creates regions
    void createRegions();
    // Helper function for the constructor, sets north and south pointers, ie it links our linked list
    void setNorthSouthPtrs();
    // See comment on setNorthSouthPtrs
    void setEastWestPtrs();
    // Sets burning true on a random node
    void lightning_strike();
    // Constructs fire stations on a random node
    void assignStation();
    // Runs the simulation
    void runSimulation(int timesteps, int firestations, int wind, int numStrikes);
    // Outputs information after the fire has burned all the way
    void report(int fullFire, int burnt);
    // Outputs a visual map of the fire
    void printMap(bool isCout, ofstream& writeTo);
    // Flags a certain time stamp's report
    void checkpoint(int numBurnt, int numBurning, int day);
    // Outputs the complete log of the fire burning
    void exportLog(string timestep, int numBurnt, int numBurning, int newIgnites, int newBurns);
};


#endif
