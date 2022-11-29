//
// Created by idota on 28/11/2022.
//

#include "CompareTeamById.h"
#include "Team.h"

bool CompareTeamById::isLeftSmaller(std::shared_ptr<Team> &team, int currentId)
{
    return team->teamID < currentId;
}

bool CompareTeamById::isLeftSmaller(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    return team->teamID < currentTeam->teamID;
}

bool CompareTeamById::isEqual(std::shared_ptr<Team> &team, int currentId)
{
    return team->teamID == currentId;
}

bool CompareTeamById::isEqual(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    return team->teamID == currentTeam->teamID;
}

void CompareTeamById::insertToLeft(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
//    if(team->isTeamValid() && currentTeam->isTeamValid() && team->)
//    {
//        currentTeam->nextValidTeam = team.get();
//        currentTeam->previousValidTeam = team->previousValidTeam;
//        team->previousValidTeam = currentTeam.get();
//        if(currentTeam->previousValidTeam != nullptr)
//            currentTeam->previousValidTeam->nextValidTeam = currentTeam.get();
//    }
}

void CompareTeamById::insertToRight(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
//    if(team->isTeamValid() && currentTeam->isTeamValid())
//    {
//        currentTeam->previousValidTeam = team.get();
//        currentTeam->nextValidTeam = team->nextValidTeam;
//        team->nextValidTeam = currentTeam.get();
//        if(currentTeam->nextValidTeam != nullptr)
//            currentTeam->nextValidTeam->previousValidTeam = currentTeam.get();
//    }
}

void CompareTeamById::handleDelete(std::shared_ptr<Team> &teamToDelete)
{
//    if(teamToDelete->isTeamValid())
//    {
//        if(teamToDelete->previousValidTeam != nullptr)
//            teamToDelete->previousValidTeam->nextValidTeam = teamToDelete->nextValidTeam;
//        if(teamToDelete->nextValidTeam != nullptr)
//            teamToDelete->nextValidTeam->previousValidTeam = teamToDelete->previousValidTeam;
//    }
}
