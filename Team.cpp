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
                                    previousValidTeam(nullptr), nextValidTeam(nullptr)
{}

Team::Team(int teamId, int totalPoints, int totalCards, int totalGoals, int teamPlayersNum, int goalKeepersNum)
        : teamID(teamId), totalPoints(totalPoints), totalCards(totalCards), totalGoals(totalGoals),
          teamPlayersNum(teamPlayersNum), gamesPlayedTeam(0), goalKeepersNum(goalKeepersNum),
          playersByID(), playerByScore(), teamTopScorer(nullptr),
          previousValidTeam(nullptr), nextValidTeam(nullptr)
{}

void Team::updateTrees(std::shared_ptr<Player> *newPlayersById, std::shared_ptr<Player> *newPlayersByScore, int length)
{

    AVLTree<std::shared_ptr<Player>, ComparePlayerById> newIdTree(newPlayersById, length);
    AVLTree<std::shared_ptr<Player>, CompareTeamPlayerByScore> newScoreTree(newPlayersByScore, length);


    playersByID.deletePostorder(playersByID.root);
    playerByScore.deletePostorder(playerByScore.root);

    this->playersByID.root = newIdTree.root;
    this->playerByScore.root = newScoreTree.root;

    teamTopScorer = newPlayersByScore[length-1].get();

    newIdTree.root = nullptr;
    newScoreTree.root = nullptr;



}




