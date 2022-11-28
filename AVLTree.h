
#ifndef WET1_AVLTREE_H
#define WET1_AVLTREE_H

//template <class T>
//class Node
//{
//public:
//    Node<T> *left;
//    Node<T> *right;
//    T value;
//    int height;
//
//    int calculateHeight();
//
//};
//
//template <class T, class Compare>
//class AVLTree
//{
//public:
//    AVLTree();
//    explicit AVLTree(int nodesNum);
//    void insertData(T data);
//    void deleteData(T data);
//    T find(T data);
//    T findById(int id);
//
//private:
//    Node<T>* root;
//
//
//
//};
//
//template<class T, class Compare>
//AVLTree<T, Compare>::AVLTree() : root(nullptr)
//{}
//
//template<class T, class Compare>
//AVLTree<T, Compare>::AVLTree(int nodesNum)
//{
////later
//}





template<class T>
class AVLNode{
public:
    AVLNode<T> *left;
    AVLNode<T> *right;
    T data;
    int height;

    explicit AVLNode(T data1) : left(nullptr), right(nullptr), data(data1), height(0) {}
};


template<class T, class Compare>
class AVLTree
{
public:
    AVLNode<T> * root;
    Compare compare;

    AVLTree():root(nullptr), compare() {}

    AVLTree(T* array, int length)
    {
        int degree = 0, rootHeight = 0, fullNodesNum = 1, product = 1;
        while(fullNodesNum < length)
        {
            product = product * 2;
            fullNodesNum = product - 1;
            degree++;
            rootHeight = degree - 1;
        }


        int nodesToDelete = fullNodesNum - length, index = 0;
        root = createTreeWithNodes(root, rootHeight);
        root = removeNodeFullTree(root, rootHeight, &nodesToDelete);
        fillInOrder(root, array, length, &index);

    }

    AVLNode<T>* createTreeWithNodes(AVLNode<T>* current, int height)
    {
        if(height == -1)
        {
            return nullptr;
        }
        current = new AVLNode<T>(nullptr);
        current->height = height;
        current->left = createTreeWithNodes(current->left,height-1);
        current->right = createTreeWithNodes(current->right,height-1);
        return current;
    }

    AVLNode<T>* removeNodeFullTree(AVLNode<T>* current, int height, int* nodesToDelete)
    {
        if(*nodesToDelete == 0)
            return current;

        if(current == nullptr)
            return nullptr;

        if(current->left == nullptr && current->right == nullptr)
        {
            (*nodesToDelete)--;
            delete current;
            return nullptr;
        }
        current->right = removeNodeFullTree(current->right, height-1, nodesToDelete);
        current->left = removeNodeFullTree(current->left, height-1, nodesToDelete);
        current->height = calculateHeight(current);
        return current;

    }

    void fillInOrder(AVLNode<T>* current, T* array, int length, int* index)
    {
        if(current == nullptr)
            return;

        fillInOrder(current->left, array, length, index);
        current->data = array[*index];
        (*index)++;
        fillInOrder(current->right, array, length, index);

    }

    int calculateHeight(AVLNode<T> *node){

        if(node->left != nullptr && node->right != nullptr)
        {
            if (node->left->height < node->right->height)
                return node->right->height + 1;
            else
                return  node->left->height + 1;
        }
        else if(node->left != nullptr && node->right == nullptr)
        {
            return node->left->height + 1;
        }
        else if(node->left == nullptr && node->right != nullptr)
        {
            return node->right->height + 1;
        }
        return 0;

    }

    int getBalanceFactor(AVLNode<T> *node)
    {
        if(node == nullptr)
        {
            return -30;//impossible
        }
        if(node->left != nullptr && node->right != nullptr)
        {
            return node->left->height - node->right->height;
        }
        else if(node->left != nullptr && node->right == nullptr)
        {
            return node->left->height + 1;
        }
        else if(node->left == nullptr && node->right != nullptr)
        {
            return -1 - node->right->height;
        }
        else
        {
            return 0;
        }
    }

    AVLNode<T> * LLrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp;
        p = node;
        temp = p->left;

        p->left = temp->right;
        temp->right = p;

        p->height= calculateHeight(p);
        temp->height= calculateHeight(temp);
        return temp;
    }


    AVLNode<T> * RRrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp;
        p = node;
        temp = p->right;

        p->right = temp->left;
        temp->left = p;

        p->height= calculateHeight(p);
        temp->height= calculateHeight(temp);
        return temp;
    }


    AVLNode<T> * RLrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp1;
        AVLNode<T> *temp2;
        p = node;
        temp1 = p->right;
        temp2 = p->right->left;

        p -> right = temp2->left;
        temp1 ->left = temp2->right;
        temp2 ->left = p;
        temp2->right = temp1;

        p->height= calculateHeight(p);
        temp1->height= calculateHeight(temp1);
        temp2->height= calculateHeight(temp2);
        return temp2;
    }

    AVLNode<T> * LRrotation(AVLNode<T> *node){
        AVLNode<T> *p;
        AVLNode<T> *temp1;
        AVLNode<T> *temp2;
        p = node;
        temp1 = p->left;
        temp2 = p->left->right;

        p -> left = temp2->right;
        temp1 ->right = temp2->left;
        temp2 ->right = p;
        temp2->left = temp1;

        p->height= calculateHeight(p);
        temp1->height= calculateHeight(temp1);
        temp2->height= calculateHeight(temp2);

        return temp2;
    }

    AVLNode<T>* insert(AVLNode<T> *current, T data){

        if(current == nullptr){
//            AVLNode<T> *n;
//            n = new AVLNode<T>;
//            n->data = data;
//            current = n;
            current = new AVLNode<T>(data);
//            current->left = nullptr;
//            current->right = nullptr;
//            current->height = 0;
            return current;
        }
        else
        {
            if(compare.isLeftSmaller(current->data, data, true))
                current->right = insert(current->right, data);
            else
                current->left = insert(current->left, data);

        }

        current->height = calculateHeight(current);

        if(getBalanceFactor(current) == 2 &&
            (getBalanceFactor(current->left) == 1 || getBalanceFactor(current->left) == 0)){
            current = LLrotation(current);
        }
        else if(getBalanceFactor(current) == -2 &&
            (getBalanceFactor(current->right) == -1 || getBalanceFactor(current->right) == 0)){
            current = RRrotation(current);
        }
        else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == 1){
            current = RLrotation(current);
        }
        else if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == -1){
            current = LRrotation(current);
        }


        return current;

    }

    template<class S>
    AVLNode<T>* findNode(AVLNode<T> *current, S data)
    {
        if(current == nullptr)
            return nullptr;

        if(compare.isEqual(current->data, data))
        {
            return current;
        }
        else if(compare.isLeftSmaller(current->data, data, false))
        {
            return findNode(current->right, data);
        }
        else
        {
            return findNode(current->left, data);
        }

    }

    template<class S>
    AVLNode<T> * deleteNode(AVLNode<T> *current, S data){
        if(current->left == nullptr && current->right == nullptr){
            if(compare.isEqual(current->data, data))
            {
                if (current == this->root)
                    this->root = nullptr;
                current->left= nullptr;
                current->right= nullptr;
                delete current;
                return nullptr;
            }
            return current;
        }

        AVLNode<T> *temp;

        if(compare.isLeftSmaller(current->data, data, false)) //current->data < data
        {
            current->right = deleteNode(current->right,data);
        }
        else if(!compare.isEqual(current->data, data)) // checking current->data > data
        {
            current->left = deleteNode(current->left,data);
        }
        else //they are equal
        {
            if(current->left != nullptr)
            {
                temp = findRightestSon(current->left);
                current->data = temp->data;
                current->left=deleteNode(current->left, temp->data);
            }
            else
            {
//                temp = findLeftestSon(p->right);
//                p->data = temp->data;
                current->data = current->right->data;
                current->right = deleteNode(current->right,current->right->data);
            }
        }

        current->height= calculateHeight(current);

        //checking for rotations
        if(getBalanceFactor(current) == 2 &&
                (getBalanceFactor(current->left) == 0 || getBalanceFactor(current->left) == 1))
            current = LLrotation(current);
        else if(getBalanceFactor(current) == 2 && getBalanceFactor(current->left) == -1)
            current = LRrotation(current);
        else if(getBalanceFactor(current) == -2 &&
            (getBalanceFactor(current->right) == -1 || getBalanceFactor(current->right) == 0))
            current = RRrotation(current);
        else if(getBalanceFactor(current) == -2 && getBalanceFactor(current->right) == 1)
            current = RLrotation(current);


        return current;
    }

    AVLNode<T>* findRightestSon(AVLNode<T>* node){
        while(node->right != nullptr)
            node = node->right;
        return node;
    }

    AVLNode<T>* findLeftestSon(AVLNode<T>* p){
        while(p->left != nullptr)
            p = p->left;

        return p;
    }


    void deletePostorder(AVLNode<T>* node)
    {
        if (node == nullptr) return;

        //delete both subtrees
        deletePostorder(node->left);
        deletePostorder(node->right);

        //delete the node
        node->left = nullptr;
        node->right = nullptr;
        delete node;

    }


    ~AVLTree(){
        deletePostorder(root);
        root= nullptr;
    }
};



#endif //WET1_AVLTREE_H
