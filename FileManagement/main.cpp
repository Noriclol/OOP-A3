#include <fstream>
#include <iostream>
#include <string>

using namespace std;


class DynamicArray {

public:
	int size = 5;
	unsigned int* scores;

	DynamicArray()
	{
		//unsigned int* data = Load();
		//make new score array size of loaded data
		//scores = new unsigned int[sizeof(data)];
	}
	~DynamicArray();

	void Add(unsigned int n);
	unsigned int* Sort(unsigned int input[], int size);

	void display();

	

private:
	unsigned int* Load()
	{
		ifstream file;



		file.open("testfile.txt");

		unsigned int length = 0;
		for (string line; std::getline(file, line); )
		{
			length++;
		}
		file.close();

		file.clear();

		file.open("testfile.txt");

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

	
	void Save()
	{
		
	}

};

unsigned int GetFileLength(string filename)
{
	ifstream file;
	file.open(filename);
	unsigned int length = 0;{};
	for (string line; std::getline(file, line); )
	{
		length++;
	}
	file.close();
	return length;
}

int main()
{
	string filename = "testfile.txt";
	DynamicArray DyArr = DynamicArray();
	
	//cout << "enter arr size\n";
	int n = GetFileLength(filename);
	//cin >> n;
	unsigned int* arr = new unsigned int[n];

	for (int i = 0; i < n; i++)
	{
		arr[i] = 1;
	}
	for (int i = 0; i < n; i++)
	{
		cout << std::to_string(i) << ": " << arr[i] << endl;
	}
}
