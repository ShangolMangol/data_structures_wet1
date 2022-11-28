//
// Created by idota on 28/11/2022.
//

#include "ComparePlayerByScore.h"


bool ComparePlayerByScore::isLeftSmaller(std::shared_ptr<Player> &player,
                                         std::shared_ptr<Player> &currentPlayer, bool mode)
{
    //Checking Goals
    if(player->numOfGoals < currentPlayer->numOfGoals)
    {
        return true;
    }
    else if(player->numOfGoals == currentPlayer->numOfGoals)
    {
        //Checking cards
        if(player-> numOfCards < currentPlayer->numOfCards)
        {
            return true;
        }
        else if(player->numOfCards == currentPlayer->numOfCards)
        {
            //Checking ID
            if(player->playerID < currentPlayer->playerID)
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

bool ComparePlayerByScore::isEqual(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    return player->playerID == currentPlayer->playerID;
}

void ComparePlayerByScore::insertToLeft(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
//    if(c)
}
