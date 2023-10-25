#include<iostream>
#include <SDL.h>
#include<Windows.h>
#include<conio.h>
#include"binaryTree.h"
#include "ternaryTree.h"
#include "binarySearchTree.h"
#include "ternarySearchTree.h"
#include "avl.h"
#include "redYellowTree.h"

using namespace std;

int main(int argc, char* argv[])
{
	int Set[] = { 10,10,10,10,10,10,10 };
	int counter = 1;
	char key;
	int i = 0;
	while (1)
	{
		system("cls");

		color(10);
		cout << "\n\n\t\t\t\t[ MAIN MENU ]" << endl;
		cout << "\t\t\t-----------------------------" << endl;


		gotoxy(7, 8);
		color(Set[0]);
		cout << "1. Binary Tree" << endl;

		gotoxy(7, 9);
		color(Set[1]);
		cout << "2. Ternary Tree" << endl;

		gotoxy(7, 10);
		color(Set[2]);
		cout << "3. Binary Search Tree" << endl;

		gotoxy(7, 11);
		color(Set[3]);
		cout << "4. Ternary Search Tree" << endl;
		
		gotoxy(7, 12);
		color(Set[4]);
		cout << "5. AVL Tree" << endl;

		gotoxy(7, 13);
		color(Set[5]);
		cout << "6. Red Yellow Tree" << endl;

		gotoxy(7, 14);
		color(Set[6]);
		cout << "0. Exit the program" << endl;

		gotoxy(20, 20);
		color(7);
		cout << "TIP:USE UP AND DOWN ARROW KEYS FOR NAVIGATION" << endl;

		key = _getch();

		if (key == 72 && (counter > 1 && counter <= 7)) {
			counter--;
			i--;
		}

		if (key == 80 && (counter >= 1 && counter < 7)) {
			counter++;
			i++;
		}

		for (int j = 0; j < 7; j++) {
			Set[j] = 10;
		}

		Set[i] = 12;

		if (key == '\r') {
			if (counter == 1) {
				binaryTree::binaryTree();
			}

			if (counter == 2) {
				ternaryTree::ternaryTree();
			}

			if (counter == 3) {

				binarySearchTree::binarySearchTree();
				
			}

			if (counter == 4) {
				ternarySearchTree::ternarySearchTree();
			}

			if (counter == 5) {
				AVL::AVL();
			}

			if (counter == 6) {
				redYellowTree::redYellowTree();
			}

			if (counter == 7) {
				exit(0);
			}

		}


	}

	return 0;

}