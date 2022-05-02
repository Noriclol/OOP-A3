#include "Scoreboard.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "string"
#include  <iostream>

// implemented stack from https://www.codespeedy.com/stack-implementation-using-array-in-c/
// implemented stack sort from https://www.geeksforgeeks.org/sort-stack-using-temporary-stack/


using namespace std;

//stack

void Stack::Pop()
{
	if (top <= -1)
		return;
	else {
		stack[top] = 0;
		top--;
	}
}

bool Stack::Push(unsigned int input)
{
	if (top >= n - 1)
		return false;
	//cout << "Stack Overflow" << endl;
	else {
		top++;
		stack[top] = input;
		return true;
	}
}

unsigned int Stack::Peek()
{
	return stack[top];
}

bool Stack::Empty() {
	if (top == -1)
	{
		return true;
	}
	return false;
}




















//DynamicArray

DynamicArray::DynamicArray()
{
	//load scoreboard
	unsigned int* data = Load();
	//make new score array size of loaded data
	scores = new unsigned int[sizeof(data)];

	unsigned int first;

	/*memcpy(scores, data, sizeof(scores) * sizeof(unsigned int));

	size = sizeof(scores) / sizeof(unsigned int);

	delete[] data;*/
	
}

DynamicArray::~DynamicArray()
{
	////save scoreboard
	//
	//delete[] scores;
}

void DynamicArray::Add(unsigned int n)
{

	//unsigned int oldsize = sizeof(scores);
	//unsigned int newsize = oldsize + 1;

	//unsigned int* newscores = new unsigned int[newsize];

	////copy contents from old arr to new
	//memcpy(newscores, scores, oldsize * sizeof(unsigned int));

	////clear old dynamic array
	//delete[] scores;

	////set size and pointer to created array
	//size = newsize;
	//scores = newscores;
	//
}

unsigned int* DynamicArray::Sort(unsigned int input[], int size)
{
	/*std::sort(input[0], input[size - 1], std::greater<int>());
	return input;*/
	return 0;
}

void DynamicArray::display()
{
	/*for (int i = 0; i < size; ++i)
		cout << scores[i] << " ";*/
}

unsigned int* DynamicArray::Load() // runs on Restart. Loads Array stored in scores.txt
{
	ifstream file;

	file.open("Scores.txt");

	unsigned int length = 0;
	for (string line; std::getline(file, line); ) 
	{
		length++;
	}
	file.close();

	file.clear();

	file.open("Scores.txt");
	
	int count = 1;
	unsigned int* arr = new unsigned int[length];

	arr[0] = 1;
	arr[1] = 2;
	arr[2] = 3;

	for (unsigned int i = 0; i < length; i++)
	{
		//auto line = std::getline(file, line, ',');
		//unsigned int n = stoi()
		//arr[i] = std::getline(file, line, ',');
	}

	for (string line; std::getline(file, line, ',');)
	{
		unsigned int n = stoi(line);
		arr[count - 1] = n;
		unsigned int currentAdded = arr[count - 1];
		count++;
	}
		
	
	file.close();


	return arr;
}

void DynamicArray::Save() // Runs on Game Over
{
	/*ofstream file;
	file.open("Scores.txt");
	for (unsigned int i = 0; i < size; i++)
	{
		unsigned int line = scores[i];
		file << line << endl;
	}
	file.close();*/
}

















//Scoreboard

Stack Scoreboard::SortScoreboard(Stack& input)
{
	Stack tmpStack;

	while (!input.Empty())
	{
		unsigned int tmp = input.Peek();
		input.Pop();

		while (!tmpStack.Empty() && tmpStack.Peek() > tmp)
		{
			input.Push(tmpStack.Peek());
			tmpStack.Pop();
		}

		tmpStack.Push(tmp);
	}

	return tmpStack;
}

void Scoreboard::Score(unsigned int points)
{
	currentScore += points;
}




