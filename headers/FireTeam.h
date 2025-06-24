#ifndef FIRE_TEAM_H
#define FIRE_TEAM_H

// CHANGED TO STRUCT FOR CLEANER ACCESS
struct FireTeam 
{
    int activeWorkTime; // the amout of time they have been at work
    int efficiency; // The amount the team slows the toal burn.
    int activation; // The burning left that will activatethe team.
    FireTeam();
    FireTeam(int _efficiency,int _activation);
};


#endif