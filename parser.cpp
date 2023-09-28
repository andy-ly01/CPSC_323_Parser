#include "parser.hpp"

using namespace std;


int main() 
{
	ParsingTable parseTable;
	string inputString;
	char state;
	bool accepted = true;
	vector<char> parseStack;

	// Stack will have $ E as it's initial elements.
	parseStack.push_back('$');
	parseStack.push_back('E');


	// user input.
	cout << "Enter string" << endl;
	cin >> inputString;

	//prints out the current stack.
	currentStack(parseStack);
	do 
	{
		state = parseStack.back();
		char input = inputString[0];

		if (state == 'e') // 'e' is used in place of ε due to "multi character character constant" error
		{
			cout << "Popping from stack: ε" << endl;
			parseStack.pop_back();
			currentStack(parseStack);
		} 

		// If state does not equal input, then input string will be rejected.
		else if (state == 'a' || state == '+' || state == '-' ||
				state == '*' || state == '/'||state == '(' || state == ')') 
		{
			if (state == input) 
			{
				{
					cout << "Popping from stack: " << parseStack.back() << endl;
					parseStack.pop_back();
					currentStack(parseStack);
					inputString.erase(0, 1);
					cout << "Input: " << inputString << endl;
				}
			}
			else 
			{
				cout << "Rejected." << endl;
				accepted = false;
				break;
			}
		}

		else if (state == 'E' || state == 'T' || state == 'Q' || state == 'R' || state == 'F') 
		{
			int row = ConvertToRow(state);
			int col = ConvertToCol(input);
			if (parseTable.Get(row,col) != 0 || (!(row == 5 && col == 1))) 
			{
				cout << "Popping from stack: " << parseStack.back() << endl;
				parseStack.pop_back();
				currentStack(parseStack);
				if (!(pushStack(parseStack, parseTable.Get(row, col)))) 
				{
					accepted = false;
					break;
				}
			}
			else 
			{
				cout << "Rejected." << endl;
				accepted = false;
				break;
			}
		}

	} while (state != '$');	// do while state does not equal '$'

	if (accepted) 
		cout << "Accepted.\n";
	else 
		cout << "Rejected.\n";

	system("pause");
	return 0;
}