//
// Created by idota on 30/11/2022.
//

#ifndef WET1_COMPARETEAMPLAYERBYSCORE_H
#define WET1_COMPARETEAMPLAYERBYSCORE_H

#include <memory>
class Player;

class CompareTeamPlayerByScore
{
public:
    bool isLeftSmaller(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
    bool isEqual(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

    void insertToLeft(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);
    void insertToRight(std::shared_ptr<Player>& player, std::shared_ptr<Player>& currentPlayer);

    void handleDelete(std::shared_ptr<Player>& playerToDelete);
};


#endif //WET1_COMPARETEAMPLAYERBYSCORE_H
