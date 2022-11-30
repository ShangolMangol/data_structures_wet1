//
// Created by idota on 30/11/2022.
//

#include "CompareValidTeamById.h"
#include "Team.h"

bool CompareValidTeamById::isLeftSmaller(std::shared_ptr<Team> &team, int currentId)
{
    return team->teamID < currentId;
}

bool CompareValidTeamById::isLeftSmaller(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    return team->teamID < currentTeam->teamID;
}

bool CompareValidTeamById::isEqual(std::shared_ptr<Team> &team, int currentId)
{
    return team->teamID == currentId;
}

bool CompareValidTeamById::isEqual(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    return team->teamID == currentTeam->teamID;
}

void CompareValidTeamById::insertToLeft(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    if (currentTeam->nextValidTeam == nullptr && currentTeam->previousValidTeam == nullptr)
    {
        currentTeam->nextValidTeam = team.get();
        currentTeam->previousValidTeam = team->previousValidTeam;
        team->previousValidTeam = currentTeam.get();
        if (currentTeam->previousValidTeam != nullptr)
            currentTeam->previousValidTeam->nextValidTeam = currentTeam.get();
    }
}

void CompareValidTeamById::insertToRight(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{
    if (currentTeam->nextValidTeam == nullptr && currentTeam->previousValidTeam == nullptr)
    {
        currentTeam->previousValidTeam = team.get();
        currentTeam->nextValidTeam = team->nextValidTeam;
        team->nextValidTeam = currentTeam.get();
        if (currentTeam->nextValidTeam != nullptr)
            currentTeam->nextValidTeam->previousValidTeam = currentTeam.get();
    }
}

void CompareValidTeamById::handleDelete(std::shared_ptr<Team> &teamToDelete)
{
    if(teamToDelete->previousValidTeam != nullptr)
        teamToDelete->previousValidTeam->nextValidTeam = teamToDelete->nextValidTeam;
    if(teamToDelete->nextValidTeam != nullptr)
        teamToDelete->nextValidTeam->previousValidTeam = teamToDelete->previousValidTeam;

    teamToDelete->nextValidTeam = nullptr;
    teamToDelete->previousValidTeam = nullptr;
}
