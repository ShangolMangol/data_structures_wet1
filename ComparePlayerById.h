

#ifndef WET1_COMPAREPLAYERBYID_H
#define WET1_COMPAREPLAYERBYID_H

#include <memory>
#include "Player.h"


class ComparePlayerById
{
public:
    bool isLeftSmaller(std::shared_ptr<Player>& player, int currentId, bool mode);
    bool isLeftSmaller(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer, bool mode);
    bool isEqual(std::shared_ptr<Player>& player, int currentId);
    bool isEqual(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

};


#endif //WET1_COMPAREPLAYERBYID_H
