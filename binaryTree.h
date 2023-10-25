#pragma once


#include<iostream>
#include<thread>
#include<chrono>
#include <SDL.h>
#include <SDL_ttf.h>
#include <queue>
#include<Windows.h>
#include<conio.h>

#include "binaryTreeVisualizer.h"
#include "binaryNode.h"

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
using namespace std;





class binaryTree
{
	Node* root;
public:
	//MAIN MENU OF BINARY TREE
	binaryTree() : root(NULL)
	{
		int Set[] = { 10,10,10,10,10,10 };
		int counter = 1;
		char key;
		int i = 0;

		while (1) {
			system("cls");
			
			color(10);
			cout << "\n\n\t\t\t\t[ BINARY TREE MENU ]" << endl;
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
			cout << "5. 2D BINARY TREE" << endl;

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
						root = insert(root, a);
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
					if (searchRecursive(root, a))
					{
						root = deleteRecursive(root, a);
						cout<<"\n\n";
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
					Node* temp = searchRecursive(root, a);
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
					inorderRecursive(root);
					cout << endl;
					cout << endl;

					cout << "Pre-Order Traversal : ";
					preorderRecursive(root);
					cout << endl;
					cout << endl;

					cout << "Post-Order Traversal : ";
					postorderRecursive(root);
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

					SDL_Window* window = SDL_CreateWindow("Binary Tree Visualization", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

					cout << "\n\n\t\t\tEXITING BINARY TREE..." << endl;
					this_thread::sleep_for(std::chrono::seconds(1));

					break;
				}
			}
			
		}
	}

	//TO INSERT THE DATA IN THE BINARY TREE

	Node* insert(Node* root, int val) {
		Node* n = new Node(val);

		if (root == nullptr)
			return n;

		queue<Node*> q;
		q.push(root);

		while (!q.empty())
		{
			Node* t = q.front();
			q.pop();

			if (t->left == nullptr)
			{
				t->left = n;
				break;
			}
			else q.push(t->left);

			if (t->right == nullptr)
			{
				t->right = n;
				break;
			}
			else q.push(t->right);
		}

		return root;
	}

	//TO DELETE THE NODE IF PRESENT
	
	Node* deleteRecursive(Node* current, int value) {
		if (current == nullptr) {
			return current;
		}

		if (value == current->value) {
			if (current->left == nullptr) {
				Node* temp = current->right;
				delete current;
				return temp;
			}
			else if (current->right == nullptr) {
				Node* temp = current->left;
				delete current;
				return temp;
			}
			else {
				Node* temp = findMin(current->right);
				current->value = temp->value;
				current->right = deleteRecursive(current->right, temp->value);
			}
		}
		else if (searchRecursive(current->left, value)) {
			current->left = deleteRecursive(current->left, value);
		}
		else if (searchRecursive(current->right, value)) {
			current->right = deleteRecursive(current->right, value);
		}

		return current;
	}

	Node* findMin(Node* node) {
		Node* result = node;
		if (node->left)
		{
			Node* lmin = findMin(node->left);
			if (lmin->value < node->value)
				result = node->left;
		}
		if (node->right)
		{
			Node* rmin = findMin(node->right);
			if (rmin->value < node->value)
				result = node->right;
		}

		return result;
	}

	//TO FIND THE DATA TO BE RETREIVED
	Node* searchRecursive(Node* current, int value) {
		if (current == nullptr || current->value == value) {
			return current;
		}

		Node* leftResult = searchRecursive(current->left, value);
		if (leftResult != nullptr) {
			return leftResult;
		}

		return searchRecursive(current->right, value);
	}
	// Recursive funtion to perform inorder traversal and print the values
	void inorderRecursive(Node* current) {
		if (current != nullptr) {
			inorderRecursive(current->left);
			std::cout << current->value << " ";
			inorderRecursive(current->right);
		}
	}

	// Recursive function to perform preorder traversal and print the values
	void preorderRecursive(Node* current) {
		if (current != nullptr) {
			std::cout << current->value << " ";
			preorderRecursive(current->left);
			preorderRecursive(current->right);
		}
	}

	// Recursive function to perform postorder traversal and print the values
	void postorderRecursive(Node* current) {
		if (current != nullptr) {
			postorderRecursive(current->left);
			postorderRecursive(current->right);
			std::cout << current->value << " ";
		}
	}
};

