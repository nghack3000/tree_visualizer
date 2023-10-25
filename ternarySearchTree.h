
#pragma once

#pragma once

#include<iostream>
#include<thread>
#include<chrono>
#include<queue>
#include<SDL.h>
#include<SDL_ttf.h>
#include<Windows.h>
#include<conio.h>

#include "ternaryNode.h"
#include "ternaryTreeVisualizer.h"


using namespace std;

class ternarySearchTree
{
	ternaryNode* root;
public:
	ternarySearchTree() : root(NULL) {
		int Set[] = { 10,10,10,10,10,10 };
		int counter = 1;
		char key;
		int i = 0;
		while (1) {
			system("cls");

			color(10);
			cout << "\n\n\t\t\t\t[ TERNARY SEARCH TREE MENU ]" << endl;
			cout << "\t\t\t----------------------------------------" << endl;

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
			cout << "5. 2D TERNARY SEARCH TREE" << endl;

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
					cout << "\n\n\t\t\tEXITING TERNARY SEARCH TREE.." << endl;
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

						cout << "Ternary Node " << i + 1 << ": ";
						cin >> a;


						root = insertTST(root, a);

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
					if (searchTST(root, a))
					{
						root = deleteTST(root, a);
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

					if (!searchTST(root, a))
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
					inOrder(root);
					cout << endl;

					cout << "\n\n";
					cout << "Pre-Order Traversal :";
					preOrder(root);
					cout << endl;

					cout << "\n\n";
					cout << "Post-Order Traversal :";
					postOrder(root);
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

					visualizerTernary a1;
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

						SDL_Window* window = SDL_CreateWindow("Ternary Tree Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
						SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


						SDL_Event e;
						bool quit = false;

						int initialSpacing = SCREEN_WIDTH / 4;

						// Set the green line color
						SDL_Color lineColor = { 0, 255, 0, 255 };

						// Render the entire ternary tree with animations
						a1.renderTree(renderer, font, root, SCREEN_WIDTH / 2, 50, 0, initialSpacing, lineColor);


						// Wait for a delay after rendering
						SDL_Delay(ANIMATION_DELAY_MS * 2); // Adjust the delay as needed

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
					}

				}



			}
		}
	}

	ternaryNode* insertTST(ternaryNode* root, char value) {
		if (root == nullptr) {
			return new ternaryNode(value);
		}

		if (value < root->value) {
			root->left = insertTST(root->left, value);
		}
		else if (value == root->value) {
			root->middle = insertTST(root->middle, value);
		}
		else {
			root->right = insertTST(root->right, value);
		}

		return root;
	}

	ternaryNode* deleteTST(ternaryNode* root, char key) {
		if (root == nullptr) {
			return nullptr;
		}

		if (key < root->value) {
			root->left = deleteTST(root->left, key);
		}
		else if (key > root->value) {
			root->right = deleteTST(root->right, key);
		}
		else {
			if (root->middle) {
				root->middle = deleteTST(root->middle, key);
			}
			else if (root->left && root->right) {
				ternaryNode* minNode = findMin(root->right);
				root->value = minNode->value;
				root->right = deleteTST(root->right, minNode->value);
			}
			else {
				ternaryNode* temp = root;
				if (root->left) {
					root = root->left;
				}
				else {
					root = root->right;
				}
				delete temp;
			}
		}

		return root;
	}

	// Function to find the minimum value node in a TST
	ternaryNode* findMin(ternaryNode* node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	bool searchTST(ternaryNode* root, char key) {
		if (root == nullptr) {
			return false;
		}

		if (key == root->value) {
			return true;
		}
		else if (key < root->value) {
			return searchTST(root->left, key);
		}
		else if (key > root->value) {
			return searchTST(root->right, key);
		}
		else {
			return searchTST(root->middle, key);
		}
	}

	void inOrder(ternaryNode* node) {
		if (node == nullptr) {
			return;
		}

		inOrder(node->left);
		cout << node->value << " ";
		inOrder(node->middle);
		inOrder(node->right);
	}

	void preOrder(ternaryNode* node) {
		if (node == nullptr) {
			return;
		}

		cout << node->value << " ";
		preOrder(node->left);
		preOrder(node->middle);
		preOrder(node->right);
	}

	void postOrder(ternaryNode* node) {
		if (node == nullptr) {
			return;
		}

		postOrder(node->left);
		postOrder(node->middle);
		postOrder(node->right);
		cout << node->value << " ";
	}


};