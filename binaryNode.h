#pragma once
#include <iostream>

using namespace std;

class Node
{
public:
	int value;
	Node* left;
	Node* right;

	Node(int data) : value(data), left(nullptr), right(nullptr) {};
};