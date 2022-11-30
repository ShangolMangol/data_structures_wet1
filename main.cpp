#include <iostream>
#include <memory>
#include "Player.h"
#include "AVLTree.h"
#include "ComparePlayerById.h"
#include "worldcup23a1.h"

//struct node {
//    struct node *left;
//    int data;
//    int height;
//    struct node *right;
//
//};
//
//class AVL
//{
//private:
//
//public:
//    struct node * root;
//    AVL(){
//        this->root = NULL;
//
//    }
//
//    int calculateHeight(struct node *p){
//
//        if(p->left && p->right)
//        {
//            if (p->left->height < p->right->height)
//                return p->right->height + 1;
//            else
//                return  p->left->height + 1;
//        }
//        else if(p->left && p->right == NULL)
//        {
//            return p->left->height + 1;
//        }
//        else if(p->left ==NULL && p->right)
//        {
//            return p->right->height + 1;
//        }
//        return 0;
//
//    }
//
//    int getBalanceFactor(struct node *n){
//        if(n->left && n->right){
//            return n->left->height - n->right->height;
//        }
//        else if(n->left && n->right == NULL){
//            return n->left->height + 1;
//        }
//        else if(n->left== NULL && n->right ){
//            return -1 - n->right->height;
//        }
//    }
//
//    struct node * llrotation(struct node *n){
//        struct node *p;
//        struct node *tp;
//        p = n;
//        tp = p->left;
//
//        p->left = tp->right;
//        tp->right = p;
//
//        p->height= calculateHeight(p);
//        tp->height= calculateHeight(tp);
//        return tp;
//    }
//
//
//    struct node * rrrotation(struct node *n){
//        struct node *p;
//        struct node *tp;
//        p = n;
//        tp = p->right;
//
//        p->right = tp->left;
//        tp->left = p;
//
//        p->height= calculateHeight(p);
//        tp->height= calculateHeight(tp);
//        return tp;
//    }
//
//
//    struct node * rlrotation(struct node *n){
//        struct node *p;
//        struct node *tp;
//        struct node *tp2;
//        p = n;
//        tp = p->right;
//        tp2 =p->right->left;
//
//        p -> right = tp2->left;
//        tp ->left = tp2->right;
//        tp2 ->left = p;
//        tp2->right = tp;
//
//        p->height= calculateHeight(p);
//        tp->height= calculateHeight(tp);
//        p->height= calculateHeight(tp2);
//        return tp2;
//    }
//
//    struct node * lrrotation(struct node *n){
//        struct node *p;
//        struct node *tp;
//        struct node *tp2;
//        p = n;
//        tp = p->left;
//        tp2 =p->left->right;
//
//        p -> left = tp2->right;
//        tp ->right = tp2->left;
//        tp2 ->right = p;
//        tp2->left = tp;
//
//        p->height= calculateHeight(p);
//        tp->height= calculateHeight(tp);
//        p->height= calculateHeight(tp2);
//
//        return tp2;
//    }
//
//    struct node* insert(struct node *r,int data){
//
//        if(r==NULL){
//            struct node *n;
//            n = new struct node;
//            n->data = data;
//            r = n;
//            r->left = r->right = NULL;
//            r->height = 0; //changed here
//            return r;
//        }
//        else{
//            if(data < r->data)
//                r->left = insert(r->left,data);
//            else
//                r->right = insert(r->right,data);
//        }
//
//        r->height = calculateHeight(r);
//
//        if(getBalanceFactor(r) == 2 && getBalanceFactor(r->left) == 1){
//            r = llrotation(r);
//        }
//        else if(getBalanceFactor(r) == -2 && getBalanceFactor(r->right) == -1){
//            r = rrrotation(r);
//        }
//        else if(getBalanceFactor(r) == -2 && getBalanceFactor(r->right) == 1){
//            r = rlrotation(r);
//        }
//        else if(getBalanceFactor(r) == 2 && getBalanceFactor(r->left) == -1){
//            r = lrrotation(r);
//        }
//
//
//        return r;
//
//    }
//
//
//
//    struct node * deleteNode(struct node *p,int data){
//        if(p->left == NULL && p->right == NULL){
//            if(p->data == data)
//            {
//                if (p == this->root)
//                    this->root = NULL;
//                p->left= nullptr;
//                p->right= nullptr;
//                delete p;
//                return NULL;
//            }
//            return p;
//        }
//
//        struct node *q;
//        if(p->data < data){
//            p->right = deleteNode(p->right,data);
//        }
//        else if(p->data > data){
//            p->left = deleteNode(p->left,data);
//        }
//        else{
//            if(p->left != NULL){
//                q = findRightestSon(p->left);
//                p->data = q->data;
//                p->left=deleteNode(p->left,q->data);
//            }
//            else{
////                q = findLeftestSon(p->right);
////                p->data = q->data;
//                p->data = p->right->data;
//                p->right = deleteNode(p->right,p->right->data);
//            }
//        }
//
//        p->height= calculateHeight(p);
//
//        if(getBalanceFactor(p) == 2 && getBalanceFactor(p->left) == 1){ p = llrotation(p); }
//        else if(getBalanceFactor(p) == 2 && getBalanceFactor(p->left) == -1){ p = lrrotation(p); }
//        else if(getBalanceFactor(p) == 2 && getBalanceFactor(p->left) == 0){ p = llrotation(p); }
//        else if(getBalanceFactor(p) == -2 && getBalanceFactor(p->right) == -1){ p = rrrotation(p); }
//        else if(getBalanceFactor(p) == -2 && getBalanceFactor(p->right) == 1){ p = rlrotation(p); }
//        else if(getBalanceFactor(p) == -2 && getBalanceFactor(p->right) == 0){ p = llrotation(p); }
//
//
//        return p;
//    }
//
//    struct node* findRightestSon(struct node* p){
//        while(p->right!=NULL)
//            p = p->right;
//        return p;
//    }
//
//    struct node* findLeftestSon(struct node* p){
//        while(p->left!=NULL)
//            p = p->left;
//
//        return p;
//    }
//
//
//    void deletePostorder(struct node* node)
//    {
//        if (node == NULL) return;
//
//        /* first delete both subtrees */
//        deletePostorder(node->left);
//        deletePostorder(node->right);
//
//        /* then delete the node */
//        std::cout << "\n Deleting node: " << node->data;
//        node->left = nullptr;
//        node->right = nullptr;
//        delete node;
//
//    }
//
//
//    ~AVL(){
//        deletePostorder(root);
//        root= nullptr;
//    }
//};

int main()
{
    std::cout << "Hello, World!" << std::endl;

    world_cup_t worldCup;
    worldCup.add_team(34, 15);
    worldCup.add_team(12, 5);
    worldCup.add_team(58, 24);
    worldCup.add_team(70, 29);

    worldCup.add_player(3,12,3,4,2, false);
    worldCup.add_player(6,12,0,0,0, true);
    worldCup.add_player(1,34,30,5,4, false);
    worldCup.add_player(7,34,10,6,2, true);
    worldCup.add_player(2,34,5,6,3, false);
    worldCup.remove_team(58);


    for (int i = 100; i < 115; ++i) {
        worldCup.add_player(i, 34, 0,0,0, false);
    }

    worldCup.remove_player(7);















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
