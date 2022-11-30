//
// Created by idota on 30/11/2022.
//

#include "CompareTeamPlayerByScore.h"

#include "Player.h"

bool CompareTeamPlayerByScore::isLeftSmaller(std::shared_ptr<Player> &player,
                                         std::shared_ptr<Player> &currentPlayer)
{
    //Checking Goals
    if(player->numOfGoals < currentPlayer->numOfGoals)
    {
        return true;
    }
    else if(player->numOfGoals == currentPlayer->numOfGoals)
    {
        //Checking cards
        if(player-> numOfCards > currentPlayer->numOfCards)
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

bool CompareTeamPlayerByScore::isEqual(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    return player->playerID == currentPlayer->playerID;
}

void CompareTeamPlayerByScore::insertToLeft(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{}

void CompareTeamPlayerByScore::insertToRight(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{}

void CompareTeamPlayerByScore::handleDelete(std::shared_ptr<Player> &playerToDelete)
{}
