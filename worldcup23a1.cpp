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
	// TODO: Your code goes here
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
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
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
	return 1006;
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
	// TODO: Your code goes here
	return 2;
}

