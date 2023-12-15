/*
The MIT License

Copyright (c) <2023> <Minsub Kim, Jiwon Park, Jeonghui Han>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include "AVLTree.h"
using namespace std;

// Node 클래스의 생성자 및 멤버 함수 구현
Node::Node(int key) : key_(key), height_(0), sub_size_(1), left_child_(NULL), right_child_(NULL) {}

Node::~Node() {}

int Node::get_key() { return key_; }
int Node::get_height() { return height_; }
int Node::get_sub_size() { return sub_size_; }
Node* Node::get_left_child() { return left_child_; }
Node* Node::get_right_child() { return right_child_; }

void Node::set_key(int key) { key_ = key; }
void Node::set_height(int height) { height_ = height; }
void Node::set_left_child(Node* left_child) { left_child_ = left_child; }
void Node::set_right_child(Node* right_child) { right_child_ = right_child; }
void Node::set_sub_size(int sub_size) { sub_size_ = sub_size; }

// AVLTree 클래스의 생성자 및 멤버 함수 구현
AVLTree::AVLTree() : root_(NULL) {}

Node* AVLTree::get_root() { return root_; }

void AVLTree::set_root(Node* root) { root_ = root; }


int AVLTree::GetHeight(Node* node) { return (node == NULL) ? -1 : node->get_height(); }
int AVLTree::GetSize(Node* node) { return (node == NULL) ? 0 : node->get_sub_size(); }

bool AVLTree::Empty() {
    return GetSize(root_) == 0;
}

int AVLTree::Size() {
    return GetSize(root_);
}
//------------------------------------------------------------------------------------------------------테스트를 위해 수정
//void AVLTree::Empty() { printf("%d\n", (GetSize(root_) == 0) ? 1 : 0); }
//void AVLTree::Size() { printf("%d\n", GetSize(root_)); }
//------------------------------------------------------------------------------------------------------

KeyDepthPair AVLTree::Maximum(int x) {
    Node* maximum_node = GetNode(x);
    while (maximum_node->get_right_child() != NULL) {
        maximum_node = maximum_node->get_right_child();
    }
    return { maximum_node->get_key(), GetDepth(maximum_node) };
}

KeyDepthPair AVLTree::Minimum(int x) {
    Node* minimum_node = GetNode(x);
    while (minimum_node->get_left_child() != NULL) {
        minimum_node = minimum_node->get_left_child();
    }
    return { minimum_node->get_key(), GetDepth(minimum_node) };
}

DepthRankPair AVLTree::Rank(int x) {
    Node* rank_node = GetNode(x);

    if (rank_node == NULL) {
        return { 0, 0 }; // 노드 x가 없을 경우, depth와 rank 모두 0으로 설정
    }
    else {
        int depth = GetDepth(rank_node);
        int rank = GetRank(get_root(), rank_node->get_key());
        return { depth, rank }; // 노드 x가 존재하는 경우, 해당 depth와 rank를 반환
    }
}

int AVLTree::Find(int x) {
    Node* find_node = GetNode(x);

    if (find_node == NULL) {
        return -1;  // 노드가 존재하지 않으면 -1 반환
    }
    else {
        return GetDepth(find_node);  // 노드가 존재하면 해당 노드의 깊이 반환
    }
}



// ----------------------------------------------------------------------------------------------------------------------------------------------
/*
//노드 x의 depth를 출력한다. 만약 노드 x가 없다면, 0을 출력한다.
void AVLTree::Find(int x) {
    Node* find_node = GetNode(x); //key == x인 노드 찾기

    //find_node가 NULL이라면 노드가 없다는 뜻이므로 0을 출력하고, 아니라면 노드의 depth를 출력한다.
    if (find_node == NULL) printf("0\n");
    else printf("%d\n", GetDepth(find_node));

    return;
}

//노드 x가 루트인 부분트리에서 최대 key를 갖는 노드의 key와 depth를 공백으로 구분하여 출력한다.
void AVLTree::Maximum(int x) {
    Node* maximum_node = GetNode(x); //key == x인 노드 찾기 -> sub root

    //최대 key는 sub root의 가장 최하단에 위치한 오른쪽 노드이므로 loop로 해당 지점까지 내려간다.
    while (maximum_node->get_right_child() != NULL) { //오른쪽 자식이 NULL이라면 최대로 내려온 것이므로 반복문 종료
        maximum_node = maximum_node->get_right_child();
    }
    printf("%d %d\n", maximum_node->get_key(), GetDepth(maximum_node));

    return;
}

//노드 x가 루트인 부분트리에서 최소 key를 갖는 노드의 key와 depth를 공백으로 구분하여 출력한다.
void AVLTree::Minimum(int x) {
    Node* minimum_node = GetNode(x);

    //최소 key는 sub root의 가장 최하단에 위치한 왼쪽 노드이므로 loop로 해당 지점까지 내려간다.
    while (minimum_node->get_left_child() != NULL) { //왼쪽 자식이 NULL이라면 최대로 내려온 것이므로 반복문 종료
        minimum_node = minimum_node->get_left_child();
    }
    printf("%d %d\n", minimum_node->get_key(), GetDepth(minimum_node));

    return;
}
*/
// ----------------------------------------------------------------------------------------------------------------------------------------------




//새로운 노드 x를 삽입하고, 노드 x의 depth를 출력한다.
void AVLTree::Insert(int x) {
    //노드 삽입. 실질적인 삽입은 private 함수에서 수행한다.
    set_root(Insert(root_, x));

    //삽입한 노드의 depth를 출력한다.
    Node* new_node = GetNode(x);
    printf("%d\n", GetDepth(new_node));

    return;
}




// ----------------------------------------------------------------------------------------------------------------------------------------------
/*
//노드 x의 depth와 rank를 공백으로 구분하여 출력한다. 만약 노드 x가 없다면, 0을 출력한다.
void AVLTree::Rank(int x) {
    Node* rank_node = GetNode(x); // key == x인 노드 찾기

    // 노드 x가 없다면 0을 출력하고 종료한다.
    if (rank_node == NULL) {
        printf("0\n");
        return;
    }
    // 노드 x가 존재한다면 depth와 rank를 출력한다.
    else {
        int depth = GetDepth(rank_node);
        int rank = GetRank(get_root(), rank_node->get_key());
        printf("%d %d\n", depth, rank);
        return;
    }
}
*/
// ----------------------------------------------------------------------------------------------------------------------------------------------


//노드 x의 depth를 출력하고 해당 노드를 삭제한다. 만약 노드 x가 없다면, 0을 출력한다.
void AVLTree::Erase(int x) {
    Node* node_to_delete = GetNode(x); // 삭제할 노드 찾기

    //만약 노드가 없으면 0을 출력하고 종료한다.
    if (node_to_delete == NULL) {
        printf("0\n");
        return;
    }

    //삭제할 노드의 깊이 출력
    int depth = GetDepth(node_to_delete);
    printf("%d\n", depth);

    //노드 삭제. 실질적인 삭제는 private 함수에서 수행한다.
    root_ = DeleteNode(root_, x);

    return;
}



//주어진 key와 일치하는 노드를 찾아 노드의 포인터를 반환한다.
Node* AVLTree::GetNode(int key) {
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
int AVLTree::GetDepth(Node* current_node) {
    if (current_node == get_root()) return 0; //root의 깊이는 0으로 정의

    //root부터 시작하여 특정 노드를 찾을 때까지 depth를 1증가시키며 내려간다.
    int depth = 0;
    int key = current_node->get_key();
    Node* tempNode = root_;
    while (true) {
        if (current_node == tempNode) return depth; //특정 노드를 찾았다면 종료

        //이때 AVL tree의 성질을 고려하여, 왼쪽 혹은 아래쪽으로 내려간다.
        tempNode = (tempNode->get_key() < key) ?
            tempNode->get_right_child() : tempNode->get_left_child();

        depth++;
    }
}


//주어진 노드에 대해 높이(height)를 계산하여 반환한다.
//height의 정의: 두 자식 노드 중 더 큰 height를 가지는 자식 노드의 height + 1
int AVLTree::CalculateHeight(Node* node) {
    //존재하지 않는 노드의 높이는 -1, 리프 노드의 높이는 0으로 정의한다.
    if (node == NULL) return -1;

    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    return max(left_child_height, right_child_height) + 1;
}

//주어진 노드에 대해 높이(height)를 계산하여 반환한다.
//sub size의 정의:양쪽 자식 노드의 크기 + 1(본인을 포함한 subTree의 크기)
int AVLTree::CalculateSubSize(Node* node) {
    //존재하지 않는 노드의 크기는 0, 리프 노드의 크기는 1로 정의한다.
    if (node == NULL) return 0;


    int left_child_size = GetSize(node->get_left_child());
    int right_child_size = GetSize(node->get_right_child());

    return left_child_size + right_child_size + 1;
}

//주어진 노드에 대해 균형 인수(balance factor)를 계산하여 반환한다. 반환값은 -2~2 사이이다.
//BalanceFactor의 정의: 두 자식 노드의 높이차 -> left child - right child로 정의
int AVLTree::CalculateBalanceFactor(Node* node) {
    if (node == NULL) return 0; //존재하지 않는 노드의 균형인수는 0으로 정의

    int left_child_height = GetHeight(node->get_left_child());
    int right_child_height = GetHeight(node->get_right_child());

    //이후 isUnBalance에서 불균형 케이스(UNBLANCE_CASE)를 분류하기 위해 절댓값은 씌우지 않고 반환한다.
    return left_child_height - right_child_height;
}


//주어진 노드에 대해 균형 여부를 판단하여 반환한다. 반환값은 0(BALANCE), 1~4(UNBALNCE) 사이이다.
int AVLTree::IsUnbalance(Node* curNode) {
    int balance_factor = CalculateBalanceFactor(curNode);
    if (abs(balance_factor) < 2) return BALANCE;

    //공지사항 반영: yNode의 두 자식 노드가 동일한 경우(child_balance_factor==0) single rotation을 수행하도록 한다.
    //cf. 기존 코드는 yNode의 balance_factor=1일 때만 LEFT_LEFT로 반환했지만, 공지사항에 따라 1 or 0인 경우로 조건문을 바꾸었다.

    //zNode의 balance_factor == 2: LL 혹은 LR
    if (balance_factor > 0) {
        int child_balance_factor = CalculateBalanceFactor(curNode->get_left_child()); //yNode의 balance_factor
        return (child_balance_factor < 0) ? LEFT_RIGHT : LEFT_LEFT;
    }
    //zNode의 balance_factor == -2: RR 혹은 RL
    else {
        int child_balance_factor = CalculateBalanceFactor(curNode->get_right_child()); //yNode의 balance_factor
        return (child_balance_factor > 0) ? RIGHT_LEFT : RIGHT_RIGHT;
    }

}

//주어진 노드의 rank 반환. 재귀함수를 통해 자신보다 작은 값의 갯수를 더해준다.
int AVLTree::GetRank(Node* node, int key) {
    //basecase: 본인이 NULL이라면 존재하지 않는 것이므로 0을 반환
    if (node == NULL)return 0;

    int node_key = node->get_key();
    //기준 키가 더 큰 경우 왼쪽+자신을 더한 뒤 오른쪽을 탐색해봐야 함
    if (node_key < key) {
        int sub_rank = GetSize(node->get_left_child()) + 1;
        return sub_rank + GetRank(node->get_right_child(), key);
    }
    //기준 키와 동일하다면 곧 자신의 위치를 찾은 것이므로 왼쪽자식의 크기+1(자신)을 반환
    else if (node_key == key) {
        int sub_rank = GetSize(node->get_left_child()) + 1;
        return sub_rank;
    }
    //기준 키가 더 작다면 왼쪽으로 더 내려가 탐색해야 함
    else {
        return GetRank(node->get_left_child(), key);
    }
}

//실질적인 삽입을 수행한 뒤, 서브 트리의 루트 노드를 반환한다.
Node* AVLTree::Insert(Node* node, int key) {
    //본인의 자리를 찾은 경우 -> 새 노드를 할당하여 반환
    if (node == NULL) {
        return new Node(key);
    }
    //본인의 자리를 찾지 못한 경우 -> 재귀적으로 내려가며 삽입 위치 탐색
    (node->get_key() < key) ?
        node->set_right_child(Insert(node->get_right_child(), key)) :
        node->set_left_child(Insert(node->get_left_child(), key));

    //본인의 하위에 새로운 자식 노드가 추가되었으므로 높이, 크기 재계산
    node->set_height(CalculateHeight(node));
    node->set_sub_size(CalculateSubSize(node));

    //재구조화 진행
    return Restruct(node);

}

//실질적인 삭제를 수행한 뒤, 서브 트리의 루트 노드를 반환한다.
Node* AVLTree::DeleteNode(Node* root, int key) {
    if (root == NULL) return root;

    // 삭제할 키를 찾음
    if (key < root->get_key()) {
        root->set_left_child(DeleteNode(root->get_left_child(), key));
    }
    else if (key > root->get_key()) {
        root->set_right_child(DeleteNode(root->get_right_child(), key));
    }
    else {
        // key == root->get_key()로 삭제할 노드를 찾은 것이니 삭제 수행
        if ((root->get_left_child() == NULL) || (root->get_right_child() == NULL)) {
            Node* temp = root->get_left_child() ? root->get_left_child() : root->get_right_child();

            // 자식 노드가 없는 경우 직접 삭제
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                // 한 개의 자식을 가진 경우 자식 노드를 삭제할 노드의 위치로 이동시킴
                *root = *temp;
            }
            delete temp;
        }
        else {
            // 두 개의 자식을 가진 경우 후임자를 이용하여 삭제 수행
            Node* temp = MinValueNode(root->get_right_child());
            root->set_key(temp->get_key());
            root->set_right_child(DeleteNode(root->get_right_child(), temp->get_key()));
        }
    }

    // 트리가 비어있는 경우
    if (root == NULL) return root;

    //본인의 하위에 있던 자식 노드가 삭제되었으므로 높이, 크기 재계산
    root->set_height(CalculateHeight(root));
    root->set_sub_size(CalculateSubSize(root));

    // 균형 재조정
    return Restruct(root);
}


// 주어진 노드의 서브트리에서 가장 작은 값을 가진 노드를 찾아 반환한다.
Node* AVLTree::MinValueNode(Node* node) {
    Node* current = node;
    while (current->get_left_child() != NULL) {
        current = current->get_left_child();
    }
    return current;
}

//주어진 노드가 불균형한 경우 적절히 회전하여 균형을 맞춘 뒤, 서브 트리의 루트 노드를 반환한다.
Node* AVLTree::Restruct(Node* node) {
    switch (IsUnbalance(node)) { //균형 여부 판단은 isUnbalance에서 수행하여 반환
        //균형 -> 0번의 회전 필요
    case BALANCE: {
        return node;
    }

                //불균형1 -> 1번의 회전 필요(single rotate)
    case LEFT_LEFT: {
        return RightRotate(node);
    }
    case RIGHT_RIGHT: {
        return LeftRotate(node);
    }

                    //불균형2 -> 2번의 회전 필요(double rotate)
    case LEFT_RIGHT: {
        Node* child_node = node->get_left_child();
        node->set_left_child(LeftRotate(child_node)); //yNode에 대해 left rotate 수행
        return RightRotate(node); //zNode에 대해 right rotate 수행
    }
    case RIGHT_LEFT: {
        Node* child_node = node->get_right_child();
        node->set_right_child(RightRotate(child_node)); //yNode에 대해 right rotate 수행
        return LeftRotate(node); //zNode에 대해 left rotate 수행
    }
    }
    return node;
}

//문제가 된 노드를 인수로 받아 오른쪽 회전한 뒤, 그 결과(sub tree) 새롭게 루트가 된 노드를 반환한다.
Node* AVLTree::RightRotate(Node* zNode) {
    Node* yNode = zNode->get_left_child(); //회전 결과 sub root가 될 노드
    Node* tNode = yNode->get_right_child();

    //회전 수행
    yNode->set_right_child(zNode); //yNode의 right child를 tNode에서 zNode로 바꾼다.
    zNode->set_left_child(tNode); //zNode의 left child를 yNode에서 yNode의 기존 right child(=tNode)로 바꾼다.

    //회전하면서 위치가 달라졌으므로 높이 재계산
    zNode->set_height(CalculateHeight(zNode));
    yNode->set_height(CalculateHeight(yNode));


    //회전하면서 크기가 달라졌으므로 크기 재계산
    zNode->set_sub_size(CalculateSubSize(zNode));
    yNode->set_sub_size(CalculateSubSize(yNode));

    return yNode;
}

//문제가 된 노드를 인수로 받아 왼쪽 회전한 뒤, 그 결과(sub tree) 새롭게 루트가 된 노드를 반환한다.
Node* AVLTree::LeftRotate(Node* zNode) {
    Node* yNode = zNode->get_right_child(); //회전 결과 sub root가 될 노드
    Node* tNode = yNode->get_left_child();

    //회전 수행
    yNode->set_left_child(zNode); //yNode의 left child를 tNode에서 zNode로 바꾼다.
    zNode->set_right_child(tNode); //zNode의 right child를 yNode에서 yNode의 기존 left child(=tNode)로 바꾼다.

    //회전하면서 위치가 달라졌으므로 높이 재계산
    zNode->set_height(CalculateHeight(zNode));
    yNode->set_height(CalculateHeight(yNode));

    //회전하면서 크기가 달라졌으므로 크기 재계산
    zNode->set_sub_size(CalculateSubSize(zNode));
    yNode->set_sub_size(CalculateSubSize(yNode));

    return yNode;
}