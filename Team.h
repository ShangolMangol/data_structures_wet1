//
// Created by idota on 28/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "AVLTree.h"
#include <memory>
#include "ComparePlayerById.h"
#include "CompareTeamPlayerByScore.h"

class Player;

class Team
{
public:


    Team(int teamId, int totalPoints);

    bool isTeamValid() const;

    int teamID;
    int totalPoints;
    int totalCards;
    int totalGoals;
    int teamPlayersNum;
    int gamesPlayedTeam;
    int goalKeepersNum;
    AVLTree<std::shared_ptr<Player>, ComparePlayerById> playersByID;
    AVLTree<std::shared_ptr<Player>, CompareTeamPlayerByScore> playerByScore;
    Player *teamTopScorer;
    Team *previousValidTeam;
    Team *nextValidTeam;

};


#endif //WET1_TEAM_H
