#include "generator.h"

vector<string> wordlist;

Generator::Generator() {
	NULL_CHAR = 'x'; //Sets the null char to a lowercase x
}

char Generator::GenerateRandomChar() {
	return 'A' + rand() % 26; //leet way to generate a random character
}

//Sets all values in grid to a null character
void Generator::ClearGrid() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int k = 0; k < GRID_SIZE; k++) {
			grid[i][k] = NULL_CHAR; //Every empty value will be a lowercase x
		}
	}
}

//Checks if word can be inserted in the grid at the given start point
bool Generator::CanInsert(const char* word, point start, direction d) {
	int i = 0;
	point newPoint = start;
	while (i < (int)strlen(word)) //Iterates through the word char array
	{
		//Attempt to shift the point
		try {
			if (grid[newPoint.x][newPoint.y] == NULL_CHAR) {
				newPoint = ShiftPoint(newPoint, d);
				i++;
			}
			else {
				return false;
			}
		}
		catch (const char* msg) //Returns false if the out of bounds error occurs
		{
			/*cout << "Cannot insert one of the words.  Please try again or choose a new word." << endl;
			exit(1);*/
			return false;
		}
	}
	return true;
}

//Replaces empty tiles with a random character
void Generator::FillGrid() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int k = 0; k < GRID_SIZE; k++) {
			if (grid[i][k] == NULL_CHAR) {
				grid[i][k] = GenerateRandomChar(); //Set every null value to a random character
			}
		}
	}
}

//Prints the grid to stdout
void Generator::PrintGrid() {
	printf("Generated Puzzle:\n");
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int k = 0; k < GRID_SIZE; k++) {
			if (k == 0) {
				printf("\t%c ", grid[i][k]); //Puts a tab at the first column to make it look pretty
			}
			else if (k == GRID_SIZE - 1) {
				printf("%c\n", grid[i][k]); //Append a newline if it is on the last column
			}
			else {
				printf("%c ", grid[i][k]);
			}
		}
	}
}

//Shifts the point depending on the direction
point Generator::ShiftPoint(point start, direction d) {
	switch (d) {
	case UP:
		start.x--; //Move up a row
		break;
	case DOWN:
		start.x++; //Move down a row
		break;
	case LEFT:
		start.y--; //Row stays the same
		break;
	case RIGHT:
		start.y++; //Row stays the same
		break;
	case UP_LEFT:
		start.x--; //Row moves up
		start.y--; //Column moves left
		break;
	case UP_RIGHT:
		start.x--; //Row moves up
		start.y++; //Column moves right
		break;
	case DOWN_LEFT:
		start.x++; //Row moves down
		start.y--; //Column moves to left
		break;
	case DOWN_RIGHT:
		start.x++; //Row moves down
		start.y++; //Column moves right
		break;
	default:
		break;
	}
	//Handle out of bounds errors
	if (start.x < -1 || start.x > GRID_SIZE || start.y < -1 || start.y > GRID_SIZE)
	{
		throw "Out of Bounds";
	}
	return start;
}

void Generator::InsertWord(const char* word) {
	point start;
	direction d;
	do {
		start.x = rand() % GRID_SIZE; //set to a random row
		start.y = rand() % GRID_SIZE; //set to a random column
		d = direction(rand() % 8); //get a random direction
	} while (!CanInsert(word, start, d));
	int i = 0;
	point newPoint = start;
	while (i < (int)strlen(word))
	{
		grid[newPoint.x][newPoint.y] = (char)toupper(word[i]);//
		newPoint = ShiftPoint(newPoint, d);
		i++;
	}
}
/*
void Generator::ReadFile(char* filename) {
	ifstream wordsFile(filename);
	string word;
	int line = 0;
	if (wordsFile.is_open()) {
		printf("Reading file '%s'\n", filename);
		while (getline(wordsFile, word)) {
			words[line] = word;
			line++;
			if (line == 8) {
				throw "Words list can not have more than 7 words";
			}
			if (word.length() < 2 || word.length() > GRID_SIZE - 1) {
				throw "Words must be at least two characters and no more than the grid size";
			}
		}
	}
	else {
		throw "Cannot open words list file";
	}
}
*/
void Generator::InsertWordsFromList() {
	//Iterate through all of the indexes in the array and insert them into the grid
	/*for (int i = 0; i < (int)(sizeof(words) / sizeof(words[0])); i++) {
		string word = words[i];
		InsertWord(word.c_str()); //Convert the word (std::string) into a useable char* array
	}*/
	vector<string> ::iterator it1;
	for (it1 = wordlist.begin(); it1 != wordlist.end(); it1++)
	{
		string word = *it1;
		InsertWord(word.c_str()); //Convert the word (std::string) into a useable char* array
	}
}
/*
void Generator::PuzzleToFile(char* filename) {
	ofstream output(filename);
	char c;
	if (output.is_open()) {
		printf("Writing to file '%s'\n", filename);
		for (int i = 0; i < GRID_SIZE; i++) {
			for (int k = 0; k < GRID_SIZE; k++) {
				if (k == GRID_SIZE - 1) {
					c = grid[i][k];
					output.put(c);
					output.put('\n');	//Append a newline if it is on the last column
				}
				else {
					c = grid[i][k];
					output.put(c);
				}
			}
		}
	}
	else {
		throw "Cannot create output file";
	}
}
*/