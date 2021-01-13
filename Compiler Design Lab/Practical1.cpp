#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class rules
{
public:
	const string delimiters = " +-*/,;><=()[]{}";
	const string operators = "+-*/><=";
	string keywords[94];

	void loadKeywords()
	{
		fstream dict("dictionaries/keywords.txt", fstream::in);

		int i = 0;
		while (!dict.eof())
		{
			string word;
			getline(dict, word);
			keywords[i++] = word;
		}

		dict.close();
	}

	bool is_keyword(string s)
	{
		for (string w : keywords)
			if (s == w) return true;
		return false;
	}

	bool is_delimiter(char c)
	{
		for (char x : delimiters)
			if (x == c) return true;
		return false;
	}

	bool is_operator(char c)
	{
		for (char x : operators)
			if (x == c) return true;
		return false;
	}

	int is_number(string s)	//0-not number; 1-integer; 2-real
	{
		int decimal_count = 0;

		for (char c : s)
			if (int(c) >= 48 && int(c) <= 57) {}
			else if (c == '.' && !decimal_count) decimal_count++;
			else return 0;
		
		return (decimal_count ? 2 : 1);
	}

	bool is_identifier(string s)
	{
		if (int(s[0]) >= 48 && int(s[0]) <= 57)
			return false;
		for(char c : s.substr(1, s.length()-1))
			if(!isalnum(int(c))) return false;

		return true;
	}
	
	rules()
	{
		loadKeywords();
	}
} cpp;

//string *tokens = new string[100];
string *keywords = new string[100];
string *identifiers = new string[100];
string *litrals = new string[100];
string *punctuators = new string[100];
string *operators = new string[100];
int k_index = 0, i_index = 0, l_index = 0, p_index = 0, o_index = 0;

void process(string input_filename)
{
	ifstream file(input_filename, fstream::in);
	while (!file.eof())
	{
		string line;
		getline(file, line);
				
		int left = 0, right = 0;
		int len = line.length() - 1;

		//cout << "\n\n" << len << "> " << line;
		cout << line << endl;
		
		while (right <= len && left <= right)
		{
			if(cpp.is_delimiter(line[right]) == false)
				right++;
			
			if (cpp.is_delimiter(line[right]) && left == right)
			{
				if (cpp.is_operator(line[right]))
				{
					operators[o_index++] = line[right];
					//cout << "\n\t" << line[right] << " is OPERATOR";
				}
				else if (line[right] == ' ') {}
				else
				{
					punctuators[p_index++] = line[right];
					//cout << "\n\t" << line[right] << " is PUNCTUATOR";
				}

				right++;
				left = right;
			}
			else if (cpp.is_delimiter(line[right]) && left != right || (right == len && left != right))
			{
				string token = line.substr(left, right - left);

				if (cpp.is_keyword(token))
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

void print()
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
	//cout << cpp.is_number("69.4a20");

	//cout << "Enter input file address : ";
	string input_filename = "input.txt";
	//cin >> input_filename;

	process(input_filename);
	print();

	cout << "\n\n_____________________________\n";
}