//
// Created by idota on 28/11/2022.
//

#include "Player.h"

Player::Player(int playerId, Player *closestLeft, Player *closestRight,
               Team *team, int gamesPlayedPlayer,
               int numOfGoals, int gamesOnJoin,
               int numOfCards, bool isGoalKeeper) :

               playerID(playerId), closestLeft(closestLeft), closestRight(closestRight),
               team(team), gamesPlayedPlayer(gamesPlayedPlayer), numOfGoals(numOfGoals),
               gamesOnJoin(gamesOnJoin), numOfCards(numOfCards), isGoalKeeper(isGoalKeeper)
{}
