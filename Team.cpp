//
// Created by idota on 28/11/2022.
//

#include "Team.h"

bool Team::isTeamValid() const
{
    return teamPlayersNum >= 11 && goalKeepersNum >= 1;
}
