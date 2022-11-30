//
// Created by idota on 28/11/2022.
//

#include "ComparePlayerById.h"
#include "Player.h"

bool ComparePlayerById::isLeftSmaller(std::shared_ptr<Player> &player, int currentId)
{
    return player->playerID < currentId;
}

bool ComparePlayerById::isLeftSmaller(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    return player->playerID < currentPlayer->playerID;
}

bool ComparePlayerById::isEqual(std::shared_ptr<Player> &player, int currentId)
{
    return player->playerID == currentId;
}

bool ComparePlayerById::isEqual(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{
    return player->playerID == currentPlayer->playerID;
}

void ComparePlayerById::insertToLeft(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{

}

void ComparePlayerById::insertToRight(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer)
{

}

void ComparePlayerById::handleDelete(std::shared_ptr<Player> &playerToDelete)
{

}

