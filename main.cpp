#include <iostream>
#include <memory>
#include "Player.h"
#include "AVLTree.h"
#include "ComparePlayerById.h"
#include "worldcup23a1.h"
#include "assert.h"




int main()
{
//    std::cout << "Hello, World!" << std::endl;
//
//    world_cup_t worldCup;
//    worldCup.add_team(34, 15);
//    worldCup.add_team(12, 5);
//    worldCup.add_team(58, 24);
//    worldCup.add_team(70, 29);
//    worldCup.add_team(99, 14);
//    worldCup.add_team(69, 1);
//
//    worldCup.add_player(3,12,3,4,2, false);
//    worldCup.add_player(6,12,0,0,0, true);
//    worldCup.add_player(1,34,30,5,4, false);
//    worldCup.add_player(7,34,10,6,2, true);
//    worldCup.add_player(2,34,5,6,3, false);
//
//
//    for (int i = 100; i < 115; ++i) {
//        worldCup.add_player(i, 34, 0,0,0, false);
//    }
//    for (int i = 200; i < 215; ++i) {
//        worldCup.add_player(i, 99, 3,2,1, true);
//    }
//    for (int i = 300; i < 315; ++i) {
//        worldCup.add_player(i, 12, 4,4,1, true);
//    }
//    for (int i = 400; i < 415; ++i) {
//        worldCup.add_player(i, 58, 3,1,1, true);
//    }
//    for (int i = 500; i < 515; ++i) {
//        worldCup.add_player(i, 70, 6,5,3, true);
//    }
//
//    std::cout << worldCup.knockout_winner(12,999).ans() << std::endl;
//
//    worldCup.remove_player(403);
//    worldCup.remove_player(6);
//    worldCup.remove_team(69);
//    StatusType temp1 = worldCup.update_player_stats(6,1,1,1);
//    if(temp1 == StatusType::FAILURE)
//    {
//        std::cout << "good" << std::endl;
//    }
//    output_t<int> temp2 = worldCup.get_team_points(69);
//    if(temp2.status() == StatusType::FAILURE)
//    {
//        std::cout << "good" << std::endl;
//    }
//
//    if(worldCup.unite_teams(34, 12, 300) == StatusType::SUCCESS)
//    {
//        std::cout << "good" << std::endl;
//    }



    try{
        world_cup_t worldCup;
        StatusType sResult;

        sResult = worldCup.add_team(10, 1);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(2, 0);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(3, 4);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(9, 1);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(4, 1);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(8, 3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(6, 3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(7, 2);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(1, 3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_team(5, 3);
        assert(sResult == StatusType::SUCCESS);


        sResult = worldCup.add_player(1, 5, 3, 3, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(2, 6, 2, 4, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(3, 6, 3, 2, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(4, 6, 4, 2, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(5, 4, 1, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(6, 9, 3, 1, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(7, 1, 3, 1, 3, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(8, 8, 2, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(9, 8, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(10, 8, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(11, 10, 4, 3, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(12, 10, 2, 4, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(13, 10, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(14, 8, 2, 1, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(15, 6, 0, 2, 3, false);
        assert(sResult == StatusType::INVALID_INPUT);
        sResult = worldCup.add_player(15, 6, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(16, 2, 4, 2, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(17, 7, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(18, 3, 1, 1, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(19, 2, 3, 2, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(20, 2, 4, 4, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(21, 5, 1, 3, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(22, 7, 4, 0, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(23, 6, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(24, 2, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(25, 9, 2, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(26, 9, 4, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(27, 5, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(28, 9, 1, 2, 1, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(29, 7, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(30, 7, 3, 3, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(31, 7, 2, 2, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(32, 7, 4, 1, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(33, 6, 2, 2, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(34, 2, 4, 3, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(35, 8, 3, 3, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(36, 9, 3, 0, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(37, 1, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(38, 3, 4, 4, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(39, 5, 2, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(40, 10, 4, 4, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(41, 10, 1, 1, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(42, 6, 3, 1, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(43, 7, 1, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(44, 1, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(45, 1, 4, 3, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(46, 7, 1, 1, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(47, 9, 1, 2, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(48, 7, 1, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(49, 4, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(50, 3, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(51, 2, 3, 4, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(52, 2, 2, 4, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(53, 5, 4, 4, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(54, 5, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(55, 8, 3, 2, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(56, 7, 4, 4, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(57, 10, 2, 1, 1, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(58, 3, 4, 4, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(59, 8, 2, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(60, 8, 2, 3, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(61, 2, 1, 3, 2, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(62, 3, 2, 1, 3, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(63, 8, 2, 4, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(64, 1, 2, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(65, 7, 1, 2, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(66, 2, 1, 1, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(67, 2, 2, 4, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(68, 4, 4, 1, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(69, 6, 3, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(70, 7, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(71, 8, 3, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(72, 6, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(73, 7, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(74, 10, 2, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(75, 8, 3, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(76, 1, 2, 1, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(77, 7, 3, 0, 2, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(78, 1, 2, 2, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(79, 10, 4, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(80, 5, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(81, 2, 1, 0, 3, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(82, 9, 4, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(83, 7, 10, 15, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(83, 7, 10, 15, 0, true);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.add_player(84, 10, 3, 0, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(85, 7, 4, 3, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(86, 6, 4, 2, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(87, 3, 4, 0, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(88, 10, 4, 1, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(89, 6, 2, 3, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(90, 9, 2, 10, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(91, 4, 0, 0, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(92, 3, 1, 0, 1, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(93, 7, 1, 1, 4, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(94, 6, 4, 3, 3, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(95, 4, 1, 3, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(96, 4, 3, 4, 0, false);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(97, 4, 2, 3, 4, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(98, 3, 0, 0, 0, true);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.add_player(99, 5, 3, 0, 1, false);
        assert(sResult == StatusType::SUCCESS);

        assert(worldCup.get_top_scorer(-1).ans() == 83);
        assert(worldCup.get_top_scorer(7).ans() == 83);
        worldCup.update_player_stats(22, 5, 40, 3);
        assert(worldCup.get_top_scorer(-1).ans() == 22);
        assert(worldCup.get_top_scorer(7).ans() == 22);
        assert(worldCup.get_top_scorer(9).ans() == 90);
        assert(worldCup.get_closest_player(98, 3).ans() == 91);
        assert(worldCup.get_closest_player(49, 4).ans() == 50);
        worldCup.unite_teams(1, 9, 19);
        sResult = worldCup.remove_team(1);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_team(9);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_team(19);
        assert(sResult == StatusType::FAILURE);
        int winner = worldCup.knockout_winner(2, 20).ans(); //Only 2, 6, 7 and 19 are competing
        worldCup.play_match(2, 19);
        worldCup.unite_teams(2, 7, 2);
        assert(worldCup.get_num_played_games(16).ans() == 5);

        // Remove team 6
        sResult = worldCup.remove_player(2);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(3);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(4);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(15);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(23);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(33);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(42);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(69);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(72);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(86);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(89);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::FAILURE);
        sResult = worldCup.remove_player(94);
        assert(sResult == StatusType::SUCCESS);
        sResult = worldCup.remove_team(6);
        assert(sResult == StatusType::SUCCESS);
        std::cout << "Test run successfully" << std::endl;
        return 0;
    } catch(...){
        return -1;
    }






//    std::shared_ptr<Player> player1 = std::shared_ptr<Player>(new Player(1, nullptr, 0, 0, 0, 0, false));
//    std::shared_ptr<Player> player2 = std::shared_ptr<Player>(new Player(2, nullptr, 0, 0, 0, 0, false));
//    std::shared_ptr<Player> player12 = std::shared_ptr<Player>(new Player(12, nullptr, 0, 0, 0, 0, false));
//    std::shared_ptr<Player> player5 = std::shared_ptr<Player>(new Player(5, nullptr, 0, 0, 0, 0, false));
//    std::shared_ptr<Player> player10 = std::shared_ptr<Player>(new Player(10, nullptr, 0, 0, 0, 0, false));
//    std::shared_ptr<Player> player3 = std::shared_ptr<Player>(new Player(3, nullptr, 0, 0, 0, 0, false));

//    AVLTree<std::shared_ptr<Player>, ComparePlayerById> playersById = AVLTree<std::shared_ptr<Player>, ComparePlayerById>();
//    playersById.root = playersById.insert(playersById.root, player1);
//    playersById.root = playersById.insert(playersById.root, player2);
//    playersById.root = playersById.insert(playersById.root, player12);
//    playersById.root = playersById.insert(playersById.root, player5);
//    playersById.root = playersById.insert(playersById.root, player10);
//    playersById.root = playersById.insert(playersById.root, player3);
//    std::cout<<playersById.root->data->playerID<<std::endl;
//
//    playersById.root = playersById.deleteNode(playersById.root, player5);
//    std::cout<<playersById.root->data->playerID<<std::endl;
//
//    playersById.root = playersById.deleteNode(playersById.root, player10);
//    playersById.root = playersById.deleteNode(playersById.root, player12);
//    std::cout<<playersById.root->data->playerID<<std::endl;
//
//    playersById.root = playersById.deleteNode(playersById.root, player1);
//    playersById.root = playersById.deleteNode(playersById.root, player2);
//    playersById.root = playersById.deleteNode(playersById.root, player3);

//    std::shared_ptr<Player> arr[]= {player1, player2, player3, player5, player10, player12};
//    AVLTree<std::shared_ptr<Player>, ComparePlayerById> almostFullById = AVLTree<std::shared_ptr<Player>, ComparePlayerById>(arr, 6);

//    std::shared_ptr<Player> arr[]= {player1, player2, player3, player5, player12};
//    AVLTree<std::shared_ptr<Player>, ComparePlayerById> almostFullById = AVLTree<std::shared_ptr<Player>, ComparePlayerById>(arr, 4);
//    AVLNode<std::shared_ptr<Player>>* playerNode = almostFullById.findNode(almostFullById.root, 3);
//    if(playerNode != nullptr)
//        std::cout<<playerNode->data->playerID <<std::endl;
//    else
//        std::cout<<"not found" <<std::endl;


//    ComparePlayerById comparePlayerById;

//    if(comparePlayerById.isLeftSmaller(player1, player2))
//        return 1;
//    return 2;
//
//
//
//
//    int length = 8;
//    int degree = 0, rootHeight = 0, fullNodesNum = 1, product = 1;
//    while(fullNodesNum < length)
//    {
//        product = product * 2;
//        fullNodesNum = product - 1;
//        degree++;
//        rootHeight = degree - 1;
//    }

//    AVL b;
//    b.root = b.insert(b.root, 3);
//    b.root = b.insert(b.root, 7);
//    b.root = b.insert(b.root, 8);
//    b.root = b.insert(b.root, 10);

//    b.root= b.deleteNode(b.root, 9);

//    b.root= b.deleteNode(b.root, b.root->data);
//    b.root= b.deleteNode(b.root, b.root->data);
//    b.root= b.deleteNode(b.root, b.root->data);
//    b.root= b.deleteNode(b.root, b.root->data);
    return 0;
}
