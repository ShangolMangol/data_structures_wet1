

#ifndef WET1_COMPAREPLAYERBYID_H
#define WET1_COMPAREPLAYERBYID_H

#include <memory>
#include "Player.h"


class ComparePlayerById
{
public:
    bool isLeftSmaller(std::shared_ptr<Player>& player, int currentId);
    bool isLeftSmaller(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
    bool isEqual(std::shared_ptr<Player>& player, int currentId);
    bool isEqual(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

    void insertToLeft(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
    void insertToRight(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

    void handleDelete(std::shared_ptr<Player>& playerToDelete);
};


#endif //WET1_COMPAREPLAYERBYID_H