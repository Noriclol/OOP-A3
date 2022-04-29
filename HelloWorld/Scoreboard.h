#pragma once
#include <iostream>
#include <fstream>

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
	int size = 5;
	unsigned int* scores;

	DynamicArray();
	~DynamicArray();

	void Add(unsigned int n);
	unsigned int* Sort(unsigned int input[], int size);

	void display();

private:
	unsigned int* Load();
	void Save();
};

class Scoreboard {
public:
	//Fields
	Stack board;
	DynamicArray board2 = DynamicArray();

	unsigned int currentScore = 0;

	// Scoreboard Functions
	void Score(unsigned int points);
	Stack SortScoreboard(Stack& input);


private:

};

