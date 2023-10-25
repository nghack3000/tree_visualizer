#pragma once
#include<iostream>
#include<algorithm>
#include<thread>
#include<chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include <queue>
#include<Windows.h>
#include<conio.h>

#include "redYellowNode.h"
#include "redYellowVisualizer.h"

using namespace std;

class redYellowTree {
	RYNode* root;
	RYNode* TNULL;

	// Preorder
	void preOrderHelper(RYNode* node) {
		if (node != TNULL) {
			std::cout << node->data << " ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		}
	}

	// Inorder
	void inOrderHelper(RYNode* node) {
		if (node != TNULL) {
			inOrderHelper(node->left);
			std::cout << node->data << " ";
			
			inOrderHelper(node->right);
		}
	}

	// Post order
	void postOrderHelper(RYNode* node) {
		if (node != TNULL) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			std::cout << node->data << " ";
		}
	}

	// Left Rotate
	void leftRotate(RYNode* x) {
		RYNode* y = x->right;
		x->right = y->left;
		if (y->left != TNULL) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// Right Rotate
	void rightRotate(RYNode* y) {
		RYNode* x = y->left;
		y->left = x->right;
		if (x->right != TNULL) {
			x->right->parent = y;
		}
		x->parent = y->parent;
		if (y->parent == nullptr) {
			this->root = x;
		}
		else if (y == y->parent->right) {
			y->parent->right = x;
		}
		else {
			y->parent->left = x;
		}
		x->right = y;
		y->parent = x;
	}



	// Balance the tree after insertion
	void fixInsert(RYNode* k) {
		RYNode* u;
		while (k->parent != nullptr && k->parent->color == Color::RED) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // Uncle
				if (u->color == Color::RED) {
					u->color = Color::YELLOW;
					k->parent->color = Color::YELLOW;
					k->parent->parent->color = Color::RED;
					k = k->parent->parent;
				}
				else {
					if (k->parent == k->parent->parent->left && k == k->parent->left) {
						Color temp = k->parent->parent->color;
						k->parent->parent->color = k->parent->color;
						k->parent->color = temp;
						rightRotate(k->parent->parent);
					}
					else if (k->parent == k->parent->parent->right && k == k->parent->right)
					{
						Color temp = k->parent->parent->color;
						k->parent->parent->color = k->parent->color;
						k->parent->color = temp;
						leftRotate(k->parent->parent);
					}
					else if (k->parent == k->parent->parent->left && k == k->parent->right)
					{
						Color temp = k->parent->parent->color;
						k->parent->parent->color = k->color;
						k->color = temp;
						leftRotate(k->parent);
						rightRotate(k->parent);
					}
					else
					{
						Color temp = k->parent->parent->color;
						k->parent->parent->color = k->color;
						k->color = temp;
						rightRotate(k->parent);
						leftRotate(k->parent);
					}
				}
			}
			else {
				u = k->parent->parent->right; // Uncle

				if (u->color == Color::RED) {
					u->color = Color::YELLOW;
					k->parent->color = Color::YELLOW;
					k->parent->parent->color = Color::RED;
					k = k->parent->parent; // Move to the grandparent
				}
				else {
					if (k == k->parent->right) {
						k = k->parent;
						leftRotate(k);
					}
					k->parent->color = Color::YELLOW;
					k->parent->parent->color = Color::RED;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) {
				break;
			}
		}
		root->color = Color::YELLOW;
	}

	void rbTransplant(RYNode* u, RYNode* v) {
		if (u->parent == nullptr) {
			root = v;
		}
		else if (u == u->parent->left) {
			u->parent->left = v;
		}
		else {
			u->parent->right = v;
		}
		v->parent = u->parent;
	}

	// Delete a node from the tree
	void fixDelete(RYNode* x) {
		RYNode* s;
		while (x != root && x->color == Color::YELLOW) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == Color::RED) {
					s->color = Color::YELLOW;
					x->parent->color = Color::RED;
					leftRotate(x->parent);
					s = x->parent->right;
				}

				if (s->left->color == Color::YELLOW && s->right->color == Color::YELLOW) {
					s->color = Color::RED;
					x = x->parent;
				}
				else {
					if (s->right->color == Color::YELLOW) {
						s->left->color = Color::YELLOW;
						s->color = Color::RED;
						rightRotate(s);
						s = x->parent->right;
					}
					s->color = x->parent->color;
					x->parent->color = Color::YELLOW;
					s->right->color = Color::YELLOW;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == Color::RED) {
					s->color = Color::YELLOW;
					x->parent->color = Color::RED;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == Color::YELLOW && s->left->color == Color::YELLOW) {
					s->color = Color::RED;
					x = x->parent;
				}
				else {
					if (s->left->color == Color::YELLOW) {
						s->right->color = Color::YELLOW;
						s->color = Color::RED;
						leftRotate(s);
						s = x->parent->left;
					}
					s->color = x->parent->color;
					x->parent->color = Color::YELLOW;
					s->left->color = Color::YELLOW;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = Color::YELLOW;
	}

	RYNode* searchTreeHelper(RYNode* node, int key) {
		if (node == TNULL || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		}

		return searchTreeHelper(node->right, key);
	}


	// Balance the tree after a node deletion
	void deleteNodeHelper(RYNode* node, int key) {
		RYNode* z = TNULL;
		RYNode* x;
		RYNode* y;
		while (node != TNULL) {
			if (node->data == key) {
				z = node;
			}

			if (node->data <= key) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (z == TNULL) {
			std::cout << "Couldn't find key in the tree" << std::endl;
			return;
		}

		y = z;
		Color yOriginalColor = y->color;
		if (z->left == TNULL) {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else {
			y = minimum(z->right);
			yOriginalColor = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (yOriginalColor == Color::YELLOW) {
			fixDelete(x);
		}
	}

	// Find the minimum node in the tree
	RYNode* minimum(RYNode* node) {
		while (node->left != TNULL) {
			node = node->left;
		}
		return node;
	}

	// Find the maximum node in the tree
	RYNode* maximum(RYNode* node) {
		while (node->right != TNULL) {
			node = node->right;
		}
		return node;
	}

	// Find the successor of a given node
	RYNode* successor(RYNode* x) {
		if (x->right != TNULL) {
			return minimum(x->right);
		}

		RYNode* y = x->parent;
		while (y != TNULL && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// Find the predecessor of a given node
	RYNode* predecessor(RYNode* x) {
		if (x->left != TNULL) {
			return maximum(x->left);
		}

		RYNode* y = x->parent;
		while (y != TNULL && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}



public:
	redYellowTree() :root(NULL), TNULL(new RYNode()) {
		int Set[] = { 10,10,10,10,10,10 };
		int counter = 1;
		char key;
		int i = 0;
		while (1) {
			system("cls");

			color(10);
			cout << "\n\n\t\t\t\t[ RED YELLOW TREE MENU ]" << endl;
			cout << "\t\t\t-------------------------------------" << endl;

			gotoxy(7, 8);
			color(Set[0]);
			cout << "1. INSERTION" << endl;

			gotoxy(7, 9);
			color(Set[1]);
			cout << "2. DELETION" << endl;

			gotoxy(7, 10);
			color(Set[2]);
			cout << "3. SEARCHING" << endl;

			gotoxy(7, 11);
			color(Set[3]);
			cout << "4. TRAVERSAL" << endl;

			gotoxy(7, 12);
			color(Set[4]);
			cout << "5. 2D RED YELLOW TREE" << endl;

			gotoxy(7, 13);
			color(Set[5]);
			cout << "0. RETURN TO THE PREVIOUS MENU" << endl;

			key = _getch();

			if (key == 72 && (counter > 1 && counter <= 6)) {
				counter--;
				i--;
			}

			if (key == 80 && (counter >= 1 && counter < 6)) {
				counter++;
				i++;
			}

			for (int j = 0; j < 6; j++) {
				Set[j] = 10;
			}

			Set[i] = 12;

			if (key == '\r')
			{
				if (counter == 6)
				{
					system("cls");
					cout << "\n\n\t\t\tEXITING RED YELLOW TREE.." << endl;
					this_thread::sleep_for(std::chrono::seconds(1));

					break;
				}

				if (counter == 1)
				{
					system("cls");

					cout << "\n\n\t\t\t\t[ DATA INSERTION ]" << endl;
					cout << "\t\t\t--------------------------------" << endl;
					int no;
					cout << "How many nodes to be inserted?" << endl;
					cout << "N = ";
					cin >> no;

					cout << "Enter the data to be inserted." << endl;
					for (int i = 0; i < no; i++)
					{
						int a;

						cout << "Node " << i + 1 << ": ";
						cin >> a;


						insert(a);

						if (!root)
						{
							cout << "Data couldn't be inserted :(" << endl;
						}
						cout << endl;
					}
					cout << "Returning to the menu..." << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
				}

				if (counter == 2)
				{
					system("cls");

					cout << "\n\n\t\t\t\t[ DATA DELETION ]" << endl;
					cout << "\t\t\t--------------------------------" << endl;
					int a;
					cout << "Enter the data to be deleted: ";
					cin >> a;
					if (searchTree(a))
					{
						deleteNode(a);
						cout << "\n\n";
						cout << "Data " << a << " is deleted from binary tree" << endl;
					}
					else
					{
						cout << "\n\n";
						cout << "Data couldn't be found to be deleted" << endl;
						cout << "Please enter valid data" << endl;
					}
					cout << "Returning to the menu..." << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
					continue;

				}

				if (counter == 3)
				{
					system("cls");

					cout << "\n\n\t\t\t\t[ DATA SEARCHING ]" << endl;
					cout << "\t\t\t----------------------------------" << endl;
					int a;
					cout << "Enter the data to be searched: ";
					cin >> a;

					if (!searchTree(a))
					{
						cout << "\n\n";
						cout << "Data couldn't be found in the binary tree " << endl;
					}
					else
					{
						cout << "\n\n";

						cout << "Data " << a << " present in the binary tree" << endl;
					}
					cout << "Returning to the menu..." << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
				}

				if (counter == 4)
				{
					system("cls");
					cout << "\n\n\t\t\t\t[ DATA TRAVERSAL ]" << endl;
					cout << "\t\t\t--------------------------------" << endl;
					cout << "\n\n";
					cout << "In-Order Traversal : ";
					printInorder();
					cout << endl;

					cout << "\n\n";
					cout << "Pre-Order Traversal :";
					printPreorder();
					cout << endl;

					cout << "\n\n";
					cout << "Post-Order Traversal :";
					printPostorder();
					cout << endl;
					this_thread::sleep_for(std::chrono::seconds(2));
					cout << "Returning to the menu..." << endl;
					this_thread::sleep_for(std::chrono::seconds(3));
				}

				if (counter == 5)
				{
					system("cls");
					color(10);
					cout << "\n\n\t\t\t\t[ DATA VISUALIZER ]" << endl;
					cout << "\t\t\t----------------------------------" << endl;
					RYVisualizer a4;
					SDL_Init(SDL_INIT_VIDEO);
					TTF_Init();
					TTF_Font* font = TTF_OpenFont("arial.ttf", 20); // Use the path to your TTF font file

					if (!font) {
						std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
						continue;

					}

					if (!root)
					{
						cout << "\n\n\t\t\tOOPSIE! KINDLY ENTER THE DATA FIRST :)" << endl;
						this_thread::sleep_for(std::chrono::seconds(2));
						continue;


					}
					else
					{
						cout << "\n\n\t\t\tENTERING GRAPHICS MODE..." << endl;
						this_thread::sleep_for(std::chrono::seconds(1));
					}

					SDL_Window* window = SDL_CreateWindow("RED YELLOW Tree Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
					SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);






					SDL_Event e;
					bool quit = false;

					// Define the initial horizontal spacing for the root level
					int initialSpacing = SCREEN_WIDTH / 4;

					// Set the green line color
					SDL_Color lineColor = { 0, 255, 0, 255 };

					// Render the entire ternary tree with animations
					a4.renderRYT(renderer, font, this->root, SCREEN_WIDTH / 2, 50,0, initialSpacing, lineColor);


					while (!quit) {
						while (SDL_PollEvent(&e)) {
							if (e.type == SDL_QUIT) {

								quit = true;
							}
						}
					}

					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					TTF_CloseFont(font);
					TTF_Quit();
					SDL_Quit();
					cout << "\n\n\t\t\tEXITING GRAPHICS MODE.." << endl;

					this_thread::sleep_for(std::chrono::seconds(1));


				}



			}
		}

	}


	// Inorder
	void inOrder() {
		inOrderHelper(this->root);
	}

	// Post order
	void postOrder() {
		postOrderHelper(this->root);
	}

	// Search the tree for a given key
	RYNode* searchTree(int k) {
		return searchTreeHelper(this->root, k);
	}

	// Balance the tree after insertion of a node
	void insert(int key) {
		RYNode* node = new RYNode(key);
		node->parent = nullptr;
		node->left = TNULL;
		node->right = TNULL;
		node->color = Color::RED; // New node is always red

		RYNode* y = nullptr;
		RYNode* x = this->root;

		while (x != TNULL && x!=nullptr) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent == nullptr) {
			node->color = Color::YELLOW;
			return;
		}

		if (node->parent->parent == nullptr) {
			return;
		}

		fixInsert(node);
	}

	// Delete a node from the tree
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	// Preorder
	void printPreorder() {
		preOrderHelper(this->root);
	}

	// Inorder
	void printInorder() {
		inOrderHelper(this->root);
	}

	// Post order
	void printPostorder() {
		postOrderHelper(this->root);
	}
	
	

};