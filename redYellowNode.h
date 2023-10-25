#pragma once
#include <iostream>

using namespace std;

enum class Color { RED, YELLOW };

class RYNode {
public:
    int data;
    RYNode* parent;
    RYNode* left;
    RYNode* right;
    Color color;

    RYNode(int value) : data(value), parent(NULL),color(Color::YELLOW), left(NULL), right(NULL) {};
    RYNode() :parent(NULL),color(Color::YELLOW), left(NULL), right(NULL) {};
};