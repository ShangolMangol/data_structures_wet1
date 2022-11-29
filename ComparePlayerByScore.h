//
// Created by idota on 28/11/2022.
//

#ifndef WET1_COMPAREPLAYERBYSCORE_H
#define WET1_COMPAREPLAYERBYSCORE_H

#include <memory>
#include "Player.h"

class ComparePlayerByScore
{
    bool isLeftSmaller(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
    bool isEqual(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

    void insertToLeft(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
    void insertToRight(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

    void handleDelete(std::shared_ptr<Player>& playerToDelete);

};


#endif //WET1_COMPAREPLAYERBYSCORE_H
