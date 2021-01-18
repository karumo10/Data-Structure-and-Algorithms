#include <iostream>

using namespace std;

class AVL {
private:
    struct node {
        int element;
        node* left;
        node* right;
        int height;
    };
    node* root;
    int getHeight(node* aim);
    void delAll(node* victim);
    node* findHelper(node* aim, int ele);
    node* leftRotate(node* curr);
    node* rightRotate(node* curr);
    node* left_rightRotate(node* curr);
        // REQUIRES: curr->left->right exists
    node* right_leftRotate(node* curr);
        // REQUIRES: curr->right->left exists
    int updateHeight(node* curr);
        // EFFECTS: update all the height fields in the descendants of curr
    bool isBalanced(node* curr);
    node* findDeepestUnbalanced(node* curr);
        // REQUIRES: the node is not empty
    node* rebalance(node* curr);
    node* insertHelper(int element, node* curr);
    node* delHelper(int element, node* curr);
    node* findMax(node* curr);
        // REQUIRES: the node is not empty
    node* findMin(node* curr);
        // REQUIRES: the node is not empty
public:
    bool isEmpty();
    AVL();
    node* find(int element);
    void insert(int element);
    AVL& operator+(int element);
    void del(int element);
    ~AVL();
};

AVL::AVL() : root(nullptr) {}

bool AVL::isEmpty() {
    return (root == nullptr);
}

int AVL::getHeight(node* aim) {
    if (aim == nullptr)
        return -1;
    else
    {
        return aim->height;
    }
    
}

void AVL::delAll(node* victim) {
    if (victim == nullptr) return;
    else {
        delAll(victim->left);
        delAll(victim->right);
        victim->left = victim->right = nullptr;
        delete victim;
    }
}

AVL::~AVL() {
    delAll(this->root);
}

AVL::node* AVL::findHelper(node* aim, int ele) {
    if (aim == nullptr) return nullptr;
    if (aim->element == ele)
        return aim;
    else if (aim->element > ele) {
        return findHelper(aim->left, ele);
    } else {
        return findHelper(aim->right, ele);
    }
}

AVL::node* AVL::find(int element) {
    node* ans = findHelper(this->root, element);
    return ans;
}

AVL::node* AVL::leftRotate(node* curr) {
    if (curr == nullptr) return curr;
    if (curr->right == nullptr) return curr; // invalid. just return original tree
    node* right = curr->right;
    node* right_left = right->left;
    curr->right = right_left;
    right->left = curr;
    updateHeight(right);
    return right;
}

AVL::node* AVL::rightRotate(node* curr) {
    if (curr == nullptr) return curr;
    if (curr->left == nullptr) return curr; // invalid. just return original tree
    node* left = curr->left;
    node* left_right = left->right;
    curr->left = left_right;
    left->right = curr;
    updateHeight(left);
    return left;
}

AVL::node* AVL::left_rightRotate(node* curr) {
    curr->left = leftRotate(curr->left);
    curr = rightRotate(curr);
    updateHeight(curr);
    return curr;
}

AVL::node* AVL::right_leftRotate(node* curr) {
    curr->right = rightRotate(curr->right);
    curr = leftRotate(curr);
    updateHeight(curr);
    return curr;
}

int AVL::updateHeight(node* curr) {
    if (curr == nullptr) return -1;
    else {
        int heiLeft = updateHeight(curr->left);
        int heiRight = updateHeight(curr->right);
        curr->height =  heiLeft > heiRight ? heiLeft+1 : heiRight+1 ;
        return curr->height;
    }
}

bool AVL::isBalanced(node* curr) {
    if (curr == nullptr) return true;
    int heiLeft = getHeight(curr->left);
    int heiRight = getHeight(curr->right);
    if (heiLeft - heiRight >= 2 || heiRight - heiLeft >= 2)
        return false;
    else return true; 
}

AVL::node* AVL::findDeepestUnbalanced(node* curr) {
    bool currIs = isBalanced(curr);
    bool leftIs = isBalanced(curr->left);
    bool rightIs = isBalanced(curr->right);
    node* ans = curr; // default value is curr. if it is balnced, it will return curr.
    if (!currIs) {
        if (!leftIs)
            ans = findDeepestUnbalanced(curr->left); // it's impossible that both left and right are unbalanced. so ignored
        else if (!rightIs)
            ans = findDeepestUnbalanced(curr->right); 
        else
            return curr; // this is answer. (left subtree and right subtree are balanced but itself is not balanced)
    }
    return ans;
}

AVL::node* AVL::rebalance(node* curr) {
    node* aim = findDeepestUnbalanced(curr);
    node* left = aim->left;
    node* right = aim->right;
    int leftH = getHeight(left), rightH = getHeight(right);
    if (leftH > rightH) { // left subtree deeper
        node* left_left = left->left;
        node* left_right = left->right;
        int left_leftH = getHeight(left_left), left_rightH = getHeight(left_right);
        if (left_leftH > left_rightH) {
            return rightRotate(curr);
        } else {
            return left_rightRotate(curr);
        } 
    } else { // right subtree deeper
        node* right_left = right->left;
        node* right_right = right->right;
        int right_leftH = getHeight(right_left), right_rightH = getHeight(right_right);
        if (right_leftH > right_rightH) {
            return right_leftRotate(curr);
        } else {
            return leftRotate(curr);
        } 
    }
}

AVL::node* AVL::insertHelper(int element, node* curr) {
    if (curr == nullptr) {
        node* inserted = new node;
        inserted->element = element;
        inserted->left = nullptr;
        inserted->right = nullptr;
        inserted->height = 0;
        curr = inserted;
    } else {
        int currele = curr->element;
        if (currele == element) 
            return curr;
        else if (currele > element) {
            curr->left = insertHelper(element, curr->left); // recursion towards the empty node
            curr->height = getHeight(curr->left) > getHeight(curr->right) ? getHeight(curr->left) + 1 : getHeight(curr->right) + 1;
                // updating height
            if (!isBalanced(curr)) { // it must be (left > right)
                if (curr->left->element > element)
                    curr = rightRotate(curr);
                else
                    curr = left_rightRotate(curr); // judging the inner or outer situation
            }
        }
        else {
            curr->right = insertHelper(element, curr->right);
            curr->height = getHeight(curr->left) > getHeight(curr->right) ? getHeight(curr->left) + 1 : getHeight(curr->right) + 1;
            if (!isBalanced(curr)) { // it must be (right > left)
                if (curr->right->element < element) 
                    curr = leftRotate(curr);
                else
                    curr = right_leftRotate(curr);
            }
        }
    }
    return curr;
}

void AVL::insert(int element) {
    root = insertHelper(element, root);
}

AVL& AVL::operator+(int element) {
    insert(element);
    return *this;
}
AVL::node* AVL::findMin(node* curr) {
    if (curr->left == nullptr)
        return curr;
    else
        return findMin(curr->left);
}

AVL::node* AVL::findMax(node* curr) {
    if (curr->right == nullptr)
        return curr;
    else
        return findMax(curr->right);
}


AVL::node* AVL::delHelper(int element, node* curr) {
    if (curr->element == element) {
        node* victim = curr;
        if (curr->left == nullptr) {
            curr = curr->right;
            delete victim;
        } else if (curr->right == nullptr) {
            curr = curr->left;
            delete victim;
        } else {
            int eleCopied = findMin(curr->right)->element;
            curr->element = eleCopied;
            curr->right = delHelper(eleCopied, curr->right);
            if (!isBalanced(curr)) { // it must be left > right. thus left cannot be empty
                if (getHeight(curr->left->left) >= getHeight(curr->left->right))  // outer situation
                    curr = rightRotate(curr);
                else // inner
                    curr = left_rightRotate(curr); 
             }      
        }
    } else if (curr->element > element) { // delete a node in lefthandside
        curr->left = delHelper(element, curr->left);
        curr->height = getHeight(curr->left) > getHeight(curr->right) ? getHeight(curr->left) + 1 : getHeight(curr->right) + 1;
        if (!isBalanced(curr)) { // it must be right > left. thus right cannot be empty
            if (getHeight(curr->right->right) >= getHeight(curr->right->left))  // outer situation
                curr = leftRotate(curr);
            else // inner
                curr = right_leftRotate(curr);
        }
    } else { // delete a node in righthandside
        curr->right = delHelper(element, curr->right);
        curr->height = getHeight(curr->left) > getHeight(curr->right) ? getHeight(curr->left) + 1 : getHeight(curr->right) + 1;
        if (!isBalanced(curr)) { // it must be left > right. thus left cannot be empty
            if (getHeight(curr->left->left) >= getHeight(curr->left->right))  // outer situation
                curr = rightRotate(curr);
            else // inner
                curr = left_rightRotate(curr); 
        }      
    }
    return curr; 
}
void AVL::del(int element) {
    root = delHelper(element, root);
}


int main() {
    AVL a;
    a=a+3+2+1+4+5+6+7+16+15+14+13+12+11+10+8+9;
    a.del(11);
    return 0;
}

 

/*
test cases:
1. insert
2. height updating
3. single rotate
4. double rotate
5. leaf node delete
6. delete node (with nonempty left subtree)
7. delete node (with nonempty left and right subt)
8. (待测) 删除之后旋转
exceptions:



*/