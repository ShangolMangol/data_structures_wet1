//
// Created by idota on 28/11/2022.
//

#include "ComparePlayerById.h"

bool ComparePlayerById::isLeftSmaller(std::shared_ptr<Player> &player, int currentId, bool mode)
{
    return player->playerID < currentId;
}

bool ComparePlayerById::isLeftSmaller(std::shared_ptr<Player> &player, std::shared_ptr<Player> &currentPlayer, bool mode)
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

