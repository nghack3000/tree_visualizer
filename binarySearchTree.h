#pragma once

#include<iostream>
#include<thread>
#include<chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include <queue>
#include<Windows.h>
#include<conio.h>

#include "binaryNode.h"
#include "binaryTreeVisualizer.h"
using namespace std;

class binarySearchTree {
	Node* root;

public:
	binarySearchTree() : root(NULL) {
		int Set[] = { 10,10,10,10,10,10 };
		int counter = 1;
		char key;
		int i = 0;

		while (1) {
			system("cls");

			color(10);
			cout << "\n\n\t\t\t\t[ BINARY SEARCH TREE MENU ]" << endl;
			cout << "\t\t\t---------------------------------------" << endl;

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
			cout << "5. 2D BINARY SEARCH TREE" << endl;

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
				if (counter == 1) {
					system("cls");

					cout << "\n\n\t\t\t\t[ DATA INSERTION ]" << endl;
					cout << "\t\t\t--------------------------------" << endl;

					int no;
					cout << "How many data do u want to insert?" << endl;
					cout << "N = ";
					cin >> no;

					cout << "Enter the data to be inserted: " << endl;
					for (int i = 0; i < no; i++)
					{

						cout << "Node " << i + 1 << ": ";
						int a;

						cin >> a;
						root = insertBST(root, a);
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
					if (searchBST(root, a))
					{
						root = deleteBST(root, a);
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
					Node* temp = searchBST(root, a);
					if (!temp)
					{
						cout << "\n\n";
						cout << "Data couldn't be found in the binary tree " << endl;
					}
					else
					{
						cout << "\n\n";

						cout << "Data " << temp->value << " present in the binary tree" << endl;
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
					cout << endl;

					cout << "Pre-Order Traversal : ";
					preOrderTraversal(root);
					cout << endl;
					cout << endl;

					cout << "Post-Order Traversal : ";
					postOrderTraversal(root);
					cout << endl;
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
					visualizerBinary a;
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

					SDL_Window* window = SDL_CreateWindow("Binary Search Tree Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
					SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);






					SDL_Event e;
					bool quit = false;

					// Define the initial horizontal spacing for the root level
					int initialSpacing = SCREEN_WIDTH / 4;

					// Set the green line color
					SDL_Color lineColor = { 0, 255, 0, 255 };

					// Render the entire ternary tree with animations
					a.renderTree(renderer, font, root, SCREEN_WIDTH / 2, 50, 0, initialSpacing, lineColor);

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


				if (counter == 6)
				{
					system("cls");

					cout << "\n\n\t\t\tEXITING BINARY SEARCH TREE..." << endl;
					this_thread::sleep_for(std::chrono::seconds(1));

					break;
				}
			}

		}
	}

	Node* insertBST(Node* root, int value) {
		if (root == nullptr) {
			return new Node(value);
		}

		if (value < root->value) {
			root->left = insertBST(root->left, value);
		}
		else if (value >= root->value) {
			root->right = insertBST(root->right, value);
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

	Node* searchBST(Node* root, int key) {

		if (root == nullptr || root->value == key) {
			return root;  
		}

		if (key > root->value) {
			return searchBST(root->right, key);
		}

		return searchBST(root->left, key);
	}

	// In-order traversal (left - root - right)
	void inOrderTraversal(Node* root) {
		if (root == nullptr) {
			return;
		}
		inOrderTraversal(root->left);
		std::cout << root->value << " ";
		inOrderTraversal(root->right);
	}

	// Pre-order traversal (root - left - right)
	void preOrderTraversal(Node* root) {
		if (root == nullptr) {
			return;
		}
		std::cout << root->value << " ";
		preOrderTraversal(root->left);
		preOrderTraversal(root->right);
	}

	// Post-order traversal (left - right - root)
	void postOrderTraversal(Node* root) {
		if (root == nullptr) {
			return;
		}
		postOrderTraversal(root->left);
		postOrderTraversal(root->right);
		std::cout << root->value << " ";
	}
};