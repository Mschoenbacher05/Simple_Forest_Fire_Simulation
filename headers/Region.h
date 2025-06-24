#include <iostream>
#ifndef REGION_H
#define REGION_H
#include "FireStation.h"



class region
{
private:
    //Pointer to the region to the north. (Or Null)
    region *north;
    //Pointer to the region to the south. (Or Null)
    region *south;
    //Pointer to the region to the east. (Or Null)
    region *east;
    //Pointer to the region to the west. (Or Null)
    region *west;
    //True: region is on fire. False: region is not on fire.
    bool isOnFire;
    //how much burning is left (0 burnt out; 100 untouched; 50 halfway burnt)
    int burningLeft;
    //how wet the region is (0 completely dry; 100 completely wet; 50 halfway wet)
    int wetness;
    //how dense the region is(0 very sparse; 100 very dense; 50 kinda dense)
    int density;
    // Does this node have a firestation
    bool hasStation;
    // It's firestation if any
    FireStation* station;
    // Does this have a deployed team
    bool teamDeployed;
    // Does this have team
    FireTeam* team;
public:
    //constructors
    region();
    region(int wetness, int density);
    ~region();



    //getters and setters
    region* getNorth();
    region* getSouth();
    region* getEast();
    region* getWest();
    FireStation* getStation();
    FireTeam* getTeam();
    bool getFire();
    int getBurningLeft();
    int getWetness();
    int getDensity();
    bool getTeamDeployed();
    bool getHasStation();
    void setNorth(region* region);
    void setSouth(region* region);
    void setEast(region* region);
    void setWest(region* region);
    void setFire(bool input);
    void setBurningLeft(int input);
    void setWetness(int input);
    void setDensity(int input);
    void setHasStation(bool input);
    void setStation(FireStation* input);
    void setTeamDeployed(bool input);
    void setTeam(FireTeam* input);




    //other behaviors
    //firefighters increased wetness and decreased density
    void fortify();
    //firefighters put out the fire
    void extinguish();
    //checks whether to catch fire, decrease wetness, or continues burning. Returns is burning or not
    bool update(int wind);

    // Helper function for update checks if it has a station and acts accordingly if it does
    void stationCheck();
    // Helper function for update Checks if a team is deployed and acts
    // TODO write team check with code currently in update
    void teamCheck();
    //sub function of update. Checks region for fire
    void update_Check_Burn(int wind, region * check);
};

#endif