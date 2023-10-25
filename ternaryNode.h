#pragma once
#include<iostream>
using namespace std;

class ternaryNode {
public:
	int value;
	ternaryNode* left;
	ternaryNode* middle;
	ternaryNode* right;

	ternaryNode(int data) : value(data), left(NULL), right(NULL), middle(NULL) {};
};