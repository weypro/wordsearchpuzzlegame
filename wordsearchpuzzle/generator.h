#pragma once
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <cctype>
#include <fstream>
#include <time.h>
#include <string>
#include "database.h"

using namespace std;

const int GRID_SIZE = 10;

//Enum containing all the different direction the words can face
enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
	UP_LEFT,
	UP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT
};

struct point { int x, y; }; //Declare a point structure that represents a point on the grid

class Generator {
	char grid[GRID_SIZE][GRID_SIZE]; //Create a nxn grid
	char NULL_CHAR; //The character that represents a null value
	string words[7];
public:
	Generator();
	char GenerateRandomChar(); //returns a random character
	bool CanInsert(const char* word, point start, direction d); //Checks if the given word can be inserted at the start position facing direction d
	void InsertWord(const char* word); //Place word at a random, valid location facing a random direction
	void ClearGrid(); //Sets the grid to be all null values
	void FillGrid(); //Fills null values with random characters
	void PrintGrid(); //Prints the grid to stdout
	point ShiftPoint(point start, direction d); //Returns the shifted point
	//void ReadFile(char* filename);
	void InsertWordsFromList();
	//void PuzzleToFile(char* filename);
};
