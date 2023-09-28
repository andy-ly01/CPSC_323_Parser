#include <vector>
#include <string>
#include <iostream>

using namespace std;

//prints out the current stack.
#define currentStack(v) \
cout << "Current stack: "; \
for (auto& x : v) cout << x << " "; \
cout << "\n\n";

/*
Parsing Table.
Row 1: 'E' | Row 2: 'Q' | Row 3: 'T' | Row 4: 'R' | Row 5: 'F'
Column 1: 'a' | Column 2: '+' | Column 3: '-' | Column 4: '*' |
Column 5: '/' | Column 6: '()' | Column 7: ')' | Column 8 = '$' |
*/
class ParsingTable {
public:
	vector<vector<int> > parseTable{ 6, vector<int>(9,0) };
	ParsingTable() 
	{
		for (int i = 0; i < parseTable.size(); ++i) 
		{
			parseTable[i][0] = 0;
		}
		for (int i = 0; i < parseTable[0].size(); ++i) 
		{
			parseTable[0][i] = 0;
		}
		parseTable[1][1] = 11; // 11 = TQ
		parseTable[1][6] = 16; // 16 = TQ
        parseTable[2][2] = 22; // 22 = +TQ
        parseTable[2][3] = 23; // 23 = -TQ
        parseTable[2][7] = 27; // 27 = ε
        parseTable[2][8] = 28; // 28 = ε
        parseTable[3][1] = 31; // 31 = FR
        parseTable[3][6] = 36; // 36 = FR
        parseTable[4][2] = 42; // 42 = ε
        parseTable[4][3] = 43; // 43 = ε
        parseTable[4][4] = 44; // 44 = *FR
        parseTable[4][5] = 45; // 45 = /FR
		parseTable[4][7] = 47; // 47 = ε
		parseTable[4][8] = 48; // 48 = ε
		parseTable[5][1] = 51; // 51 = a
		parseTable[5][6] = 56; // 56 = (E)
	}

	// takes row and column as parameters, return the state.
	int Get(int row, int col) 
	{
		return parseTable[row][col];
	}
};

// returns row based on char
int ConvertToRow(char c) 
{
	switch (c)
	{
	case 'E':
		return 1;
	case 'Q':
		return 2;
	case 'T':
		return 3;
	case 'R':
		return 4;
	case 'F':
		return 5;
	default:
		return 0;
		break;
	}
}

// returns column based on char input
int ConvertToCol(char c) 
{
	switch (c)
	{
	case 'a':
		return 1;
	case '+':
		return 2;
	case '-':
		return 3;
	case '*':
		return 4;
	case '/':
		return 5;
	case '(':
		return 6;
	case ')':
		return 7;
	case '$':
		return 8;
	default:
		return 0;
		break;
	}
}


// Using a vector to represent stack because it is much easier to print out the current elements.
// Given the stack and an integer that represents a state(s) in the parsing table, push the corresponding state(s) onto the stack.
bool pushStack(vector<char>& parseStack, int x) 
{
	switch (x)
	{
	case 0:
		return false;
	case 11:
	case 16:
		cout << "Pushing to stack: TQ" << endl;
		parseStack.push_back('Q');
		parseStack.push_back('T');
		currentStack(parseStack);
		return true;
		break;
	case 22:
		cout << "Pushing to stack: +TQ" << endl;
		parseStack.push_back('Q');
		parseStack.push_back('T');
		parseStack.push_back('+');
		currentStack(parseStack);
		return true;
		break;
	case 23:
		cout << "Pushing to stack: -TQ" << endl;
		parseStack.push_back('Q');
		parseStack.push_back('T');
		parseStack.push_back('-');
		currentStack(parseStack);
		return true;
		break;
	case 27:
	case 28:
		cout << "Pushing to stack: ε" << endl;
		parseStack.push_back('e');	// 'e' is used in place of ε due to "multi character character constant" error
		currentStack(parseStack);
		return true;
		break;
	case 31:
	case 36:
		cout << "Pushing to stack: FR" << endl;
		parseStack.push_back('R');
		parseStack.push_back('F');
		currentStack(parseStack);
		return true;
		break;
	case 42:
	case 43:
		cout << "Pushing to stack: ε" << endl;
		parseStack.push_back('e'); // 'e' is used in place of ε due to "multi character character constant" error
		currentStack(parseStack);
		return true;
		break;
	case 44:
		cout << "Pushing to stack: *FR" << endl;
		parseStack.push_back('R');
		parseStack.push_back('F');
		parseStack.push_back('*');
		currentStack(parseStack);
		return true;
		break;	
	case 45:
		cout << "Pushing to stack: *FR" << endl;
		parseStack.push_back('R');
		parseStack.push_back('F');
		parseStack.push_back('/');
		currentStack(parseStack);
		return true;
		break;	
	case 47:
	case 48:
		cout << "Pushing to stack: ε" << endl;
		parseStack.push_back('e'); // 'e' is used in place of ε due to "multi character character constant" error
		currentStack(parseStack);
		return true;
		break;
	case 51:
		cout << "Pushing to stack: a" << endl;
		parseStack.push_back('a');
		currentStack(parseStack);
		return true;
		break;
	case 56:
		cout << "Pushing to stack: (E)" << endl;
		parseStack.push_back(')');
		parseStack.push_back('E');
		parseStack.push_back('(');
		currentStack(parseStack);
		return true;
		break;
	default:
		return false;
		break;
	}
}