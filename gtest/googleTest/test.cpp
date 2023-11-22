#include "pch.h"
#include "../gtest/AVLTree.cpp"

// Node 클래스의 생성자 테스트
TEST(NodeTest, Constructor) {
    Node node(10);

    EXPECT_EQ(node.get_key(), 10);
    EXPECT_EQ(node.get_height(), 1);
    EXPECT_EQ(node.get_left_child(), nullptr);
    EXPECT_EQ(node.get_right_child(), nullptr);
}

// AVLTree 클래스의 생성자 테스트
TEST(AVLTreeTest, Constructor) {
    AVLTree avlTree;

    EXPECT_EQ(avlTree.get_size(), 0);
    EXPECT_EQ(avlTree.get_root(), nullptr);
}

// AVLTree에 노드 삽입 테스트
TEST(AVLTreeTest, Insert) {
    AVLTree avlTree;

    // 첫 번째 삽입
    avlTree.Insert(10);
    EXPECT_EQ(avlTree.get_size(), 1);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_EQ(avlTree.get_root()->get_key(), 10);

    // 두 번째 삽입
    avlTree.Insert(20);
    EXPECT_EQ(avlTree.get_size(), 2);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 20);

    // 세 번째 삽입
    avlTree.Insert(30);
    EXPECT_EQ(avlTree.get_size(), 3);
    // 이 시점에서 AVL 트리는 균형을 재조정해야 함
    // 예상되는 구조: 20이 루트, 10과 30이 자식
    EXPECT_EQ(avlTree.get_root()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 10);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);
}

// AVLTree의 Empty 메소드 테스트
TEST(AVLTreeTest, Empty) {
    AVLTree avlTree;

    // 트리가 비어있는 경우
    EXPECT_EQ(avlTree.Empty(), true);

    // 트리에 노드 삽입
    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Empty(), false);

    // 트리에서 노드 삭제
    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Empty(), true);
}

// AVLTree의 Size 메소드 테스트
TEST(AVLTreeTest, Size) {
    AVLTree avlTree;

    // 초기 트리 크기 확인
    EXPECT_EQ(avlTree.Size(), 0);

    // 트리에 노드 삽입 후 크기 확인
    avlTree.Insert(10);
    EXPECT_EQ(avlTree.Size(), 1);

    // 또 다른 노드 삽입 후 크기 확인

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.Size(), 2);

    // 노드 삭제 후 크기 확인
    avlTree.Erase(10);
    EXPECT_EQ(avlTree.Size(), 1);

    // 나머지 노드 삭제 후 크기 확인
    avlTree.Erase(20);
    EXPECT_EQ(avlTree.Size(), 0);
}