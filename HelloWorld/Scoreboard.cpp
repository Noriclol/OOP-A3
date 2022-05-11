#include "Scoreboard.h"

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

	//Get filelength to use for array

	filelength = (int)GetFileLength(filename);

	//set scores length
	scores = new unsigned int[filelength];

	Load();
}

DynamicArray::~DynamicArray()
{
	Save();
	delete[] scores;
}

void DynamicArray::Add(unsigned int n)
{
	unsigned int newlength = filelength + 1;
	unsigned int* newscores = new unsigned int[newlength];

	//copy contents from old arr to new
	memcpy(newscores, scores, filelength * sizeof(unsigned int));

	//add new number
	newscores[newlength - 1] = n;


	//clear old dynamic array
	delete[] scores;

	//set size and pointer to created array
	filelength = newlength;
	scores = newscores;

}

void DynamicArray::Sort()
{
	int temp;

	for (int i = 0; i < filelength - 1; i++) {
		for (int j = i + 1; j < filelength; j++) {

			if (scores[i] < scores[j]) {

				temp = scores[j];

				scores[j] = scores[i];

				scores[i] = temp;

			}
		}
	}
}

void DynamicArray::Display()
{
	for (int i = 0; i < filelength; ++i)
		cout << to_string(scores[i]) << " ";

	cout << endl;
}

unsigned int DynamicArray::GetFileLength(string filename)
{
	ifstream file;
	file.open(filename);
	unsigned int length = 0; {};
	for (string line; std::getline(file, line); )
	{
		length++;
	}
	file.close();
	return length;
}


void DynamicArray::Load() // runs on Restart. Loads Array stored in scores.txt
{
	ifstream file;


	file.open(filename);

	int count = 0;
	for (string line; std::getline(file, line);)
	{
		if (!(count <= filelength))
			return;

		const unsigned int n = stoi(line);
		scores[count] = n;
		count++;
	}

	file.close();
}

void DynamicArray::Save() // Runs on Game Over
{
	ofstream file;
	char ch = ',';
	file.open(filename, ios::out | ios::trunc);

	for (int i = 0; i < filelength; i++)
	{
		unsigned int x = scores[i];
		string line = to_string(x);
		line += ch;
		file << line << endl;
	}
	file.close();
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




