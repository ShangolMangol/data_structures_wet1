#include "worldcup23a1.h"

using std::shared_ptr;

int absoluteValue(int value)
{
    if(value >= 0)
        return value;
    return -1 * value;
}

world_cup_t::world_cup_t() : teamsById(), validTeams(), playersById(),
                        playersByScore(), playersNum(0), topScorer(nullptr)
{}

world_cup_t::~world_cup_t()
{
	// NOTHING TO DO HERE
}


StatusType world_cup_t::add_team(int teamId, int points)
{
    if(teamId <= 0 || points < 0)
        return StatusType::INVALID_INPUT;
    AVLNode<shared_ptr<Team>>* temp = teamsById.findNode(teamsById.root,teamId);
    if(temp != nullptr)
        return StatusType::FAILURE;
	try{
        shared_ptr<Team> team = shared_ptr<Team>(new Team(teamId, points));
        teamsById.root = teamsById.insert(teamsById.root,team);
    } catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Team>>* teamNode = teamsById.findNode(teamsById.root, teamId);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    if(teamNode->data->teamPlayersNum != 0)
        return StatusType::FAILURE;

    if(teamNode->data->isTeamValid())
       validTeams.root = validTeams.deleteNode(validTeams.root, teamId);
    teamsById.root = teamsById.deleteNode(teamsById.root, teamId);


    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper)
{
	if(playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0)
        return StatusType::INVALID_INPUT;
    else if(gamesPlayed == 0 && (goals > 0 || cards > 0))
        return StatusType::INVALID_INPUT;


    AVLNode<shared_ptr<Team>>* teamTemp = teamsById.findNode(teamsById.root,teamId);
    if(teamTemp == nullptr)
        return  StatusType::FAILURE;

    AVLNode<shared_ptr<Player>>* playerTemp = playersById.findNode(playersById.root,playerId);
    if(playerTemp != nullptr)
        return  StatusType::FAILURE;



    try
    {
        shared_ptr<Player> newPlayer =
                shared_ptr<Player>(new Player(playerId, teamTemp->data.get(), gamesPlayed,
                                                                     goals,
                                                                     teamTemp->data->gamesPlayedTeam,
                                                                     cards, goalKeeper));
        playersById.root = playersById.insert(playersById.root, newPlayer);
        playersByScore.root = playersByScore.insert(playersByScore.root, newPlayer);
        newPlayer->team->playersByID.root = newPlayer->team->playersByID.insert(
                        newPlayer->team->playersByID.root, newPlayer);
        newPlayer->team->playerByScore.root = newPlayer->team->playerByScore.insert(
                newPlayer->team->playerByScore.root, newPlayer);


        if(!newPlayer->isLowerScorer(topScorer))
        {
            topScorer = newPlayer.get();
            newPlayer->team->teamTopScorer = newPlayer.get();
        }
        else if(!newPlayer->isLowerScorer(newPlayer->team->teamTopScorer))
        {
            newPlayer->team->teamTopScorer = newPlayer.get();
        }

        bool teamValidBefore = newPlayer->team->isTeamValid();

        newPlayer->team->totalGoals += newPlayer->numOfGoals;
        newPlayer->team->totalCards += newPlayer->numOfCards;
        newPlayer->team->teamPlayersNum = newPlayer->team-> teamPlayersNum + 1;
        if(goalKeeper)
            newPlayer->team->goalKeepersNum += 1;
        newPlayer->gamesOnJoin = newPlayer->team->gamesPlayedTeam;

        playersNum++;

        if(!teamValidBefore && newPlayer->team->isTeamValid())
            validTeams.root = validTeams.insert(validTeams.root, teamTemp->data);


    } catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_player(int playerId)
{
	if(playerId <= 0)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Player>>* playerTemp = playersById.findNode(playersById.root,playerId);
    if(playerTemp == nullptr)
        return  StatusType::FAILURE;

    try
    {
        Team* team = playerTemp->data->team;
        shared_ptr<Player> playerToDelete = playerTemp->data;
        bool wasTeamValid = team->isTeamValid();

        team->totalGoals -= playerToDelete->numOfGoals;
        team->totalCards -= playerToDelete->numOfCards;
        team->teamPlayersNum -= 1;
        if(team->teamPlayersNum < 0)
            team->teamPlayersNum = 0;
        if(playerToDelete->isGoalKeeper)
            team->goalKeepersNum -= 1;
        if(team->goalKeepersNum < 0)
            team->goalKeepersNum = 0;

        this->playersNum--;
        if(this->playersNum < 0)
            this->playersNum = 0;

        playersById.root = playersById.deleteNode(playersById.root, playerToDelete->playerID);
        playersByScore.root = playersByScore.deleteNode(playersByScore.root, playerToDelete);
        team->playerByScore.root = team->playerByScore.deleteNode(team->playerByScore.root,
                                                                  playerToDelete);
        team->playersByID.root = team->playersByID.deleteNode(team->playersByID.root,
                                                              playerToDelete->playerID);



        if(wasTeamValid && !team->isTeamValid())
            validTeams.root = validTeams.deleteNode(validTeams.root, team->teamID);

        AVLNode<shared_ptr<Player>>* playerTempTop = playersByScore.findRightestSon(playersByScore.root);
        if(playerTempTop != nullptr)
            topScorer = playerTempTop->data.get();
        else
            topScorer = nullptr;

        playerTempTop = team->playerByScore.findRightestSon(team->playerByScore.root);
        if(playerTempTop != nullptr)
            team->teamTopScorer = playerTempTop->data.get();
        else
            team->teamTopScorer = nullptr;


    }
    catch (std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                        int scoredGoals, int cardsReceived)
{
	if(playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Player>>* playerTemp = playersById.findNode(playersById.root,playerId);
    if(playerTemp == nullptr)
        return  StatusType::FAILURE;

    try {
        Team *team = playerTemp->data->team;
        shared_ptr<Player> playerToUpdate = playerTemp->data;

        playersByScore.root = playersByScore.deleteNode(playersByScore.root, playerToUpdate);
        team->playerByScore.root = team->playerByScore.deleteNode(team->playerByScore.root,
                                                                  playerToUpdate);

        playerToUpdate->gamesPlayedPlayer += gamesPlayed;
        playerToUpdate->numOfGoals += scoredGoals;
        playerToUpdate->numOfCards += cardsReceived;

        team->totalGoals += scoredGoals;
        team->totalCards += cardsReceived;

        playersByScore.root = playersByScore.insert(playersByScore.root, playerToUpdate);
        team->playerByScore.root = team->playerByScore.insert(team->playerByScore.root, playerToUpdate);

        AVLNode<shared_ptr<Player>>* playerTempTop = playersByScore.findRightestSon(playersByScore.root);
        if(playerTempTop != nullptr)
            topScorer = playerTempTop->data.get();
        else
            topScorer = nullptr;

        playerTempTop = team->playerByScore.findRightestSon(team->playerByScore.root);
        if(playerTempTop != nullptr)
            team->teamTopScorer = playerTempTop->data.get();
        else
            team->teamTopScorer = nullptr;


    } catch(std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Team>>* teamTemp1 = validTeams.findNode(validTeams.root,teamId1);
    if(teamTemp1 == nullptr)
        return  StatusType::FAILURE;

    AVLNode<shared_ptr<Team>>* teamTemp2 = validTeams.findNode(validTeams.root,teamId2);
    if(teamTemp2 == nullptr)
        return  StatusType::FAILURE;

    int score1 = teamTemp1->data->totalPoints + teamTemp1->data->totalGoals - teamTemp1->data->totalCards;
    int score2 = teamTemp2->data->totalPoints + teamTemp2->data->totalGoals - teamTemp2->data->totalCards;

    if(score1 > score2)
    {
        teamTemp1->data->totalPoints += 3;
    }
    else if(score1 < score2)
    {
        teamTemp2->data->totalPoints += 3;
    }
    else
    {
        teamTemp1->data->totalPoints += 1;
        teamTemp2->data->totalPoints += 1;
    }

    teamTemp1->data->gamesPlayedTeam += 1;
    teamTemp2->data->gamesPlayedTeam += 1;

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
	if(playerId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    AVLNode<shared_ptr<Player>>* playerTemp = playersById.findNode(playersById.root,playerId);
    if(playerTemp == nullptr)
        return  output_t<int>(StatusType::FAILURE);

    int gamesPlayed = playerTemp->data->team->gamesPlayedTeam +
            playerTemp->data->gamesPlayedPlayer - playerTemp->data->gamesOnJoin;

    return output_t<int>(gamesPlayed);
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if(teamId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    AVLNode<shared_ptr<Team>>* teamNode = teamsById.findNode(teamsById.root, teamId);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    return output_t<int>(teamNode->data->totalPoints);
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{

    if (teamId1 <= 0 || teamId2 <= 0 || newTeamId <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;

    AVLNode<shared_ptr<Team>> *teamTemp1 = teamsById.findNode(teamsById.root, teamId1);
    if (teamTemp1 == nullptr)
        return StatusType::FAILURE;

    AVLNode<shared_ptr<Team>> *teamTemp2 = teamsById.findNode(teamsById.root, teamId2);
    if (teamTemp2 == nullptr)
        return StatusType::FAILURE;


    AVLNode<shared_ptr<Team>> *newTeamTemp = teamsById.findNode(teamsById.root, newTeamId);
    if (newTeamTemp != nullptr && teamId1 != newTeamId && teamId2 != newTeamId)
        return StatusType::FAILURE;


    shared_ptr<Player> *team1PlayersById = nullptr;
    shared_ptr<Player> *team1PlayersByScore = nullptr;
    shared_ptr<Player> *team2PlayersById = nullptr;
    shared_ptr<Player> *team2PlayersByScore = nullptr;
    shared_ptr<Player> *newTeamPlayersById = nullptr;
    shared_ptr<Player> *newTeamPlayersByScore = nullptr;
    try {
        int team1Size = teamTemp1->data->teamPlayersNum;
        int team2Size = teamTemp2->data->teamPlayersNum;

        team1PlayersById = teamTemp1->data->playersByID.getInOrder(team1Size);
        team1PlayersByScore = teamTemp1->data->playerByScore.getInOrder(team1Size);
        team2PlayersById = teamTemp2->data->playersByID.getInOrder(team2Size);
        team2PlayersByScore = teamTemp2->data->playerByScore.getInOrder(team2Size);

        newTeamPlayersById = new shared_ptr<Player>[team1Size + team2Size];
        newTeamPlayersByScore = new shared_ptr<Player>[team1Size + team2Size];

        //merging the arrays
        int index1 = 0, index2 = 0, newIndex = 0;
        while (index1 < team1Size && index2 < team2Size) {
            if (team1PlayersById[index1]->playerID < team2PlayersById[index2]->playerID) {
                newTeamPlayersById[newIndex] = team1PlayersById[index1];
                index1++;
            } else {
                newTeamPlayersById[newIndex] = team2PlayersById[index2];
                index2++;
            }
            newIndex++;
        }
        while (index1 < team1Size)
        {
            newTeamPlayersById[newIndex] = team1PlayersById[index1];
            index1++;newIndex++;
        }
        while (index2 < team2Size)
        {
            newTeamPlayersById[newIndex] = team2PlayersById[index2];
            index2++;newIndex++;
        }

        index1 = 0;
        index2 = 0;
        newIndex = 0;
        while (index1 < team1Size && index2 < team2Size) {
            if (team1PlayersByScore[index1]->isLowerScorer(team2PlayersByScore[index2].get())) {
                newTeamPlayersByScore[newIndex] = team1PlayersByScore[index1];
                index1++;
            } else {
                newTeamPlayersByScore[newIndex] = team2PlayersByScore[index2];
                index2++;
            }
            newIndex++;
        }
        while (index1 < team1Size)
        {
            newTeamPlayersByScore[newIndex] = team1PlayersByScore[index1];
            index1++;newIndex++;
        }
        while (index2 < team2Size)
        {
            newTeamPlayersByScore[newIndex] = team2PlayersByScore[index2];
            index2++;newIndex++;
        }

        //creating new team
        shared_ptr<Team> newTeam = shared_ptr<Team>(new Team(newTeamId,
                                                             teamTemp1->data->totalPoints +
                                                             teamTemp2->data->totalPoints,
                                                             teamTemp1->data->totalCards + teamTemp2->data->totalCards,
                                                             teamTemp1->data->totalGoals + teamTemp2->data->totalGoals,
                                                             teamTemp1->data->teamPlayersNum +
                                                             teamTemp2->data->teamPlayersNum,
                                                             teamTemp1->data->goalKeepersNum +
                                                             teamTemp2->data->goalKeepersNum));

        if (newTeamId == teamId1)
            newTeam->gamesPlayedTeam = teamTemp1->data->gamesPlayedTeam;
        if (newTeamId == teamId2)
            newTeam->gamesPlayedTeam = teamTemp2->data->gamesPlayedTeam;

        //updating trees
        newTeam->updateTrees(newTeamPlayersById, newTeamPlayersByScore, team1Size + team2Size);

        //updating players
        for (int i = 0; i < team1Size + team2Size; ++i) {
            Player *player = newTeamPlayersById[i].get();
            if (player->team->teamID != newTeamId) {
                player->gamesPlayedPlayer =
                        player->gamesPlayedPlayer + player->team->gamesPlayedTeam - player->gamesOnJoin;
                player->gamesOnJoin = 0;
            }
            player->team = newTeam.get();
        }


        if (teamTemp1->data->isTeamValid())
            validTeams.root = validTeams.deleteNode(validTeams.root, teamId1);
        teamsById.root = teamsById.deleteNode(teamsById.root, teamId1);


        AVLNode<shared_ptr<Team>> *teamTemp2 = teamsById.findNode(teamsById.root, teamId2);
        if (teamTemp2 == nullptr)
            return StatusType::FAILURE;

        if (teamTemp2->data->isTeamValid())
            validTeams.root = validTeams.deleteNode(validTeams.root, teamId2);
        teamsById.root = teamsById.deleteNode(teamsById.root, teamId2);


        teamsById.root = teamsById.insert(teamsById.root, newTeam);
        if(newTeam->isTeamValid())
            validTeams.root = validTeams.insert(validTeams.root, newTeam);


    }

    catch (std::bad_alloc& e)
    {
        if(team1PlayersById != nullptr)
            delete[] team1PlayersById;
        if(team1PlayersByScore != nullptr)
            delete[] team1PlayersByScore;
        if(team2PlayersById != nullptr)
            delete[] team2PlayersById;
        if(team2PlayersByScore != nullptr)
            delete[] team2PlayersByScore;
        if(newTeamPlayersById != nullptr)
            delete[] newTeamPlayersById;
        if(newTeamPlayersByScore != nullptr)
            delete[] newTeamPlayersByScore;
        return StatusType::ALLOCATION_ERROR;
    }
    delete[] team1PlayersById;
    delete[] team1PlayersByScore;
    delete[] team2PlayersById;
    delete[] team2PlayersByScore;
    delete[] newTeamPlayersById;
    delete[] newTeamPlayersByScore;

    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId == 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    if(teamId < 0)
    {
        if(topScorer != nullptr)
            return output_t<int>(topScorer->playerID);
        return output_t<int>(StatusType::FAILURE);
    }

    AVLNode<shared_ptr<Team>>* teamNode = teamsById.findNode(teamsById.root, teamId);
    if(teamNode == nullptr)
        return output_t<int>(StatusType::FAILURE);

    if(teamNode->data->teamTopScorer == nullptr)
        return output_t<int>(StatusType::FAILURE);
    return output_t<int>(teamNode->data->teamTopScorer->playerID);
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId == 0)
        return output_t<int>(StatusType::INVALID_INPUT);


    if(teamId < 0)
        return output_t<int>(playersNum);


    AVLNode<shared_ptr<Team>> *teamTemp = teamsById.findNode(teamsById.root, teamId);
    if (teamTemp == nullptr)
        return output_t<int>(StatusType::FAILURE);

    return output_t<int>(teamTemp->data->teamPlayersNum);
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
	if(teamId == 0 || output == nullptr || output == NULL)
        return StatusType::INVALID_INPUT;

    if(playersNum == 0)
        return StatusType::FAILURE;

    shared_ptr<Player>* playersByScoreArray = nullptr;
    int length = 0;
    try
    {
        int index = 0;
        if(teamId < 0)
        {
            //playersByScoreArray = playersByScore.getInOrder(playersNum);
            //length = playersNum;
            Player* player = nullptr;
            AVLNode<shared_ptr<Player>>* startPlayerTemp = playersByScore.findLeftestSon(playersByScore.root);
            if(startPlayerTemp != nullptr)
                player = startPlayerTemp->data.get();
            else
                player = nullptr;

            while (player != nullptr)
            {
                output[index] = player->playerID;
                player = player->closestRight;
                index++;
            }
            return StatusType::SUCCESS;
        }
        else
        {
            AVLNode<shared_ptr<Team>> *teamTemp = teamsById.findNode(teamsById.root, teamId);
            if (teamTemp == nullptr)
                return StatusType::FAILURE;

            playersByScoreArray = teamTemp->data->playerByScore.getInOrder(teamTemp->data->teamPlayersNum);
            length = teamTemp->data->teamPlayersNum;

            for (int i = 0; i < length; ++i)
            {
                output[i] = playersByScoreArray[i]->playerID;
            }
        }


    }
    catch(std::bad_alloc & e)
    {
        return StatusType::ALLOCATION_ERROR;
    }


    delete[] playersByScoreArray;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    if(playerId <= 0 || teamId <= 0)
    {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    AVLNode<shared_ptr<Team>>* teamNode = teamsById.findNode(teamsById.root, teamId);
    if(teamNode == nullptr)
        return StatusType::FAILURE;

    AVLNode<shared_ptr<Player>>* playerTemp = teamNode->data->playersByID.findNode(
                            teamNode->data->playersByID.root,playerId);

    if(playerTemp == nullptr || (playerTemp->data->closestLeft == nullptr && playerTemp->data->closestRight == nullptr))
        return  output_t<int>(StatusType::FAILURE);

    Player* player = playerTemp->data.get();
    Player* closestLeft = player->closestLeft;
    Player* closestRight = player->closestRight;
    if(closestLeft == nullptr)
        return output_t<int>(closestRight->playerID);
    if(closestRight == nullptr)
        return output_t<int>(closestLeft->playerID);
    if(player->numOfGoals - closestLeft->numOfGoals < closestRight->numOfGoals - player->numOfGoals)
        return output_t<int>(closestLeft->playerID);
    if(player->numOfGoals - closestLeft->numOfGoals > closestRight->numOfGoals - player->numOfGoals)
        return output_t<int>(closestRight->playerID);
    if(absoluteValue(player->numOfCards - closestLeft->numOfCards) < absoluteValue(closestRight->numOfCards - player->numOfCards))
        return output_t<int>(closestLeft->playerID);
    if(absoluteValue(player->numOfCards - closestLeft->numOfCards) > absoluteValue(closestRight->numOfCards - player->numOfCards))
        return output_t<int>(closestRight->playerID);
    if(absoluteValue(player->playerID - closestLeft->playerID) < absoluteValue(closestRight->playerID - player->playerID))
        return output_t<int>(closestLeft->playerID);
    if(absoluteValue(player->playerID - closestLeft->playerID) > absoluteValue(closestRight->playerID - player->playerID))
        return output_t<int>(closestRight->playerID);
    if(closestLeft->playerID > closestRight->playerID)
        return output_t<int>(closestLeft->playerID);
    return output_t<int>(closestRight->playerID);
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId < 0 || maxTeamId < 0 || minTeamId > maxTeamId)
        return output_t<int>(StatusType::INVALID_INPUT);
    try
    {
        AVLNode<shared_ptr<Team>>* teamInRange = validTeams.findNodeInRange(validTeams.root,
                                                                            minTeamId, maxTeamId);
        if(teamInRange == nullptr)
            return output_t<int>(StatusType::FAILURE);
        Team* currentTeam = teamInRange->data.get();
        while (currentTeam->nextValidTeam != nullptr && currentTeam->nextValidTeam->teamID <= maxTeamId)
        {
            currentTeam = currentTeam->nextValidTeam;
        }
        int length = 1;
        while (currentTeam->previousValidTeam != nullptr && currentTeam->previousValidTeam->teamID >= minTeamId)
        {
            currentTeam = currentTeam->previousValidTeam;
            length++;
        }
        if(length == 1)
            return output_t<int>(currentTeam->teamID);
        SimulationTeam* teamsForKnockout = new SimulationTeam[length];
        for (int i = 0; i < length; ++i)
        {
            teamsForKnockout[i] = SimulationTeam(currentTeam->teamID,
                                                 currentTeam->totalPoints + currentTeam->totalGoals - currentTeam->totalCards);
            currentTeam = currentTeam->nextValidTeam;
        }
        SimulationTeam* newTeamsForKnockout;
        int newLength = 0;
        while(length > 1)
        {
            if(length % 2 == 1)
                newLength = length/2 + 1;
            else
                newLength = length/2;

            newTeamsForKnockout = new SimulationTeam[newLength];

            for (int i = 0; i < newLength; ++i)
            {
                if(2*i + 1 >= length)
                {
                    newTeamsForKnockout[i] = teamsForKnockout[2 * i];
                }
                else {
                    if (teamsForKnockout[2 * i].score > teamsForKnockout[2 * i + 1].score)
                    {
                        newTeamsForKnockout[i] = teamsForKnockout[2 * i];

                    }
                    else if(teamsForKnockout[2 * i].score < teamsForKnockout[2 * i + 1].score)
                    {
                        newTeamsForKnockout[i] = teamsForKnockout[2 * i +1];
                    }
                    else
                    {
                        if(teamsForKnockout[2*i].teamId > teamsForKnockout[2*i +1].teamId)
                            newTeamsForKnockout[i] = teamsForKnockout[2 * i];
                        else
                            newTeamsForKnockout[i] = teamsForKnockout[2 * i +1];

                    }
                    newTeamsForKnockout[i].score = teamsForKnockout[2*i].score + teamsForKnockout[2*i +1].score + 3;

                }

            }
            delete[] teamsForKnockout;
            teamsForKnockout = newTeamsForKnockout;
            length = newLength;
        }
        int winningTeamId = teamsForKnockout[0].teamId;
        delete[] teamsForKnockout;
        return output_t<int>(winningTeamId);
    }
    catch(std::bad_alloc & e)
    {
        return  output_t<int>(StatusType::ALLOCATION_ERROR);
    }

}

