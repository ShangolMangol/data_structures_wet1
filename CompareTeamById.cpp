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
}

void CompareTeamById::insertToRight(std::shared_ptr<Team> &team, std::shared_ptr<Team> &currentTeam)
{

}

void CompareTeamById::handleDelete(std::shared_ptr<Team> &teamToDelete)
{

}
