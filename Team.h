//
// Created by idota on 28/11/2022.
//

#ifndef WET1_TEAM_H
#define WET1_TEAM_H
#include "AVLTree.h"
#include "ComparePlayerById.h"
#include "CompareTeamPlayerByScore.h"
#include <memory>
#include "Player.h"

//class Player;
//class ComparePlayerById;
//class CompareTeamPlayerByScore;

class Team
{
public:


    Team(int teamId, int totalPoints);

    Team(int teamId, int totalPoints, int totalCards, int totalGoals, int teamPlayersNum, int goalKeepersNum);

    bool isTeamValid() const;

    void updateTrees(std::shared_ptr<Player>* newPlayersById, std::shared_ptr<Player>* newPlayersByScore, int length);

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
