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

#pragma once
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>

enum UNBALANCE_CASE {
    BALANCE = 0,
    LEFT_LEFT = 1,
    RIGHT_RIGHT = 2,
    LEFT_RIGHT = 3,
    RIGHT_LEFT = 4
};

// Minimum, Maximum 테스트를 위해 추가
struct KeyDepthPair {
    int key;
    int depth;
};

// Rank 테스트를 위해 추가
struct DepthRankPair {
    int depth;
    int rank;
};


class Node {
public:
    Node(int key);
    ~Node();

    int get_key();
    int get_height();
    int get_sub_size();
    Node* get_left_child();
    Node* get_right_child();

    void set_key(int key);
    void set_height(int height);
    void set_left_child(Node* left_child);
    void set_right_child(Node* right_child);
    void set_sub_size(int sub_size);

private:
    int key_;
    int height_;
    int sub_size_;
    Node* left_child_;
    Node* right_child_;
};

// AVLTree 클래스 정의
class AVLTree {
public:
    AVLTree();
    Node* get_root();

    void set_root(Node* root);
    
    bool Empty();
    int Size();
    //void Empty();
    //void Size();
    KeyDepthPair Minimum(int x);
    KeyDepthPair Maximum(int x);
    //void Minimum(int x);
    //void Maximum(int x);
    int Find(int x);
    //void Find(int x);
    void Insert(int x);
    DepthRankPair Rank(int x);
    //void Rank(int x);
    void Erase(int x);

private:
    Node* root_;

    Node* GetNode(int key);
    int GetDepth(Node* node);
    int GetHeight(Node* node);
    int GetSize(Node* node);
    int GetRank(Node* node, int x);
    int IsUnbalance(Node* node);
    int CalculateBalanceFactor(Node* node);
    int CalculateHeight(Node* node);
    int CalculateSubSize(Node* node);
    Node* Insert(Node* node, int key);
    Node* DeleteNode(Node* node, int key);
    Node* MinValueNode(Node* node);
    Node* Restruct(Node* node);
    Node* RightRotate(Node* node);
    Node* LeftRotate(Node* node);
};

#endif // AVL_TREE_H