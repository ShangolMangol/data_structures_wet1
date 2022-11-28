//
// Created by idota on 28/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "AVLTree.h"
#include <memory>
#include "CompareTeamById.h"

class Player;

class Team
{
public:
    int teamID;
    int totalPoints;
    int totalCards;
    int totalGoals;
    int teamPlayersNum;
    int gamesPlayedTeam;
    int goalKeepersNum;
    AVLTree<std::shared_ptr<Player>,CompareTeamById> playersByID;
    //AVLTree<std::shared_ptr<Player>,CompareTeamByScore> playerByScore;
    Player *teamTopScorer;
    Team *previousPlayingTeam;
    Team *nextPlayingTeam;

};


#endif //WET1_TEAM_H
