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

#include "pch.h"
#include "../gtest/AVLTree.cc"



// -------------------------------------------------------------------------------기본 TEST
/*
// Node 생성자 테스트
TEST(NodeTest, Constructor) {
    Node node(10);

    EXPECT_EQ(node.get_key(), 10);
    EXPECT_EQ(node.get_height(), 0);
    EXPECT_EQ(node.get_sub_size(), 1);
    EXPECT_EQ(node.get_left_child(), nullptr);
    EXPECT_EQ(node.get_right_child(), nullptr);
}


// AVLTree 생성자 테스트
TEST(AVLTreeTest, Constructor) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.Size(), 0);
    EXPECT_EQ(avlTree.get_root(), nullptr);
}


// Empty 테스트
TEST(AVLTreeTest, Empty) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.Empty(), true);

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Empty(), false);

    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Empty(), true);
}


// Size 테스트
TEST(AVLTreeTest, Size) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.Size(), 0);

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 1);

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);

    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Size(), 1);

    avlTree.Erase(20);
    EXPECT_EQ(avlTree.Size(), 0);
}
 

// AVLTree에 노드 오름차순 삽입 테스트
TEST(AVLTreeTest, Insert_ascending) {
    AVLTree avlTree;

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 1);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_EQ(avlTree.get_root()->get_key(), 10);

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 20);

    avlTree.Insert(30);
    EXPECT_EQ(avlTree.Size(), 3);


    EXPECT_EQ(avlTree.get_root()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);
}


// AVLTree에 노드 내림차순 삽입 테스트
TEST(AVLTreeTest, Insert_descending) {
    AVLTree avlTree;

    avlTree.Insert(30);
    EXPECT_EQ(avlTree.Size(), 1);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_EQ(avlTree.get_root()->get_key(), 30);

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 20);

    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 3);


    EXPECT_EQ(avlTree.get_root()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);
}


// 오름차순 삽입2
TEST(AVLTreeTest, Insert_ascending2) {
    AVLTree avlTree;

    for (int i = 1; i <= 5; ++i) {
        avlTree.Insert(i);
    }

    EXPECT_EQ(avlTree.Size(), 5);

    EXPECT_EQ(avlTree.get_root()->get_key(), 2);

    Node* leftChild = avlTree.get_root()->get_left_child();
    EXPECT_NE(leftChild, nullptr);
    EXPECT_EQ(leftChild->get_key(), 1);


    Node* rightChild = avlTree.get_root()->get_right_child();
    EXPECT_NE(rightChild, nullptr);
    EXPECT_EQ(rightChild->get_key(), 4);


    EXPECT_EQ(rightChild->get_left_child()->get_key(), 3);
    EXPECT_EQ(rightChild->get_right_child()->get_key(), 5);
}


// 내림차순 삽입2
TEST(AVLTreeTest, Insert_descending2) {
    AVLTree avlTree;

    for (int i = 5; i >= 1; i--) {
        avlTree.Insert(i);
    }

    EXPECT_EQ(avlTree.Size(), 5);

    EXPECT_EQ(avlTree.get_root()->get_key(), 4);

    Node* leftChild = avlTree.get_root()->get_left_child();
    EXPECT_NE(leftChild, nullptr);
    EXPECT_EQ(leftChild->get_key(), 2);


    Node* rightChild = avlTree.get_root()->get_right_child();
    EXPECT_NE(rightChild, nullptr);
    EXPECT_EQ(rightChild->get_key(), 5);


    EXPECT_EQ(leftChild->get_left_child()->get_key(), 1);
    EXPECT_EQ(leftChild->get_right_child()->get_key(), 3);
}


// Find 테스트. Restruct도 여기서 확인 가능
TEST(AVLTreeTest, Find) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);

    EXPECT_EQ(avlTree.Find(5), 2);
    EXPECT_EQ(avlTree.Find(7), 1);
    EXPECT_EQ(avlTree.Find(8), 0);
    EXPECT_EQ(avlTree.Find(9), 3);
    EXPECT_EQ(avlTree.Find(45), 2);
    EXPECT_EQ(avlTree.Find(58), 3);
    EXPECT_EQ(avlTree.Find(63), 1);
    EXPECT_EQ(avlTree.Find(77), 2);
    EXPECT_EQ(avlTree.Find(89), 3);

    EXPECT_EQ(avlTree.Find(15), -1);  // 노드 15는 존재하지 않으므로 -1 반환
}


// Restruct 테스트
TEST(AVLTreeTest, restruct) {
    // Single Rotation, RR Rotation 테스트
    AVLTree avlTree;
    avlTree.Insert(20);
    avlTree.Insert(25);
    avlTree.Insert(30);

    EXPECT_EQ(avlTree.Find(25), 0);
    EXPECT_EQ(avlTree.Find(20), 1);
    EXPECT_EQ(avlTree.Find(30), 1);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);


    // Single Rotation, LL Rotation 테스트
    AVLTree avlTree2;
    avlTree2.Insert(30);
    avlTree2.Insert(25);
    avlTree2.Insert(20);

    EXPECT_EQ(avlTree2.Find(25), 0);
    EXPECT_EQ(avlTree2.Find(20), 1);
    EXPECT_EQ(avlTree2.Find(30), 1);
    EXPECT_EQ(avlTree2.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree2.get_root()->get_right_child()->get_key(), 30);


    // Double Rotation, LR Rotation 테스트
    AVLTree avlTree3;
    avlTree3.Insert(30);
    avlTree3.Insert(20);
    avlTree3.Insert(25);

    EXPECT_EQ(avlTree2.Find(25), 0);
    EXPECT_EQ(avlTree2.Find(20), 1);
    EXPECT_EQ(avlTree2.Find(30), 1);
    EXPECT_EQ(avlTree2.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree2.get_root()->get_right_child()->get_key(), 30);


    // Double Rotation, RL Rotation 테스트
    avlTree2.Insert(20);
    avlTree2.Insert(30);
    avlTree2.Insert(25);

    EXPECT_EQ(avlTree2.Find(25), 0);
    EXPECT_EQ(avlTree2.Find(20), 1);
    EXPECT_EQ(avlTree2.Find(30), 1);
    EXPECT_EQ(avlTree2.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree2.get_root()->get_right_child()->get_key(), 30);
}


// Minimum 테스트
TEST(AVLTreeTest, Minimum) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);

    KeyDepthPair result = avlTree.Minimum(63);
    EXPECT_EQ(result.key, 9);
    EXPECT_EQ(result.depth, 3);

    result = avlTree.Minimum(8);
    EXPECT_EQ(result.key, 5);
    EXPECT_EQ(result.depth, 2);
}


// Maximum 테스트 
TEST(AVLTreeTest, Maximum) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);


    KeyDepthPair result = avlTree.Maximum(63);
    EXPECT_EQ(result.key, 89);
    EXPECT_EQ(result.depth, 3);

    result = avlTree.Maximum(45);
    EXPECT_EQ(result.key, 58);
    EXPECT_EQ(result.depth, 3);
}


// Rank 테스트
TEST(AVLTreeTest, Rank) {
    AVLTree avlTree;
    avlTree.Insert(7);
    avlTree.Insert(8);
    avlTree.Insert(9);
    avlTree.Insert(45);
    avlTree.Insert(5);
    avlTree.Insert(63);
    avlTree.Insert(58);
    avlTree.Insert(77);
    avlTree.Insert(89);


    DepthRankPair result = avlTree.Rank(8);
    EXPECT_EQ(result.depth, 0);
    EXPECT_EQ(result.rank, 3);


    result = avlTree.Rank(45);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 5);


    result = avlTree.Rank(9);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 4);


    result = avlTree.Rank(77);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 8);


    result = avlTree.Rank(58);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 6);


    result = avlTree.Rank(89);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 9);


    result = avlTree.Rank(101);
    EXPECT_EQ(result.depth, 0);
    EXPECT_EQ(result.rank, 0);
}


// Rank 테스트2
TEST(AVLTreeTest, Rank2) {
    AVLTree avlTree;
    avlTree.Insert(8);
    avlTree.Insert(3);
    avlTree.Insert(11);
    avlTree.Insert(2);
    avlTree.Insert(6);
    avlTree.Insert(9);
    avlTree.Insert(13);
    avlTree.Insert(1);
    avlTree.Insert(5);
    avlTree.Insert(7);
    avlTree.Insert(10);
    avlTree.Insert(12);
    avlTree.Insert(4);


    DepthRankPair result = avlTree.Rank(1);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 1);

    result = avlTree.Rank(2);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 2);

    result = avlTree.Rank(3);
    EXPECT_EQ(result.depth, 1);
    EXPECT_EQ(result.rank, 3);

    result = avlTree.Rank(4);
    EXPECT_EQ(result.depth, 4);
    EXPECT_EQ(result.rank, 4);

    result = avlTree.Rank(5);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 5);

    result = avlTree.Rank(6);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 6);

    result = avlTree.Rank(7);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 7);

    result = avlTree.Rank(8);
    EXPECT_EQ(result.depth, 0);
    EXPECT_EQ(result.rank, 8);

    result = avlTree.Rank(9);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 9);

    result = avlTree.Rank(10);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 10);

    result = avlTree.Rank(11);
    EXPECT_EQ(result.depth, 1);
    EXPECT_EQ(result.rank, 11);

    result = avlTree.Rank(12);
    EXPECT_EQ(result.depth, 3);
    EXPECT_EQ(result.rank, 12);

    result = avlTree.Rank(13);
    EXPECT_EQ(result.depth, 2);
    EXPECT_EQ(result.rank, 13);

    EXPECT_EQ(avlTree.Size(), 13);
}


// Erase 테스트
TEST(AVLTreeTest, SimpleErase) {
    AVLTree avlTree;

    avlTree.Insert(10);
    avlTree.Insert(5);
    avlTree.Insert(20);

    EXPECT_EQ(avlTree.Size(), 3);

    avlTree.Erase(10);

    EXPECT_EQ(avlTree.Size(), 2);

    EXPECT_EQ(avlTree.Find(10), -1);

    EXPECT_EQ(avlTree.Find(5), 1);
    EXPECT_EQ(avlTree.Find(20), 0);
}


// Erase 테스트3
TEST(AVLTreeTest, Erase2) {
    AVLTree avlTree;
    avlTree.Insert(10);
    avlTree.Insert(20);
    avlTree.Insert(5);
    avlTree.Insert(15);
    avlTree.Insert(25);
    avlTree.Insert(3);
    avlTree.Insert(7);
    avlTree.Insert(13);
    avlTree.Insert(17);
    avlTree.Insert(1);

    EXPECT_EQ(avlTree.Size(), 10);

    avlTree.Erase(25); // 자식 없는 노드 삭제 후 Restruct

    EXPECT_EQ(avlTree.Find(15), 1);
    EXPECT_EQ(avlTree.Find(13), 2);
    EXPECT_EQ(avlTree.Find(20), 2);
    EXPECT_EQ(avlTree.Find(17), 3);

    avlTree.Erase(17); // 자식 없는 노드 삭제 후 Restruct X

    EXPECT_EQ(avlTree.Find(15), 1);
    EXPECT_EQ(avlTree.Find(13), 2);
    EXPECT_EQ(avlTree.Find(20), 2);

    avlTree.Erase(15); // 자식 두 개인 노드 후임자를 통해 삭제

    EXPECT_EQ(avlTree.Find(13), 2);
    EXPECT_EQ(avlTree.Find(20), 1);

    avlTree.Erase(3); // 자식 하나인 노드 삭제

    EXPECT_EQ(avlTree.Size(), 6);

    EXPECT_EQ(avlTree.get_root()->get_key(), 10);

    Node* leftChild = avlTree.get_root()->get_left_child();
    Node* rightChild = avlTree.get_root()->get_right_child();

    EXPECT_EQ(leftChild->get_key(), 5);
    EXPECT_EQ(leftChild->get_left_child()->get_key(), 1);
    EXPECT_EQ(leftChild->get_right_child()->get_key(), 7);
    
    EXPECT_EQ(rightChild->get_key(), 20);
    EXPECT_EQ(rightChild->get_left_child()->get_key(), 13);

    KeyDepthPair minresult = avlTree.Minimum(10);
    EXPECT_EQ(minresult.key, 1);
    EXPECT_EQ(minresult.depth, 2);

    KeyDepthPair maxresult = avlTree.Maximum(5);
    EXPECT_EQ(maxresult.key, 7);
    EXPECT_EQ(maxresult.depth, 2);

    DepthRankPair result = avlTree.Rank(13);
    EXPECT_EQ(result.rank, 5);
    EXPECT_EQ(result.depth, 2);
}


*/




// -------------------------------------------------------------------------------Fixture TEST
/*
class AVLTreeTest :public ::testing::Test {
protected:
    AVLTree avlTree;

    void SetUp() override {
        avlTree.Insert(10);
        avlTree.Insert(20);
        avlTree.Insert(5);
    }

    void TearDown() override {

    }

};

// 기본 Size, Empty 테스트
TEST_F(AVLTreeTest, BasicTreeFunctions) {
    EXPECT_EQ(avlTree.Size(), 3);
    EXPECT_FALSE(avlTree.Empty());

    avlTree.Erase(15);
    EXPECT_EQ(avlTree.Size(), 3);
}

// Empty 테스트
TEST_F(AVLTreeTest, IsEmpty) {
    EXPECT_FALSE(avlTree.Empty());
}

// Size 테스트
TEST_F(AVLTreeTest, SizeTest) {
    EXPECT_EQ(avlTree.Size(), 3);
}

// Insert 테스트
TEST_F(AVLTreeTest, InsertTest) {
    avlTree.Insert(15);
    EXPECT_EQ(avlTree.Size(), 4);
}

// Erase 테스트
TEST_F(AVLTreeTest, EraseTest) {
    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Size(), 2);
}

// Insert, Erase 테스트
TEST_F(AVLTreeTest, NodeInsertAndDelete) {
    EXPECT_EQ(avlTree.Size(), 3);

    avlTree.Insert(15);
    EXPECT_EQ(avlTree.Size(), 4);

    avlTree.Erase(20);
    EXPECT_EQ(avlTree.Size(), 3);
    EXPECT_EQ(avlTree.Find(20), -1);
}

// Maximum, Minimum 테스트
TEST_F(AVLTreeTest, FindMinMax) {
    KeyDepthPair minResult = avlTree.Minimum(10);
    EXPECT_EQ(minResult.key, 5);
    EXPECT_EQ(minResult.depth, 1);

    KeyDepthPair maxResult = avlTree.Maximum(10);
    EXPECT_EQ(maxResult.key, 20);
    EXPECT_EQ(maxResult.depth, 1);
}

// Rank 테스트
TEST_F(AVLTreeTest, NodeRank) {
    DepthRankPair result = avlTree.Rank(10);
    EXPECT_EQ(result.rank, 2);
    EXPECT_EQ(result.depth, 0);
}

// Find 테스트
TEST_F(AVLTreeTest, FindNode) {
    EXPECT_EQ(avlTree.Find(10), 0);
    EXPECT_EQ(avlTree.Find(5), 1);
    EXPECT_EQ(avlTree.Find(15), -1);
}

// 노드 순회 테스트
TEST_F(AVLTreeTest, TreeTraversal) {
    EXPECT_EQ(avlTree.get_root()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 5);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 20);

    avlTree.Insert(30);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_right_child()->get_key(), 30);
}

// 노드 탐색 및 랭크 테스트
TEST_F(AVLTreeTest, SearchAndRank) {
    EXPECT_EQ(avlTree.Find(20), 1);
    EXPECT_EQ(avlTree.Find(100), -1);

    DepthRankPair rankResult = avlTree.Rank(15);
    EXPECT_EQ(rankResult.rank, 0);
    EXPECT_EQ(rankResult.depth, 0);
}

// 최대값 및 최소값 테스트
TEST_F(AVLTreeTest, FindMinMaxValues) {
    KeyDepthPair minResult = avlTree.Minimum(10);
    EXPECT_EQ(minResult.key, 5);
    EXPECT_EQ(minResult.depth, 1);

    KeyDepthPair maxResult = avlTree.Maximum(20);
    EXPECT_EQ(maxResult.key, 20);
    EXPECT_EQ(maxResult.depth, 1);
}

// 노드 삭제 테스트
TEST_F(AVLTreeTest, NodeDeletion) {
    avlTree.Erase(5);
    EXPECT_EQ(avlTree.Size(), 2);
    EXPECT_EQ(avlTree.get_root()->get_left_child(), nullptr);

    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Size(), 1);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_NE(avlTree.get_root()->get_key(), 10);

    avlTree.Erase(100);
    EXPECT_EQ(avlTree.Size(), 1);
}

// 노드 삭제 후 Minimum, Maximum, Rank 테스트
TEST_F(AVLTreeTest, EraseWithMinMaxRankTest) {
    avlTree.Insert(30);
    avlTree.Insert(40);
    avlTree.Insert(50);


    KeyDepthPair minBeforeErase = avlTree.Minimum(avlTree.get_root()->get_key());
    KeyDepthPair maxBeforeErase = avlTree.Maximum(avlTree.get_root()->get_key());
    EXPECT_EQ(minBeforeErase.key, 5);
    EXPECT_EQ(maxBeforeErase.key, 50);


    avlTree.Erase(5);
    avlTree.Erase(50);

    KeyDepthPair minAfterErase = avlTree.Minimum(avlTree.get_root()->get_key());
    KeyDepthPair maxAfterErase = avlTree.Maximum(avlTree.get_root()->get_key());
    EXPECT_EQ(minAfterErase.key, 10);
    EXPECT_EQ(maxAfterErase.key, 40);

    DepthRankPair rankTest = avlTree.Rank(30);
    EXPECT_EQ(rankTest.rank, 3);
}

// 다중 노드 삭제 후 트리 구조 검증 테스트
TEST_F(AVLTreeTest, MultipleNodeDeletionStructureTest) {
    avlTree.Insert(15);
    avlTree.Insert(22);
    avlTree.Insert(35);

    avlTree.Erase(5);
    avlTree.Erase(35);
    avlTree.Erase(22);

    EXPECT_EQ(avlTree.Size(), 3);
    EXPECT_EQ(avlTree.get_root()->get_key(), 15);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 20);
}

*/




// -------------------------------------------------------------------------------value-parameterized TEST
/*
class AVLTreeInsertTest : public ::testing::TestWithParam<int> {
protected:
    AVLTree avlTree;

    void SetUp() override {
        avlTree.Insert(10);
        avlTree.Insert(20);
        avlTree.Insert(30);
    }
};

// Size 테스트
TEST_F(AVLTreeInsertTest, TreeSize) {
    EXPECT_EQ(avlTree.Size(), 3);
}

// Empty 테스트
TEST_F(AVLTreeInsertTest, IsTreeEmpty) {
    EXPECT_FALSE(avlTree.Empty());
}

// Insert 테스트
TEST_P(AVLTreeInsertTest, NodeInsertion) {
    int nodeToInsert = GetParam();
    avlTree.Insert(nodeToInsert);

    int depth = avlTree.Find(nodeToInsert);
    ASSERT_NE(depth, -1);
}

// 특정 조건에 따른 삭제 테스트
TEST_P(AVLTreeInsertTest, NodeDeletion) {
    int nodeToDelete = GetParam();
    avlTree.Insert(nodeToDelete);
    avlTree.Erase(nodeToDelete);

    int depth = avlTree.Find(nodeToDelete);
    ASSERT_EQ(depth, -1);
}

// Find 테스트
TEST_P(AVLTreeInsertTest, FindNode) {
    int nodeToFind = GetParam();
    avlTree.Insert(nodeToFind);

    int depth = avlTree.Find(nodeToFind);
    EXPECT_NE(depth, -1);
}

// Rank 테스트
TEST_P(AVLTreeInsertTest, NodeRank) {
    int nodeToRank = GetParam();
    avlTree.Insert(nodeToRank);

    DepthRankPair rankResult = avlTree.Rank(nodeToRank);
    ASSERT_NE(rankResult.depth, 0);
    ASSERT_NE(rankResult.rank, 0);
}

// Minimum 테스트
TEST_P(AVLTreeInsertTest, FindMinimum) {
    int nodeToTest = GetParam();
    avlTree.Insert(nodeToTest);

    KeyDepthPair minResult = avlTree.Minimum(nodeToTest);
    ASSERT_EQ(minResult.key, nodeToTest);
    ASSERT_NE(minResult.depth, -1);
}

// Maximum 테스트
TEST_P(AVLTreeInsertTest, FindMaximum) {
    int nodeToTest = GetParam();
    avlTree.Insert(nodeToTest);

    KeyDepthPair maxResult = avlTree.Maximum(nodeToTest);
    ASSERT_EQ(maxResult.key, nodeToTest);
    ASSERT_NE(maxResult.depth, -1);
}

INSTANTIATE_TEST_CASE_P(Default, AVLTreeInsertTest, ::testing::Values(5, 15, 25, 35, 45));



*/
