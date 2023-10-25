#pragma once
#include <iostream>

using namespace std;

class AVLNode {
public:
    int data;
    int height;
    int count;
    int balanceFactor;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int value) : data(value), height(1), count(1),balanceFactor(0), left(nullptr), right(nullptr) {}
};