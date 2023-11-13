/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                        Libraries, Types, Global variables..                                      */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

#include <iostream>
using namespace std;

//balance하다면 0(=false), unbalance하다면 1~4(=true)
enum UNBLANCE_CASE {
    BALANCE = 0, 
    LEFT_LEFT = 1, 
    RIGHT_RIGHT = 2, 
    LEFT_RIGHT = 3, 
    RIGHT_LEFT = 4 
};




/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                                 Class declaration                                                */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

struct Node {
public:
    //생성자와 소멸자
    Node(int key) : key_(key), height_(1) { left_child_ = right_child_ = NULL; }
    ~Node() {}

    //접근자
    int get_key() { return key_; }
    int get_height() { return height_; }
    Node* get_left_child() { return left_child_; }
    Node* get_right_child() { return right_child_; }

    //제어자
    void set_key(int key) { key_ = key; }
    void set_height(int height) { height_ = height; }
    void set_left_child(Node* left_child) { left_child_ = left_child; }
    void set_right_child(Node* right_child) { right_child_ = right_child; }

private:

    int key_;
    int height_;
    Node* left_child_;
    Node* right_child_;
};


class AVLTree {
public:
    //생성자
    AVLTree() : root_(NULL), size_(0) {}

    //접근자
    int get_size() { return size_; }
    Node* get_root() { return root_; }

    //제어자
    void increaseSize() { size_++; }
    void decreaseSize() { size_--; }
    void set_root(Node* root) { root_ = root; }

    //요구 사항(basic)
    void empty() { (size_ == 0) ? printf("1\n") : printf("0\n"); }
    void size() { printf("%d\n", size_); }
    void minimum(int x);
    void maximum(int x);
    void find(int x);
    void insert(int x);

    //요구 사항(advance)
    void rank(int x);
    void erase(int x);

private:
    //노드 상태 계산 함수
    Node* getNode(int key);
    int getDepth(Node* node);
    int getHeight(Node* node) { return (node == NULL) ? 0 : node->get_height(); }
    int isUnbalance(Node* node);
    int calculateBalanceFactor(Node* node);
    int calculateHeight(Node* node);
    int getRank(Node *node, int x);

    //기능 구현을 위한 추가적인 함수
    Node* insert(Node* node, int key);
    Node* restruct(Node* node);
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* node);

private:
    Node* root_;
    int size_;
};




/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                                  main function                                                   */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        AVLTree avlTree;
        int q;
        cin >> q;
        while (q--) {
            string command;
            cin >> command;

            //추가 입력(x) 불필요
            if (command == "empty") {
                avlTree.empty();
                continue;
            }
            if (command == "size") {
                avlTree.size();
                continue;
            }

            //추가 입력(x) 필요 
            int x;
            cin >> x;
            if (command == "minimum") {
                avlTree.minimum(x);
                continue;
            }
            if (command == "maximum") {
                avlTree.maximum(x);
                continue;
            }
            if (command == "find") {
                avlTree.find(x);
                continue;
            }
            if (command == "insert") {
                avlTree.insert(x);
                continue;
            }
            if (command == "rank") {
                avlTree.rank(x);
                continue;
            }
            if (command == "erase") {
                avlTree.erase(x);
                continue;
            }
        }
    }
}




/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                          AVLTree Class : Requirements definition                                 */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

//노드 x의 depth를 출력한다. 만약 노드 x가 없다면, 0을 출력한다.
void AVLTree::find(int x) {
    Node* find_node = getNode(x); //key == x인 노드 찾기

    if (find_node == NULL) printf("0\n");
    else printf("%d\n", getDepth(find_node));

    return;
}

//노드 x가 루트인 부분트리에서 최대 key를 갖는 노드의 key와 depth를 공백으로 구분하여 출력한다.
void AVLTree::maximum(int x) {
    Node* maximum_node = getNode(x); //key == x인 노드 찾기 -> sub root

    //최대 key: sub root의 가장 오른쪽 노드 -> loop로 해당 지점까지 내려간다.
    while (maximum_node->get_right_child() != NULL) {
        maximum_node = maximum_node->get_right_child();
    }
    printf("%d %d\n", maximum_node->get_key(), getDepth(maximum_node));
    
    return;
}

//노드 x가 루트인 부분트리에서 최소 key를 갖는 노드의 key와 depth를 공백으로 구분하여 출력한다.
void AVLTree::minimum(int x) {
    Node* minimum_node = getNode(x);

    //최소 key: sub root의 가장 왼쪽 노드 -> loop로 해당 지점까지 내려간다.
    while (minimum_node->get_left_child() != NULL) {
        minimum_node = minimum_node->get_left_child();
    }
    printf("%d %d\n", minimum_node->get_key(), getDepth(minimum_node));

    return;
}

//새로운 노드 x를 삽입하고, 노드 x의 depth를 출력한다.
void AVLTree::insert(int x) {
    //노드 삽입
    set_root(insert(root_, x));
    increaseSize();

    Node* new_node = getNode(x); //삽입한 노드의 포인터 가져오기
    printf("%d\n", getDepth(new_node));

    return;
}

//노드 x의 depth와 rank를 공백으로 구분하여 출력한다. 만약 노드 x가 없다면, 0을 출력한다.
void AVLTree::rank(int x)
{
    Node *rank_node = getNode(x); // key == x인 노드 찾기

    if (rank_node == NULL) printf("0\n"); // 노드 x가 없다면 0 출력
    else
    { // 노드 x가 존재할 때
        printf("%d ", getDepth(rank_node));
        printf("%d\n", getRank(get_root(), rank_node->get_key()) + 1); // 노드 x의 rank 출력
    }
}

//노드 x의 depth를 출력하고 해당 노드를 삭제한다. 만약 노드 x가 없다면, 0을 출력한다.

void AVLTree::erase(int x) {

}


/*------------------------------------------------------------------------------------------------------------------*/
/*                                                                                                                  */
/*                                        AVLTree Class : private function definition                               */
/*                                                                                                                  */
/*------------------------------------------------------------------------------------------------------------------*/

//주어진 key와 일치하는 노드를 찾아 노드의 포인터를 반환한다.
Node* AVLTree::getNode(int key) {
    Node* current_node = get_root(); //root부터 시작

    while (true) {
        if (current_node == NULL) return NULL; //찾기 실패
        else if (current_node->get_key() == key) return current_node; //찾기 성공

        //AVL tree의 성질을 고려하여, 왼쪽 혹은 아래쪽으로 내려가며 탐색한다.
        current_node = (current_node->get_key() < key) ? 
            current_node->get_right_child() : current_node->get_left_child();
    }

    return current_node;
}


//주어진 노드에 대해 깊이(depth)를 계산하여 반환한다.
int AVLTree::getDepth(Node* current_node) {
    if (current_node == get_root()) return 0; //root의 깊이는 0으로 정의

    int depth = 0;
    int key = current_node->get_key();
    Node* tempNode = root_;
    while (true) {
        if (current_node == tempNode) return depth;

        //AVL tree의 성질을 고려하여, 왼쪽 혹은 아래쪽으로 내려가며 depth를 증가시킨다.
        tempNode = (tempNode->get_key() < key) ? 
            tempNode->get_right_child() : tempNode->get_left_child();

        depth++;
    }
}


//주어진 노드에 대해 높이(height)를 계산하여 반환한다.
int AVLTree::calculateHeight(Node* node) {
    if (node == NULL) return -1; //존재하지 않는 노드의 높이는 -1, 리프 노드의 높이는 0으로 정의

    int left_child_height = getHeight(node->get_left_child());
    int right_child_height = getHeight(node->get_right_child());

    return max(left_child_height, right_child_height) + 1;
}


//주어진 노드에 대해 균형 인수(balance factor, left-right)를 계산하여 반환한다. 반환값은 -2~2 사이이다.
int AVLTree::calculateBalanceFactor(Node* node) {
    if (node == NULL) return 0; //존재하지 않는 노드의 균형인수는 0으로 정의

    int left_child_height = getHeight(node->get_left_child());
    int right_child_height = getHeight(node->get_right_child());

    return left_child_height - right_child_height;
}


//주어진 노드에 대해 균형 여부를 판단하여 반환한다. 반환값은 0(BALANCE), 1~4(UNBALNCE) 사이이다.
int AVLTree::isUnbalance(Node* curNode) {
    int balance_factor = calculateBalanceFactor(curNode);
    if (abs(balance_factor) < 2) return BALANCE;

    if (balance_factor > 0) {
        int child_balance_factor = calculateBalanceFactor(curNode->get_left_child());
        return (child_balance_factor > 0) ? LEFT_LEFT : LEFT_RIGHT;
    }

    else {
        int child_balance_factor = calculateBalanceFactor(curNode->get_right_child());
        return (child_balance_factor < 0) ? RIGHT_RIGHT : RIGHT_LEFT;
    }

}

//주어진 노드의 rank 반환. 재귀함수를 통해 자신보다 작은 값의 갯수를 더해준다.
int AVLTree::getRank(Node *node, int x)
{
    if (node == NULL) return 0; //노드가 존재하지 않으면 0 리턴

    int rank = 0;
    if (node->get_key() < x) rank++;

    rank += getRank(node->get_left_child(), x);
    rank += getRank(node->get_right_child(), x);

    return rank;
}

//실질적인 삽입을 수행한 뒤, 서브 트리의 루트 노드를 반환한다.
Node* AVLTree::insert(Node* node, int key) {
    //본인의 자리를 찾은 경우 -> 새 노드를 할당하여 반환
    if (node == NULL) {
        return new Node(key);
    }

    //본인의 자리를 찾지 못한 경우 -> 재귀적으로 내려가며 삽입 위치 탐색
    (node->get_key() < key) ?
        node->set_right_child(insert(node->get_right_child(), key)):
        node->set_left_child(insert(node->get_left_child(), key));

    //본인의 하위에 새로운 자식 노드가 추가되었으므로 높이 재계산
    node->set_height(calculateHeight(node));

    //재구조화 진행
    return restruct(node);
    
}

//주어진 노드가 불균형한 경우 적절히 회전하여 균형을 맞춘 뒤, 서브 트리의 루트 노드를 반환한다.
Node* AVLTree::restruct(Node* node) {
    switch (isUnbalance(node)) { //균형 여부 판단
    //균형 -> 0번의 회전 필요
    case BALANCE: {
        return node;
    }

    //불균형1 -> 1번의 회전 필요(single rotate)
    case LEFT_LEFT: {
        return rightRotate(node);
    }
    case RIGHT_RIGHT: {
        return leftRotate(node);
    }

    //불균형 -> 2번의 회전 필요(double rotate)
    case LEFT_RIGHT: {
        Node* child_node = node->get_left_child();
        node->set_left_child(leftRotate(child_node));
        return rightRotate(node);
    }
    case RIGHT_LEFT: {
        Node* child_node = node->get_right_child();
        node->set_right_child(rightRotate(child_node));
        return leftRotate(node);
    }
    }
    return node;
}

//문제가 된 노드를 인수로 받아 오른쪽 회전한 뒤, 그 결과(sub tree) 새롭게 루트가 된 노드를 반환한다.
Node* AVLTree::rightRotate(Node* zNode) {
    Node* yNode = zNode->get_left_child();
    Node* tNode = yNode->get_right_child();

    //회전 수행
    yNode->set_right_child(zNode);
    zNode->set_left_child(tNode);

    //회전하면서 위치가 달라졌으므로 높이 재계산
    zNode->set_height(calculateHeight(zNode));
    yNode->set_height(calculateHeight(yNode));

    return yNode;
}

//문제가 된 노드를 인수로 받아 왼쪽 회전한 뒤, 그 결과(sub tree) 새롭게 루트가 된 노드를 반환한다.
Node* AVLTree::leftRotate(Node* zNode) {
    Node* yNode = zNode->get_right_child();
    Node* tNode = yNode->get_left_child();

    //회전 수행
    yNode->set_left_child(zNode);
    zNode->set_right_child(tNode);

    //회전하면서 위치가 달라졌으므로 높이 재계산
    zNode->set_height(calculateHeight(zNode));
    yNode->set_height(calculateHeight(yNode));

    return yNode;
}