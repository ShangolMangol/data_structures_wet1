//
// Created by idota on 28/11/2022.
//

#include "Team.h"

bool Team::isTeamValid() const
{
    return teamPlayersNum >= 11 && goalKeepersNum >= 1;
}

Team::Team(int teamId, int totalPoints) : teamID(teamId), totalPoints(totalPoints), totalCards(0),
                                    totalGoals(0), teamPlayersNum(0), gamesPlayedTeam(0),
                                    goalKeepersNum(0), playersByID(), playerByScore(), teamTopScorer(nullptr),
                                    previousValidTeam(), nextValidTeam()
{}


