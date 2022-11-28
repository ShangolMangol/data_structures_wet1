//
// Created by idota on 28/11/2022.
//

#ifndef WET1_COMPAREPLAYERBYSCORE_H
#define WET1_COMPAREPLAYERBYSCORE_H

#include <memory>
#include "Player.h"

class ComparePlayerByScore
{
    bool isLeftSmaller(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer, bool mode);
    bool isEqual(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

    void insertToLeft(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
};


#endif //WET1_COMPAREPLAYERBYSCORE_H
