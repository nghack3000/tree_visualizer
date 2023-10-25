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

#include "avlNode.h"
#include "binaryNode.h"
#include "avlTreeVisualizer.h"


using namespace std;

class AVL {
	AVLNode* root = NULL;
	Node* initial_root = NULL;
public:
	AVL(): root(NULL){
		int Set[] = { 10,10,10,10,10,10 };
		int counter = 1;
		char key;
		int i = 0;
		while (1) {
			system("cls");

			color(10);
			cout << "\n\n\t\t\t\t[ AVL TREE MENU ]" << endl;
			cout << "\t\t\t----------------------------------" << endl;

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
			cout << "5. 2D AVL TREE" << endl;

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
					cout << "\n\n\t\t\tEXITING AVL TREE.." << endl;
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


						root = insert(root, a);
						initial_root = insertBinary(initial_root, a);

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
					if (search(root, a))
					{
						root = deleteNode(root, a);
						initial_root = deleteBST(initial_root, a);
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

					if (!search(root, a))
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
					inOrderTraversal(root);
					cout << endl;

					cout << "\n\n";
					cout << "Pre-Order Traversal :";
					preOrderTraversal(root);
					cout << endl;

					cout << "\n\n";
					cout << "Post-Order Traversal :";
					postOrderTraversal(root);
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
					visualizerAVLBinary a3;
					SDL_Init(SDL_INIT_VIDEO);
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

					SDL_Window* window = SDL_CreateWindow("AVL TREE VISUALIZATION AND BST VISUALIZATION", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
					SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

					//SDL_Window* window2 = SDL_CreateWindow("BINARY SEARCH TREE VIUSALIZATION", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH/2, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
					//SDL_Renderer* renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED);






					SDL_Event e;
					bool quit = false;

					// Define the initial horizontal spacing for the root level
					int initialSpacing = SCREEN_WIDTH / 10;

					// Set the green line color
					SDL_Color lineColor = { 0, 255, 0, 255 };

					// Render the entire ternary tree with animations
					a3.renderTree(renderer, font, root, SCREEN_WIDTH / 4, 50, 1, initialSpacing, lineColor);
					a3.renderBinaryTree(renderer, font, initial_root, (SCREEN_WIDTH*3) / 4, 50, 1, initialSpacing, lineColor);


					while (!quit) {
						while (SDL_PollEvent(&e)) {
							if (e.type == SDL_QUIT) {

								quit = true;
							}
						}
					}
				


			

					SDL_DestroyRenderer(renderer);
					SDL_DestroyWindow(window);
					//SDL_DestroyRenderer(renderer2);
					//SDL_DestroyWindow(window2);
					
					TTF_CloseFont(font);
					TTF_Quit();
					SDL_Quit();
					
		
					
					cout << "\n\n\t\t\tEXITING GRAPHICS MODE.." << endl;

					this_thread::sleep_for(std::chrono::seconds(1));
					

				}



			}
		}

	}

	int getHeight(AVLNode* node) {
		if (node == nullptr)
			return 0;
		return node->height;
	}

	int getBalanceFactor(AVLNode* node) {
		if (node == nullptr)
			return 0;
		node->balanceFactor = getHeight(node->left) - getHeight(node->right);
			return node->balanceFactor;
	}

	void updateHeight(AVLNode* node) {
		node->height = 1 + max(getHeight(node->left), getHeight(node->right));
	}

	AVLNode* rotateRight(AVLNode* y) {
		AVLNode* x = y->left;
		AVLNode* T2 = x->right;

		x->right = y;
		y->left = T2;

		updateHeight(y);
		updateHeight(x);

		y->balanceFactor = getBalanceFactor(y);
		x->balanceFactor = getBalanceFactor(x);

		return x;
	}

	AVLNode* rotateLeft(AVLNode* x) {
		AVLNode* y = x->right;
		AVLNode* T2 = y->left;

		y->left = x;
		x->right = T2;

		updateHeight(x);
		updateHeight(y);

		x->balanceFactor = getBalanceFactor(x);
		y->balanceFactor = getBalanceFactor(y);

		return y;
	}

	Node* insertBinary(Node* root, int value) {
		if (!root) {
			root = new Node(value);
			return root;
		}

		if (root->value > value) {
			root->left = insertBinary(root->left, value);
		}
		else {
			root->right = insertBinary(root->right, value);
		}

		return root;
	}

	AVLNode* insert(AVLNode* root, int value) {
		if (root == nullptr) {
			root = new AVLNode(value);
			return root;
		}
		if (value < root->data) {
			root->left = insert(root->left, value);
		}
		else if (value > root->data) {
			root->right = insert(root->right, value);
		}
		else {
			root->count++; 
		}

		updateHeight(root);

		int balance = root->balanceFactor;
		balance = getBalanceFactor(root);

		if (balance > 1) {
			if (value < root->left->data) {
				return rotateRight(root);
			}
			else {
				root->left = rotateLeft(root->left);
				return rotateRight(root);
			}
		}

		if (balance < -1) {
			if (value > root->right->data) {
				return rotateLeft(root);
			}
			else {
				root->right = rotateRight(root->right);
				return rotateLeft(root);
			}

			return root;
		}

		return root;
	}

	AVLNode* findMinValueNode(AVLNode* node) {
		AVLNode* current = node;
		while (current->left != nullptr) {
			current = current->left;
		}
		return current;
	}


	AVLNode* deleteNode(AVLNode* root, int value) {
		if (root == nullptr) {
			return root;
		}

		if (value < root->data) {
			root->left = deleteNode(root->left, value);
		}
		else if (value > root->data) {
			root->right = deleteNode(root->right, value);
		}
		else {
			if (root->count > 1) {
				// Decrease the count for duplicate values
				root->count--;
			}
			else {
				// If count is 1 or less, perform the actual deletion
				if (root->left == nullptr || root->right == nullptr) {
					AVLNode* temp = (root->left) ? root->left : root->right;
					if (temp == nullptr) {
						temp = root;
						root = nullptr;
					}
					else {
						*root = *temp;
					}
					delete temp;
				}
				else {
					AVLNode* temp = findMinValueNode(root->right);
					root->data = temp->data;
					root->right = deleteNode(root->right, temp->data);
				}
			}
		}

		if (root == nullptr) {
			return root;
		}

		updateHeight(root);

		root->balanceFactor= getBalanceFactor(root);

		if (root->balanceFactor > 1) {
			if (getBalanceFactor(root->left) >= 0) {
				return rotateRight(root);
			}
			else {
				root->left = rotateLeft(root->left);
				return rotateRight(root);
			}
		}

		if (root->balanceFactor < -1) {
			if (getBalanceFactor(root->right) <= 0) {
				return rotateLeft(root);
			}
			else {
				root->right = rotateRight(root->right);
				return rotateLeft(root);
			}
		}

		return root;
	}
	Node* findMin(Node* node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	Node* deleteBST(Node* root, int a) {
		if (root == nullptr) {
			return root;
		}


		if (a < root->value) {
			root->left = deleteBST(root->left, a);
		}

		else if (a > root->value) {
			root->right = deleteBST(root->right, a);
		}

		else {

			if (root->left == nullptr) {
				Node* temp = root->right;
				delete root;
				return temp;
			}
			else if (root->right == nullptr) {
				Node* temp = root->left;
				delete root;
				return temp;
			}


			Node* temp = findMin(root->right);
			root->value = temp->value;


			root->right = deleteBST(root->right, temp->value);
		}
		return root;
	}

	AVLNode* search(AVLNode* root, int value) {
		if (root == nullptr || root->data == value) {
			return root;
		}

		if (value < root->data) {
			return search(root->left, value);
		}
		else {
			return search(root->right, value);
		}
	}

	void inOrderTraversal(AVLNode* root) {
		if (root == nullptr) {
			return;
		}

		inOrderTraversal(root->left);
		std::cout << root->data << " ";
		inOrderTraversal(root->right);
	}

	void preOrderTraversal(AVLNode* root) {
		if (root == nullptr) {
			return;
		}

		std::cout << root->data << " ";
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}

	void postOrderTraversal(AVLNode* root) {
		if (root == nullptr) {
			return;
		}

		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		std::cout << root->data << " ";
	}


};