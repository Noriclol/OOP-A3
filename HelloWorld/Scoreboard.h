#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

#include "Constants.h"

using namespace std;

class Stack {
public:
	//Fields
	unsigned int stack[5];
	int n = 5;
	int top = -1;

	//constructor
	Stack() {
		stack[0] = 0;
		stack[1] = 0;
		stack[2] = 0;
		stack[3] = 0;
		stack[4] = 0;
	}
	
	////functions
	void Pop();
	bool Push(unsigned int input);
	unsigned int Peek();
	bool Empty();

	//Stack Sort(Stack& input);


};

class DynamicArray{

public:
	unsigned int* scores;
	int filelength;
	string filename = "Scores.txt"; //change to scoreboard.txt

	DynamicArray();
	~DynamicArray();

	void Add(unsigned int n);
	void Sort();
	void Display();

private:

	unsigned int GetFileLength(string filename);
	void Load();
	void Save();

};

class Scoreboard {
public:
	//Fields
	DynamicArray board = DynamicArray();

	unsigned int currentScore = 0;

	// Scoreboard Functions
	void Score(unsigned int points);
	Stack SortScoreboard(Stack& input);


private:

};

