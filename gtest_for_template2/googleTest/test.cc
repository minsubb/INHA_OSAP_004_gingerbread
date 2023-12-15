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
#include "../gtest/AVLTree.h"
#include <gtest/gtest.h>

// Node 생성자 테스트
TEST(NodeTest, Constructor) {
    Node<int> node(10);

    EXPECT_EQ(node.get_key(), 10);
    EXPECT_EQ(node.get_height(), 0);
    EXPECT_EQ(node.get_sub_size(), 1);
    EXPECT_EQ(node.get_left_child(), nullptr);
    EXPECT_EQ(node.get_right_child(), nullptr);
}

// AVLTree 생성자 테스트
TEST(AVLTreeTest, Constructor) {
    AVLTree<int> avlTree;

    EXPECT_EQ(avlTree.get_root(), nullptr);
}

// Empty 함수 테스트
TEST(AVLTreeTest, Empty) {
    AVLTree<int> avlTree;

    EXPECT_TRUE(avlTree.Empty());

    avlTree.Insert(10);
    EXPECT_FALSE(avlTree.Empty());

    avlTree.Erase(10);
    EXPECT_TRUE(avlTree.Empty());
}

// Size 함수 테스트
TEST(AVLTreeTest, Size) {
    AVLTree<int> avlTree;

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

// Insert 함수 테스트
TEST(AVLTreeTest, Insert) {
    AVLTree<int> avlTree;

    avlTree.Insert(10);
    EXPECT_NE(avlTree.get_root(), nullptr);
    EXPECT_EQ(avlTree.get_root()->get_key(), 10);

    avlTree.Insert(20);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 20);

    avlTree.Insert(5);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 5);
}

TEST(AVLTreeTest, Insert_ascending) {
    AVLTree<int> avlTree;

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

TEST(AVLTreeTest, Insert_descending) {
    AVLTree<int> avlTree;

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
    AVLTree<int> avlTree;

    for (int i = 1; i <= 5; ++i) {
        avlTree.Insert(i);
    }

    EXPECT_EQ(avlTree.Size(), 5);

    EXPECT_EQ(avlTree.get_root()->get_key(), 2);

    Node<int>* leftChild = avlTree.get_root()->get_left_child();
    EXPECT_NE(leftChild, nullptr);
    EXPECT_EQ(leftChild->get_key(), 1);


    Node<int>* rightChild = avlTree.get_root()->get_right_child();
    EXPECT_NE(rightChild, nullptr);
    EXPECT_EQ(rightChild->get_key(), 4);


    EXPECT_EQ(rightChild->get_left_child()->get_key(), 3);
    EXPECT_EQ(rightChild->get_right_child()->get_key(), 5);
}


// 내림차순 삽입2
TEST(AVLTreeTest, Insert_descending2) {
    AVLTree<int> avlTree;

    for (int i = 5; i >= 1; i--) {
        avlTree.Insert(i);
    }

    EXPECT_EQ(avlTree.Size(), 5);

    EXPECT_EQ(avlTree.get_root()->get_key(), 4);

    Node<int>* leftChild = avlTree.get_root()->get_left_child();
    EXPECT_NE(leftChild, nullptr);
    EXPECT_EQ(leftChild->get_key(), 2);


    Node<int>* rightChild = avlTree.get_root()->get_right_child();
    EXPECT_NE(rightChild, nullptr);
    EXPECT_EQ(rightChild->get_key(), 5);


    EXPECT_EQ(leftChild->get_left_child()->get_key(), 1);
    EXPECT_EQ(leftChild->get_right_child()->get_key(), 3);
}

// Find 함수 테스트
TEST(AVLTreeTest, Find) {
    AVLTree<int> avlTree;
    avlTree.Insert(10);
    avlTree.Insert(20);
    avlTree.Insert(5);

    EXPECT_EQ(avlTree.Find(10), 0);
    EXPECT_EQ(avlTree.Find(20), 1);
    EXPECT_EQ(avlTree.Find(5), 1);
    EXPECT_EQ(avlTree.Find(15), -1);
}

// Find 테스트2. Restruct도 여기서 확인 가능
TEST(AVLTreeTest, Find2) {
    AVLTree<int> avlTree;
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
    AVLTree<int> avlTree;
    avlTree.Insert(20);
    avlTree.Insert(25);
    avlTree.Insert(30);

    EXPECT_EQ(avlTree.Find(25), 0);
    EXPECT_EQ(avlTree.Find(20), 1);
    EXPECT_EQ(avlTree.Find(30), 1);
    EXPECT_EQ(avlTree.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree.get_root()->get_right_child()->get_key(), 30);


    // Single Rotation, LL Rotation 테스트
    AVLTree<int> avlTree2;
    avlTree2.Insert(30);
    avlTree2.Insert(25);
    avlTree2.Insert(20);

    EXPECT_EQ(avlTree2.Find(25), 0);
    EXPECT_EQ(avlTree2.Find(20), 1);
    EXPECT_EQ(avlTree2.Find(30), 1);
    EXPECT_EQ(avlTree2.get_root()->get_left_child()->get_key(), 20);
    EXPECT_EQ(avlTree2.get_root()->get_right_child()->get_key(), 30);


    // Double Rotation, LR Rotation 테스트
    AVLTree<int> avlTree3;
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


// Erase 테스트
TEST(AVLTreeTest, SimpleErase) {
    AVLTree<int> avlTree;

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
    AVLTree<int> avlTree;
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

    Node<int>* leftChild = avlTree.get_root()->get_left_child();
    Node<int>* rightChild = avlTree.get_root()->get_right_child();

    EXPECT_EQ(leftChild->get_key(), 5);
    EXPECT_EQ(leftChild->get_left_child()->get_key(), 1);
    EXPECT_EQ(leftChild->get_right_child()->get_key(), 7);

    EXPECT_EQ(rightChild->get_key(), 20);
    EXPECT_EQ(rightChild->get_left_child()->get_key(), 13);
}


// -------------------------------------------------------------------------------------------------------------- int형 테스트
