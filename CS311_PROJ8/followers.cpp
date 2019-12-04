// followers.cpp
// Alex Cater, Kurt Nunn, Christopher Seamount
// 2019-12-03
// CS 311 Fall 2019
// Header for C++ STL table implementation
// There is no associated source file.

// for std::cin, std::cout, std::endl
#include<iostream>
// for std::ifstream
#include<fstream>
// for std::string
#include<string>
// for std::vector
#include<vector>
// for std::sort
#include<algorithm>
// for std::map
#include<map>

typedef std::vector<std::string> ValType;
typedef std::map<std::string, ValType> MapType;


// printTable
// Prints table of words and all words that directly follow
// Pre:
//     None
// Requirements on Types:
//     Must pass type: map<string,vector<string>>
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void printTable(const MapType& table)
{
	std::cout << "Number of distinct words: " << table.size() << std::endl << std::endl;
	for (auto n : table)
	{
		std::cout << n.first << " : ";
		for (auto itr = n.second.begin(); itr != n.second.end(); ++itr)
		{
			std::cout << *itr << " ";
		}
		std::cout << std::endl;
	}
}

// sortTable
// Sorts a given table of words in lexicographical order
// Pre:
//     The words contain characters that can be compared according to lexicographical order.
// Requirements on Types:
//     Must pass type: map<string,vector<string>>
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void sortTable(MapType& table)
{
	for (auto& n : table)
	{
		std::sort(n.second.begin(), n.second.end());
	}
}

// insertWord
// Inserts the specified word into the table and unique words that immediatly follow
// Pre:
//     None.
// Requirements on Types:
//     Must pass type: map<string,vector<string>>, ands two strings
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void insertWord(MapType& table, const std::string& currentword, std::string& previousword)
{
	if (table.find(previousword) == table.end())
	{
		table.insert(MapType::value_type(previousword, ValType()));
		table[previousword].push_back(currentword);
	}
	else
	{
		if (std::find(table[previousword].begin(), table[previousword].end(), currentword) == table[previousword].end())
		{
			table[previousword].push_back(currentword);
		}
	}

	previousword = currentword;
	return;
}

// makeTable
// creates table of unique words and words that directly follow
// Pre:
//     must check if file was opened correctly before passing into this function
// Requirements on Types:
//     must pass an ifstream
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
MapType makeTable(std::ifstream& myfile)
{
	MapType table;
	std::string currentword = "";
	std::string previousword = "";

	myfile >> previousword;
	while (!myfile.eof())
	{
		myfile >> currentword;
		insertWord(table, currentword, previousword);
	}
	std::string temp = "";
	insertWord(table, temp, currentword);
	sortTable(table);

	return table;
}

// main
// Inputs a filename from the user and reads the named file.
// Pre:
//     The file with the specified name exists within the current directory.
// Requirements on Types:
//     None.
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
int main()
{
	std::string filename;
	std::cout << "Enter a filename: ";
	std::getline(std::cin, filename);

	std::ifstream myfile;
	myfile.open(filename);
	if (!myfile)
	{
		std::cout << "Unable to open file \"" << filename << "\"" << std::endl;
		return -1;
	}

	MapType table = makeTable(myfile);

	printTable(table);

	myfile.close();

	return 0;
}
