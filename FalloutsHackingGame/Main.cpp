#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <sstream>

void populateWords(std::vector<std::string> &v, int length);
int numberOfGuesses(int d);
void printInfo(std::vector<std::string> v, int g);
int compareWords(std::string w1, std::string w2);

int main()
{
	//Difficulty
	int difficulty = 0;

	//Input
	std::string input;

	//Word length based on difficulty, base word lenght is 4
	int wordLength = 4;

	//Vector to hold the words
	std::vector<std::string> words;
	words.resize(8);

	//String to hold the players choice
	std::string choice = "";

	//Correct word the player needs to guess
	std::string correctWord = "";

	bool win = false;

	//Get the difficulty
	while (difficulty < 1 || difficulty > 5)
	{
		std::cout << "Enter your difficulty (1-5): ";
		
		std::cin >> difficulty;
	}

	//Let the user know something is happening
	std::cout << "\nRetrieving passwords..." << std::endl;

	//Add to the wordLength
	wordLength += difficulty;

	//Get the words we will use for the game
	populateWords(words, wordLength);

	//Pick a random word from the vector to be the correct word
	correctWord = words.at(rand() % words.size());

	//Number of guesses the player gets
	int numOfGuesses = numberOfGuesses(difficulty);

	//Print the game information
	printInfo(words, numOfGuesses);

	//Correct letters
	int numOfCorrectLetters;

	//The main game loop
	while (numOfGuesses > 0 && choice != correctWord)
	{
		std::cin >> choice;

		//Decrease numOfGuesses if incorrect
		if (choice != correctWord)
		{
			numOfGuesses--;
		}
		else
		{
			win = true;
			break;
		}

		numOfCorrectLetters = compareWords(correctWord, choice);
		std::cout << numOfCorrectLetters << "/" << correctWord.size() << " correct" << std::endl;

		//Print out the number of guesses that they have
		std::cout << "\nGuesses remaining: " << numOfGuesses;

		//Prompt user for their input
		std::cout << "\n>> ";
	}

	if (win)
	{
		std::cout << "\n\nCorrect password.\n";
	}
	else
	{
		std::cout << "\n\nLocked out.\n";
	}

	system("pause");
	return 0;
}

/*
 This function reads the words from the text file and finds the words with the correct length.
 It then adds the correct amount of those words to the vector we will use to hold the possible choices.
*/
void populateWords(std::vector<std::string> &v, int length)
{
	//ifstream to read the txt file
	std::ifstream inFile("enable1.txt");

	//vector to hold all words that match in length
	std::vector<std::string> words;

	//Get all words that match the correct length
	for (std::string line; getline(inFile, line);)
	{
		if (line.size() == length)
		{
			words.push_back(line);
		}
	}

	//Index for the array
	int index = 0;

	srand(time(NULL));

	//Add random words from the vector to the array
	while (v.at(v.size() - 1) == "")
	{
		//Add to the vector a word that is in the other vectror
		v.at(index) = words.at(rand() % words.size() - 1);
		index++;
	}
}

/*
 This function returns the number of guesses the player is allowed based on difficulty
*/
int numberOfGuesses(int d)
{
	switch (d)
	{
	case 1:
		return 5;
		break;
	case 2:
		return 4;
		break;
	case 3:
		return 3;
		break;
	case 4:
		return 3;
		break;
	case 5:
		return 3;
		break;
	default:
		return 3;
		break;
	}
}

/*
 This function prints the information to the screen. It will print the words to choose from and the 
 number of guesses that the player has left
*/
void printInfo(std::vector<std::string> v, int g)
{
	//Prompt the player
	std::cout << "Choose a password:\n" << std::endl;

	//Print out each word
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v.at(i) << std::endl;
	}

	//Print out the number of guesses that they have
	std::cout << "\nGuesses remaining: " << g;
	
	//Prompt user for their input
	std::cout << "\n>> ";
}

/*
 This function compares the words used to see how many letters guessed were in the correct order
*/
int compareWords(std::string w1, std::string w2)
{
	int amountCorrect = 0;

	for (int i = 0; i < w1.size(); i++)
	{
		if (w1[i] == w2[i])
		{
			amountCorrect++;
		}
	}

	return amountCorrect;
}