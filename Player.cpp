//
// Created by idota on 28/11/2022.
//

#include "Team.h"
#include "Player.h"

Player::Player(int playerId, Player *closestLeft, Player *closestRight,
               Team *team, int gamesPlayedPlayer,
               int numOfGoals, int gamesOnJoin,
               int numOfCards, bool isGoalKeeper) :

               playerID(playerId), closestLeft(closestLeft), closestRight(closestRight),
               team(team), gamesPlayedPlayer(gamesPlayedPlayer), numOfGoals(numOfGoals),
               gamesOnJoin(gamesOnJoin), numOfCards(numOfCards), isGoalKeeper(isGoalKeeper)
{}

Player::Player(int playerId, Team *team, int gamesPlayedPlayer, int numOfGoals, int gamesOnJoin, int numOfCards,
               bool isGoalKeeper) : playerID(playerId), closestLeft(nullptr), closestRight(nullptr),
                                    team(team), gamesPlayedPlayer(gamesPlayedPlayer), numOfGoals(numOfGoals),
                                    gamesOnJoin(gamesOnJoin), numOfCards(numOfCards), isGoalKeeper(isGoalKeeper)
{}

bool Player::isLowerScorer(Player *currentTopScorer) const
{
    if(currentTopScorer == nullptr)
        return false;
    //Checking Goals
    if(this->numOfGoals < currentTopScorer->numOfGoals)
    {
        return true;
    }
    else if(this->numOfGoals == currentTopScorer->numOfGoals)
    {
        //Checking cards
        if(this-> numOfCards > currentTopScorer->numOfCards)
        {
            return true;
        }
        else if(this->numOfCards == currentTopScorer->numOfCards)
        {
            //Checking ID
            if(this->playerID < currentTopScorer->playerID)
            {
                return true;
            }
            return false;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
