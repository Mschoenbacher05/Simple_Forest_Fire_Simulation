#include "Forest.h"
#include "Region.h"
#include "FireStation.h"
#include "FireTeam.h"

forest::forest(int x, int y)
{
    // Specify dimension
    x_dim = x;
    y_dim = y;

    createRegions();
    setEastWestPtrs();
    setNorthSouthPtrs();

    // // Output regions
    // for (int i = 0; i < x_dim; i++)
    // {
    //     for (int j = 0; j < y_dim; j++)
    //     {
    //         cout << "Region" << " (" << i << ", " << j << ")  " << regions[{i,j}]->getWetness() << endl;
    //     }
    // }
}

void forest::createRegions()
{
    // Create nodes
    for (int i = 0; i < x_dim; i++)
    {
        for (int j = 0; j < y_dim; j++)
        {
            //create a new region, and add it to the current loop location
            //This means that they are added across columns, then across rows. 
            region *added_region = new region;
            regions[std::make_pair(i, j)] = added_region;
        }
    }
}

/* Algorithm for setting direction pointers: */
// Essentially move up (through the y dimension)/ to the right (through the x dimension) and set North/East Pointers.
// Then move up/down starting at 1 region in that direction and set the south/east pointers. See offical documentation for graphic on how this works

/* Algorithm Psuedocode */
// For n less than max_dimension 1 value
//      for c less than max_dimension 2 value - 1
//          set the region at [(n,c) or (c,n) depending on which dimension you are moving through]'s North/East pointer to the the region at position (c,n+1)/(n,c+1)
void forest::setNorthSouthPtrs()
{
    for (int i = 0; i < x_dim; i++)
    {
        // Set north pointer
        for (int j = 0; j < y_dim - 1; j++) // From y = 0 up to ymax -1 set the north pointer to the region with the y value 1 above the current node
        {
            regions[{i, j}]->setNorth(regions[{i, j + 1}]);
        }

        // Set south pointers
        for (int j = 1; j < y_dim; j++) // Start at the y = 1 and assign south and then move the maximum y value
        {
            regions[{i, j}]->setSouth(regions[{i, j - 1}]);
        }
    }
}

void forest::setEastWestPtrs()
{
    // Set East pointers, note, same as above,
    for (int j = 0; j < y_dim; j++)
    {
        // Set north pointer
        for (int i = 0; i < x_dim - 1; i++) // From x = 0 up to xmax -1 set the east pointer to the region with the x value 1 above the current node
        {
            regions[{i, j}]->setEast(regions[{i + 1, j}]);
        }

        // Set south pointers
        for (int i = 1; i < x_dim; i++) // Start at  x = 1 and assign west and then move the maximum y value
        {
            regions[{i, j}]->setWest(regions[{i - 1, j}]);
        }
    }
}

// Catalyst for starting the simulation. Will be called in the runSimulation() function.
void forest::lightning_strike()
{

    // Pick an unlucky x cord
    int x_unlucky = rand() % x_dim;

    // unlucky y cord
    int y_unlucky = rand() % y_dim;

    // find that region in the map
    region *unlucky = regions[{x_unlucky, y_unlucky}];

    // Set it on fire
    unlucky->setFire(true);
    //useful for testing, not so much anymore. 
    //cout << "soemthing funny" << endl;
}

void forest::runSimulation(int maxSteps, int firestations, int wind = 50, int numStrikes = 1)
{
    // In order to enter for loop, nonzero number of regions must be burning.
    // Will be reset to zero before each iteration through map
    int numBurningRegions = numStrikes;

    // trackers reset to zero and incremented each timestep
    int numBurntRegions;
    int newIgnites;
    int oldBurns;

    // Strike with lightning
    for (int i = 0; i < numStrikes; i++)
    {
        // no guarantee that one region isn't struck twice.
        lightning_strike();
    }

    // Make sure there are not too many fireStations
    if (firestations > x_dim * y_dim)
    {
        firestations = x_dim * y_dim;
    }
    // Create fire stations
    for (int i = 0; i < firestations; i++)
    {
        // built in guarantee that a region won't be selected twice.
        assignStation();
    }

    // allBurning is the timestep where everything is on fire or already burnt.
    // Starts at 0, is set mid-simulation.
    // 0 at the end implies not everything caught fire.
    int allBurning = 0;

    for (int i = 0; i < maxSteps && numBurningRegions != 0; i++)
    {
        // Reset burn trackers
        numBurningRegions = 0;
        numBurntRegions = 0;
        newIgnites = 0;
        oldBurns = 0;

        // Iterate through the map
        for (map<pair<int, int>, region *>::iterator it = regions.begin(); it != regions.end(); it++)
        {
            if (it->second->getBurningLeft() == 0)
            {
                oldBurns++;
            }
            // update each function
            // update counters
            if (it->second->update(wind))
            {
                numBurningRegions++;
                if (it->second->getBurningLeft() == 100)
                {
                    newIgnites++;
                }
            }
            else if (it->second->getBurningLeft() == 0)
            {
                numBurntRegions++;
            }
        }
        // rough draft of the report function.
        // cout << "Timestep: " << i << " Number of burning: " << numBurningRegions << " Number of burnt: " << numBurntRegions << endl;
        
        // update the time steps
        timesteps = i;
        // calculate when the entire forest catches fire.
        if (allBurning == 0 && numBurningRegions + numBurntRegions == x_dim * y_dim)
        {
            allBurning = i;
        }
        // print checkpoint to console every 24 hours
        if (i % 24 == 0)
        {
            checkpoint(numBurntRegions, numBurningRegions, i / 24);
        }
        exportLog(std::to_string(i), numBurntRegions, numBurningRegions, newIgnites, (numBurntRegions - oldBurns));
    }

    report(allBurning, numBurntRegions);
    // start loop timeSteps times, or until fire is gone.
    // Set BurningRegions and BurntRegions to 0
    //  Loop through entire forest
    //  Update region
    //  if update returns true, increment burningRegions
    //  check region for burnt out, and increment burnt regions
    // cout timestep, burningRegions, and burntRegions
    // Call report.
}

// Assigns stations randomly
void forest::assignStation() // Strech goal, an overloaded version that assigns specific regions
{
    //declare variables before loop so that they can be used outside of the loop. 
    region *lucky = NULL;
    int x_lucky = 0;
    int y_lucky = 0;
    do
    {
        // Pick an lucky x cord
        x_lucky = rand() % x_dim;

        // lucky y cord
        y_lucky = rand() % y_dim;

        // find that region in the map
        lucky = regions[{x_lucky, y_lucky}];

        //loop until a region without a station is found. 
    } while (lucky->getStation());

    // Set station and construct
    lucky->setHasStation(true);
    // Size is currently hard coded as 3
    FireStation *station = new FireStation(3);
    lucky->setStation(station);
    //print the station location to the terminal. 
    cout << "Station at ( " << x_lucky << ", " << y_lucky << " )" << endl;
}

// output a report to the terminal
void forest::report(int fullFire, int burnt)
{
    cout << "The forest took " << timesteps << " hours to burn." << endl;
    if (fullFire != 0)
    {
        cout << endl << "The entire forest was on fire after " << fullFire << "hours." << endl;
    }
    else
    {

        cout << "About " << ((100 * burnt) / (x_dim * y_dim)) << "% of the forest was burnt." << endl << endl;
    }
}

// prints a map of the forest to the terminal or file, depending on argument
void forest::printMap(bool isCout, ofstream &writeTo)
{
    // printing to terminal
    if (isCout)
    {
        //print key
        cout << "Key= Untouched: ^, extingished: \", burning: X, burnt: _" << endl;
        cout << "Firestation:    *               ~           x         -" << endl;
        for (map<pair<int, int>, region *>::iterator it = regions.begin(); it != regions.end(); it++)
        {
            if (it->second->getFire())
            {
                if(it->second->getHasStation()){
                    cout << "x ";
                }
                else{
                    cout << "X ";
                }
            }
            else if (it->second->getBurningLeft() == 0)
            {
                if(it->second->getHasStation()){
                    cout << "- ";
                }
                else{
                    cout << "_ ";
                }
            }
            else if (it->second->getBurningLeft() == 100)
            {
                if(it->second->getHasStation()){
                    cout << "* ";
                }
                else{
                    cout << "^ ";
                }
            }
            else
            {
                if(it->second->getHasStation()){
                    cout << "~ ";
                }
                else{
                    cout << "\" ";
                }
            }
            if (it->first.second == y_dim - 1)
            {
                cout << endl;
            }
        }
    }
    // printing to file
    else
    {
        writeTo << "Key= Untouched: ^, extingished: \", burning: X, burnt: _" << endl;
        writeTo << "Firestation:    *               ~           x         -" << endl;
        for (map<pair<int, int>, region *>::iterator it = regions.begin(); it != regions.end(); it++)
        {
            if (it->second->getFire())
            {
                if(it->second->getHasStation()){
                    writeTo << "x ";
                }
                else{
                    writeTo << "X ";
                }
            }
            else if (it->second->getBurningLeft() == 0)
            {
                if(it->second->getHasStation()){
                    writeTo << "- ";
                }
                else{
                    writeTo << "_ ";
                }
            }
            else if (it->second->getBurningLeft() == 100)
            {
                if(it->second->getHasStation()){
                    writeTo << "* ";
                }
                else{
                    writeTo << "^ ";
                }
            }
            else
            {
                if(it->second->getHasStation()){
                    writeTo << "~ ";
                }
                else{
                    writeTo << "\" ";
                }
            }
            if (it->first.second == y_dim - 1)
            {
                writeTo << endl;
            }
        }
    }
}

//send a micro-report to terminal every 24 timesteps (day)
void forest::checkpoint(int numBurnt, int numBurning, int day)
{
    //quick update for every day in the simulation. 
    cout << "day: " << day << endl
         << "# of burnt regions: " << numBurnt << endl
         << "# of burning regions: " << numBurning << endl;
    // printMap();
}

void forest::exportLog(string timestep, int numBurnt, int numBurning, int newIgnites, int newBurns)
{
    //This function saves all the information to a file
    ofstream logOutput("./log/step" + timestep + ".txt");
    logOutput << "Timestep: " << timestep << "\n";
    logOutput << "Currently burning: " << numBurning << "\n";
    logOutput << "Total fully burnt: " << numBurnt << "\n";
    logOutput << "Ignited this timestep: " << newIgnites << "\n";
    logOutput << "Burnt down this timestep: " << newBurns << "\n\n";

    // print the forest map to the log
    printMap(false, logOutput);
}

// destructor
forest::~forest()
{
    for (map<pair<int, int>, region *>::iterator it = regions.begin(); it != regions.end(); it++)
    {
        delete it->second;
        it->second = NULL;
    }
}
