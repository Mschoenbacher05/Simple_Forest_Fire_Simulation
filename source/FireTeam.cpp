#include"FireTeam.h"

FireTeam::FireTeam()
{
    activeWorkTime = 0;
    efficiency = 0.0;
    activation = 0;
}

FireTeam::FireTeam(int _efficiency,int _activation)
{
    activeWorkTime = 0;
    efficiency = _efficiency;
    activation = _activation;
}




