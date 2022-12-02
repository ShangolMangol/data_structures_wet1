//
// Created by idota on 02/12/2022.
//

#ifndef WET1_SIMULATIONTEAM_H
#define WET1_SIMULATIONTEAM_H


class SimulationTeam
{
public:
    SimulationTeam();
    SimulationTeam(int teamId, int score);
    SimulationTeam& operator=(const SimulationTeam& simulationTeam);

    int teamId;
    int score;


};


#endif //WET1_SIMULATIONTEAM_H
