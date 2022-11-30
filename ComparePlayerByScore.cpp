//
// Created by idota on 28/11/2022.
//

#include "ComparePlayerByScore.h"
#include "Player.h"

bool ComparePlayerByScore::isLeftSmaller(std::shared_ptr<Player> &player,
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

bool ComparePlayerByScore::isEqual(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    return player->playerID == currentPlayer->playerID;
}

void ComparePlayerByScore::insertToLeft(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    if (currentPlayer->closestRight == nullptr && currentPlayer->closestLeft == nullptr)
    {
        currentPlayer->closestRight = player.get();
        currentPlayer->closestLeft = player->closestLeft;
        player->closestLeft = currentPlayer.get();
        if (currentPlayer->closestLeft != nullptr)
            currentPlayer->closestLeft->closestRight = currentPlayer.get();
    }
}

void ComparePlayerByScore::insertToRight(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    if(currentPlayer->closestRight == nullptr && currentPlayer->closestLeft == nullptr)
    {
        currentPlayer->closestLeft = player.get();
            currentPlayer->closestRight = player->closestRight;
            player->closestRight = currentPlayer.get();
            if(currentPlayer->closestRight != nullptr)
                currentPlayer->closestRight->closestLeft = currentPlayer.get();
    }
}

void ComparePlayerByScore::handleDelete(std::shared_ptr<Player> &playerToDelete)
{
    if(playerToDelete->closestLeft != nullptr)
        playerToDelete->closestLeft->closestRight = playerToDelete->closestRight;
    if(playerToDelete->closestRight != nullptr)
        playerToDelete->closestRight->closestLeft = playerToDelete->closestLeft;

    playerToDelete->closestLeft = nullptr;
    playerToDelete->closestRight = nullptr;
}


