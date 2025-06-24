#include "Region.h"

// constructors
region::region()
{
    north = NULL;
    south = NULL;
    east = NULL;
    west = NULL;
    isOnFire = false;
    burningLeft = 100;
    wetness = 50 + rand() % 50;
    density = rand() % 100;
    hasStation = false;
    station = NULL;
    team = NULL;
    teamDeployed = false;
}

region::region(int _wetness, int _density)
{
    north = NULL;
    south = NULL;
    east = NULL;
    west = NULL;
    isOnFire = false;
    burningLeft = 100;
    wetness = _wetness;
    density = _density;
    hasStation = false;
    team = NULL;
    teamDeployed = false;
}

// destroy the station
region::~region()
{
    delete station;
    station = NULL;
}
// getters and setters
region *region::getNorth()
{
    return north;
}
region *region::getSouth()
{
    return south;
}
region *region::getEast()
{
    return east;
}
region *region::getWest()
{
    return west;
}
FireStation *region::getStation()
{
    return station;
}
FireTeam *region::getTeam()
{
    return team;
}
bool region::getFire()
{
    return isOnFire;
}
int region::getBurningLeft()
{
    return burningLeft;
}
int region::getWetness()
{
    return wetness;
}
int region::getDensity()
{
    return density;
}
bool region::getTeamDeployed()
{
    return teamDeployed;
}
bool region::getHasStation()
{
    return hasStation;
}
void region::setNorth(region *input)
{
    north = input;
}
void region::setSouth(region *input)
{
    south = input;
}
void region::setEast(region *input)
{
    east = input;
}
void region::setWest(region *input)
{
    west = input;
}
void region::setFire(bool input)
{
    isOnFire = input;
}
void region::setBurningLeft(int input)
{
    burningLeft = input;
}
void region::setWetness(int input)
{
    wetness = input;
}
void region::setDensity(int input)
{
    density = input;
}
void region::setHasStation(bool input)
{
    hasStation = input;
}
void region::setStation(FireStation *input)
{
    station = input;
}
void region::setTeamDeployed(bool input)
{
    teamDeployed = input;
}
void region::setTeam(FireTeam *input)
{
    team = input;
}

// other behaviors
// firefighters increased wetness and decreased density
void region::fortify()
{
    if (density >= 30)
    {
        density -= 30;
    }
    else
    {
        density = 0;
    }

    if (wetness <= 50)
    {
        wetness += 50;
    }
    else
    {
        wetness = 100;
    }
    return;
}
// firefighters put out the fire
void region::extinguish()
{
    isOnFire = false;
    return;
}

// sub function of update. Checks region for fire
void region::update_Check_Burn(int wind, region *check)
{
    // If the region we are inspecting is a corner and thus is checking a null value do nothing
    if (check == NULL)
    {
        return;
    }
    // Check to see if this region is on fire and burning left is less than 90
    if (check->getFire() && check->getBurningLeft() < 90)
    {

        // if random chance hits
        if ((2 * ((rand() % 100) + wetness) - (density + wind)) < 30)
        {
            // light on fire.
            isOnFire = true;
            return;
        }
        else
        {
            // otherwise decrease wetness (1-5 no wind; 5-10 full wind)
            wetness -= ((rand() % 100) + wind) / 15;
        }
    }
}

// checks whether to catch fire, decrease wetness, or continues burning.
// For purposes of the burning regions attribute of the forest class, this function will return if it is burning or not to avoid needing to perform a map search to determine that.
bool region::update(int wind)
{
    // If this region has a station or active fire_team certain events need to happen
    stationCheck();
    teamCheck();

    // If it is not on fire and has not burnt out
    if (!isOnFire && burningLeft > 0)
    {
        // check surrounding regions to light this region on fire
        update_Check_Burn(wind, north);
        update_Check_Burn(wind, south);
        update_Check_Burn(wind, east);
        update_Check_Burn(wind, west);

        return isOnFire;
    }
    // else meaning the region is currently burning
    else
    {
        if (rand() % 15 == 0)
        {
            extinguish();
            return isOnFire;
        }

        // Adjust down the burning left varaivble (1-10 no wind; 10-20 full wind)
        burningLeft -= (((rand() % 100) + wind) / 10);
        // If we go below or to 0 inform us that the fire is out
        if (burningLeft <= 0)
        {
            burningLeft = 0;
            isOnFire = false;
        }
        return isOnFire;
    }
}

void region::stationCheck()
{
    // If this node has a fire station.
    if (hasStation)
    {
        // AT SOME POINT TRY TO FUNCTIONALIZE / GENERALIZE THIS INTO THE DEPLOY METHOD FOR FIRE STATIONS
        if (north != NULL)
        {
            // If the north is on fire, and the qeue is not empty and north's burnign left is less than or equal to activation
            if (north->getFire() && !station->fire_team_north.empty() && north->getBurningLeft() <= station->fire_team_north.front()->activation)
            {
                // Delete any team that is currently there to send out the new one
                delete north->getTeam();
                north->setTeam(NULL);

                // Set the team to the front of the north queue
                north->setTeam(station->fire_team_north.front());
                north->setTeamDeployed(true);

                // Pop off that element
                station->fire_team_north.pop();
                // Now a team has been deployed to the north point
            }
        }
        else if (south != NULL)
        {
            if (south->getFire() && !station->fire_team_south.empty() && south->getBurningLeft() <= station->fire_team_south.front()->activation)
            {
                delete south->getTeam();
                south->setTeam(NULL);

                // Set the team to the front of the south queue
                south->setTeam(station->fire_team_south.front());
                south->setTeamDeployed(true);

                // Pop off that element
                station->fire_team_south.pop();
                // Now a team has been deployed to the south point
            }
        }
        else if (east != NULL)
        {
            if (east->getFire() && !station->fire_team_east.empty() && east->getBurningLeft() <= station->fire_team_east.front()->activation)
            {
                delete east->getTeam();
                east->setTeam(NULL);

                // Set the team to the front of the north queue
                east->setTeam(station->fire_team_east.front());
                east->setTeamDeployed(true);

                // Pop off that element
                station->fire_team_east.pop();
                // Now a team has been deployed to the north point
            }
        }
        else if (west != NULL)
        {
            if (west->getFire() && !station->fire_team_west.empty() && west->getBurningLeft() <= station->fire_team_west.front()->activation)
            {
                delete west->getTeam();
                west->setTeam(NULL);
                // Set the team to the front of the north queue
                west->setTeam(station->fire_team_west.front());
                west->setTeamDeployed(true);
                // Pop off that element
                station->fire_team_west.pop();
                // Now a team has been deployed to the north point
            }
        }
        else if (isOnFire && !station->fire_team_home.empty() && burningLeft <= station->fire_team_home.front()->activation)
        {
            delete team;
            team = NULL;
            team = station->fire_team_home.front();
            teamDeployed = true;
            station->fire_team_home.pop();
        }

        // FINISH THIS

        // If on fire and burning left <= fireteam_direction->getActivation
        // fireteam_direction[element] = direction->Team
        // direction -> teamdeployedTrue
    }
}

void region::teamCheck()
{
    // If this region has a fireteam active
    if (teamDeployed)
    {
        // If the team can work (That is it has not worked more than a hard coded 24 hours) fortify if not delete it
        if (team->activeWorkTime != 24)
        {
            // If a region is on fire, there is a 25% chance firefighters extinguish the region. Otherwise tehy will just fortify
            if (isOnFire)
            {
                if (rand() % 4 == 0)
                {
                    extinguish();
                }
            }
            else
            {
                fortify();
            }
            // Increment work
            team->activeWorkTime++;
        }
        // Otherwise it is time to be deleted
        else
        {
            delete team;
            team = NULL;
            teamDeployed = false;
        }
    }
}