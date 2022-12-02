#include <iostream>
#include <memory>
#include "Player.h"
#include "AVLTree.h"
#include "ComparePlayerById.h"
#include "worldcup23a1.h"




int main()
{
    std::cout << "Hello, World!" << std::endl;

    world_cup_t worldCup;
    worldCup.add_team(34, 15);
    worldCup.add_team(12, 5);
    worldCup.add_team(58, 24);
    worldCup.add_team(70, 29);
    worldCup.add_team(99, 14);
    worldCup.add_team(69, 1);

    worldCup.add_player(3,12,3,4,2, false);
    worldCup.add_player(6,12,0,0,0, true);
    worldCup.add_player(1,34,30,5,4, false);
    worldCup.add_player(7,34,10,6,2, true);
    worldCup.add_player(2,34,5,6,3, false);


    for (int i = 100; i < 115; ++i) {
        worldCup.add_player(i, 34, 0,0,0, false);
    }
    for (int i = 200; i < 215; ++i) {
        worldCup.add_player(i, 99, 3,2,1, true);
    }
    for (int i = 300; i < 315; ++i) {
        worldCup.add_player(i, 12, 4,4,1, true);
    }
    for (int i = 400; i < 415; ++i) {
        worldCup.add_player(i, 58, 3,1,1, true);
    }
    for (int i = 500; i < 515; ++i) {
        worldCup.add_player(i, 70, 6,5,3, true);
    }

    std::cout << worldCup.knockout_winner(12,999).ans() << std::endl;

    worldCup.remove_player(403);
    worldCup.remove_player(6);
    worldCup.remove_team(69);
    StatusType temp1 = worldCup.update_player_stats(6,1,1,1);
    if(temp1 == StatusType::FAILURE)
    {
        std::cout << "good" << std::endl;
    }
    output_t<int> temp2 = worldCup.get_team_points(69);
    if(temp2.status() == StatusType::FAILURE)
    {
        std::cout << "good" << std::endl;
    }

    if(worldCup.unite_teams(34, 12, 300) == StatusType::SUCCESS)
    {
        std::cout << "good" << std::endl;
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
