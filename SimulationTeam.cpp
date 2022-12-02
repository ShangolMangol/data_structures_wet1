//
// Created by idota on 02/12/2022.
//

#include "SimulationTeam.h"

SimulationTeam::SimulationTeam() : teamId(0), score(0)
{}

SimulationTeam::SimulationTeam(int teamId, int score) : teamId(teamId), score(score)
{}

SimulationTeam &SimulationTeam::operator=(const SimulationTeam &simulationTeam)
{
    this->teamId = simulationTeam.teamId;
    this->score = simulationTeam.score;
    return *this;
}
