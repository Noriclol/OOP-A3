#include <fstream>
#include <iostream>
#include <string>

using namespace std;


class DynamicArray {

public:
	unsigned int* scores;
	int filelength;
	string filename = "testfile.txt";

	DynamicArray()
	{

		//Get filelength to use for array
		
		filelength = (int)GetFileLength(filename);

		//set scores length
		scores = new unsigned int[filelength];

		Load();
	}
	~DynamicArray()
	{
		Save();
		delete[] scores;
	}


	//untested
	void Add(unsigned int n)
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

	void Sort(/*unsigned int input[], int size*/)
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

	void Display()
	{
		for (int i = 0; i < filelength; ++i)
			cout << to_string(scores[i]) << " ";

		cout << endl;
	}

private:

	unsigned int GetFileLength(string filename)
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


	void Load()
	{
		ifstream file;
		

		file.open(filename);


		//error probably
		//for (std::getline(file, line, ',');int count = 0; count++)
		//{
		//	const unsigned int n = stoi(line);
		//	scores[count] = n;
		//}


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
	void Save()
	{

		ofstream file;
		char ch = ',';
		file.open("testfile.txt", ios::out | ios::trunc);

		for (int i = 0; i < filelength; i++)
		{
			unsigned int x = scores[i];
			string line = to_string(x);
			line += ch;
			file << line << endl;
		}
		file.close();
	}

};



int main()
{
	DynamicArray Data = DynamicArray();

	//Fancy Debugging menu

	bool closed = false;
	while (!closed)
	{
		unsigned int n = 0;
		cout << "	  Menu\n";
		cout << "1 add			: \n";
		cout << "2 sort			: \n";
		cout << "3 Display		: \n";
		cout << "4 close/save	: \n";
		int x = -1;
		cin >> x;
		switch (x) {
		case 1:
			//add
	
			cout << "Enter uint: ";
			cin >> n;
			cout << "\n";
			Data.Add(n);
	
			break;


		case 2:
			//sort
	
			cout << "Sorting...\n";
			Data.Sort();

			break;


		case 3:
			//Display

			cout << "Displaying Array...\n";
			Data.Display();
	
			break;


		case 4:
			//close and save



			cout << "Closing...\n";
			closed = true;

			break;


		case -1:
			//do nothing
			break;
		}
	}

}
