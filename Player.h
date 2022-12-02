//
// Created by idota on 28/11/2022.
//

#ifndef WET1_PLAYER_H
#define WET1_PLAYER_H



//#include "Team.h"
class Team;

class Player
{
public:

    Player(int playerId, Player *closestLeft, Player *closestRight, Team *team, int gamesPlayedPlayer, int numOfGoals,
           int gamesOnJoin, int numOfCards, bool isGoalKeeper);

    Player(int playerId, Team *team, int gamesPlayedPlayer, int numOfGoals, int gamesOnJoin, int numOfCards,
           bool isGoalKeeper);

    bool isLowerScorer(Player* currentTopScorer) const;

    int playerID;
    Player* closestLeft;
    Player* closestRight;
    Team* team;
    int gamesPlayedPlayer;
    int numOfGoals;
    int gamesOnJoin;
    int numOfCards;
    bool isGoalKeeper;
};


#endif //WET1_PLAYER_H
