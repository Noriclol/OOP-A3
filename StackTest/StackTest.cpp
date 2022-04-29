
#include <iostream>

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
	void Pop() {
		if (top <= -1)
			return;
		else {
			stack[top] = 0;
			top--;
		}
	}

	bool Push(unsigned int input) {
		if (top >= n - 1)
			return false;
		//cout << "Stack Overflow" << endl;
		else {
			top++;
			stack[top] = input;
			return true;
		}
	}

	unsigned int Peek() {
		return stack[top];
	}

	bool Empty() {
		if (top == -1)
		{
			return true;
		}
		return false;
	}
};




Stack Sort(Stack& input) {
	Stack tmpStack;

	while (input.top != -1)
	{
		unsigned int tmp = input.Peek();
		input.Pop();

		while (tmpStack.top != -1 && tmpStack.Peek() > tmp)
		{
			input.Push(tmpStack.Peek());
			tmpStack.Pop();
		}

		tmpStack.Push(tmp);
	}

	return tmpStack;
}

int main()
{
    std::cout << "Stack Test\n";

	Stack input;
	input.Push(34);
	input.Push(3);
	input.Push(31);
	input.Push(98);
	input.Push(92);

	Stack tmpStack = Sort(input);

	while (!tmpStack.Empty())
	{
		cout << tmpStack.Peek() << "\n ";
		tmpStack.Pop();
	}

}



