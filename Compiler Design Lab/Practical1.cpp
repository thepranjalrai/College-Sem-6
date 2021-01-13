#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// A class which represents set of rules
class rules
{
public:
	const string delimiters = " +-*/,;><=()[]{}";	//Punctuators or Delimiters
	const string operators = "+-*/><=";				//Operators
	string keywords[94];							//Keywords

	void loadKeywords()								//Function to load keywords from a file
	{
		fstream dict("keywords.txt", fstream::in);

		int i = 0;
		while (!dict.eof())
		{
			string word;
			getline(dict, word);
			keywords[i++] = word;
		}

		dict.close();
	}

	bool is_keyword(string s)						//Returns true if s is a keyword
	{
		for (string w : keywords)
			if (s == w) return true;
		return false;
	}

	bool is_delimiter(char c)						//Returns true if c is a punctuator
	{
		for (char x : delimiters)
			if (x == c) return true;
		return false;
	}

	bool is_operator(char c)						//Returns true if c is an operator
	{
		for (char x : operators)
			if (x == c) return true;
		return false;
	}

	int is_number(string s)							//Returns : 0 if not a number; 1 if integer; 2 if real
	{
		int decimal_count = 0;

		for (char c : s)
			if (int(c) >= 48 && int(c) <= 57) {}
			else if (c == '.' && !decimal_count) decimal_count++;
			else return 0;
		
		return (decimal_count ? 2 : 1);
	}

	bool is_identifier(string s)					//Returns true if s is an identifier
	{
		if (int(s[0]) >= 48 && int(s[0]) <= 57)
			return false;
		for(char c : s.substr(1, s.length()-1))
			if(!isalnum(int(c))) return false;

		return true;
	}
	
	rules()											//Constructor function
	{
		loadKeywords();
	}
} cpp;												//Declaring CPP instance of rules

string *keywords = new string[100];					//Arrays for storing respective tokens
string *identifiers = new string[100];
string *litrals = new string[100];
string *punctuators = new string[100];
string *operators = new string[100];

int k_index = 0, i_index = 0, l_index = 0, p_index = 0, o_index = 0;	//Index variables for respective arrays

void process(string input_filename)					//The dunction to do token classification
{
	ifstream file(input_filename, fstream::in);
	while (!file.eof())
	{
		string line;
		getline(file, line);												//For eachline in file
				
		int left = 0, right = 0;											//Initialize token indices
		int len = line.length() - 1;										//Consider line length

		cout << line << endl;												//Show line
		
		while (right <= len && left <= right)
		{
			if(cpp.is_delimiter(line[right]) == false)						//If not a punctuator, see next character
				right++;
			
			if (cpp.is_delimiter(line[right]) && left == right)				//If punctuator, and token if of unit length
			{
				if (cpp.is_operator(line[right]))							//If Operator, classify.
				{
					operators[o_index++] = line[right];
					//cout << "\n\t" << line[right] << " is OPERATOR";
				}
				else if (line[right] == ' ') {}								//If Whitespace, ignore.
				else														//Else, classify as punctuator.
				{
					punctuators[p_index++] = line[right];
					//cout << "\n\t" << line[right] << " is PUNCTUATOR";
				}

				right++;													//Consider next character
				left = right;
			}
			else if (cpp.is_delimiter(line[right]) && left != right || (right == len && left != right))	//If proper token
			{
				string token = line.substr(left, right - left);				//Extract token

				if (cpp.is_keyword(token))									//Classify as Keyword/Integer/Real Number/Identifier/Literal
				{
					keywords[k_index++] = token;	
					//cout << "\n\t\"" << token << "\" is KEYWORD";
				}
				else if (cpp.is_number(token) == 1)
				{
					litrals[l_index++] = token;		
					//cout << "\n\t\"" << token << "\" is INTEGER";
				}
				else if (cpp.is_number(token) == 2)
				{
					litrals[l_index++] = token;		
					//cout << "\n\t\"" << token << "\" is REAL NUMBER";
				}
				else if (cpp.is_identifier(token))
				{
					identifiers[i_index++] = token; 
					//cout << "\n\t\"" << token << "\" is IDENTIFIER";
				}
				else
				{
					litrals[l_index++] = token;		
					//cout << "\n\t\"" << token << "\" is LITERAL";
				}

				left = right;
				//cout << "\n" << left << "_" << right;
			}
		}		
	}
}

void print()							//Function to show output
{
	cout << "KEYWORDS\n";
	for (int i = 0; i < k_index; i++)
		cout << keywords[i] << "\t";

	cout << "\n\nIDENTIFIERS\n";
	for (int i = 0; i < i_index; i++)
		cout << identifiers[i] << "\t";

	cout << "\n\nLITERALS\n";
	for (int i = 0; i < l_index; i++)
		cout << litrals[i] << "\t";

	cout << "\n\nPUNCTUATORS\n";
	for (int i = 0; i < p_index; i++)
		cout << punctuators[i] << "\t";

	cout << "\n\nOPERATORS\n";
	for (int i = 0; i < o_index; i++)
		cout << operators[i] << "\t";
}

int main()
{
	cout << "______________\n\n";
	cout << "The Input File:-\n______________\n\n";
	string input_filename = "input.txt";	

	process(input_filename);

	cout << "______________\n\n";
	cout << "The OUTPUT:-\n______________\n\n";
	print();

	cout << "\n\n_____________________________\n\n";
}