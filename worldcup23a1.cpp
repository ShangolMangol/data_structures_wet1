#include "worldcup23a1.h"

using std::shared_ptr;


world_cup_t::world_cup_t() : teamsById(), validTeams(), playersById(),
                        playersByScore(), playersNum(0), topScorer(nullptr)
{}

world_cup_t::~world_cup_t()
{
	// NOTHING TO DO HERE PROBABLY
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

    teamsById.root = teamsById.deleteNode(teamsById.root, teamId);
    if(teamNode->data->isTeamValid())
       validTeams.root = validTeams.deleteNode(validTeams.root, teamId);

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
        newPlayer->team->teamPlayersNum += 1;
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
        if(playerToDelete->isGoalKeeper)
            team->goalKeepersNum -= 1;
        if(team->goalKeepersNum < 0)
            team->goalKeepersNum = 0;

        playersById.root = playersById.deleteNode(playersById.root, playerToDelete->playerID);
        playersByScore.root = playersByScore.deleteNode(playersByScore.root, playerToDelete);
        team->playerByScore.root = team->playerByScore.deleteNode(team->playerByScore.root,
                                                                  playerToDelete);
        team->playersByID.root = team->playersByID.deleteNode(team->playersByID.root,
                                                              playerToDelete->playerID);

        if(wasTeamValid && !team->isTeamValid())
            validTeams.root = validTeams.deleteNode(validTeams.root, team->teamID);

        topScorer = playersByScore.findRightestSon(playersByScore.root)->data.get();
        team->teamTopScorer = team->playerByScore.findRightestSon(team->playerByScore.root)->data.get();

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

        topScorer = playersByScore.findRightestSon(playersByScore.root)->data.get();
        team->teamTopScorer = team->playerByScore.findRightestSon(team->playerByScore.root)->data.get();

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
        while (index1 < team1Size || index2 < team2Size) {
            if (team1PlayersById[index1]->playerID < team2PlayersById[index2]->playerID) {
                newTeamPlayersById[newIndex] = team1PlayersById[index1];
                index1++;
            } else {
                newTeamPlayersById[newIndex] = team2PlayersById[index2];
                index2++;
            }
            newIndex++;
        }

        index1 = 0;
        index2 = 0;
        newIndex = 0;
        while (index1 < team1Size || index2 < team2Size) {
            if (team1PlayersByScore[index1]->isLowerScorer(team2PlayersByScore[index2].get())) {
                newTeamPlayersByScore[newIndex] = team1PlayersByScore[index1];
                index1++;
            } else {
                newTeamPlayersByScore[newIndex] = team2PlayersByScore[index2];
                index2++;
            }
            newIndex++;
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


        teamsById.root = teamsById.deleteNode(teamsById.root, teamId1);
        if (teamTemp1->data->isTeamValid())
            validTeams.root = validTeams.deleteNode(validTeams.root, teamId1);

        teamsById.root = teamsById.deleteNode(teamsById.root, teamId2);
        if (teamTemp2->data->isTeamValid())
            validTeams.root = validTeams.deleteNode(validTeams.root, teamId2);

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
        return StatusTy
        pe::ALLOCATION_ERROR;
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
	// TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{
    // TODO: Your code goes here
    if()
    AVLNode<shared_ptr<Player>>* playerTemp = playersById.findNode(playersById.root,playerId);
    if(playerTemp == nullptr)
        return  StatusType::FAILURE;
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

