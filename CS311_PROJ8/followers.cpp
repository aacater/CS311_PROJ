// followers.cpp
// Alex Cater, Kurt Nunn, Christopher Seamount
// 2019-12-03
// CS 311 Fall 2019
// Header for C++ STL table implementation
// There is no associated source file.

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

typedef std::vector<std::string> ValType;
typedef std::map<std::string, ValType> MapType;


// printList
// Prints list of words and all words that directly follow
// Pre:
//     None
// Requirements on Types:
//     Must pass type: map<string,vector<string>>
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void printList(const MapType& list)
{
	std::cout << "Number of distinct words: " << list.size() << std::endl << std::endl;
	for (auto n : list)
	{
		std::cout << n.first << " : ";
		for (auto itr = n.second.begin(); itr != n.second.end(); ++itr)
		{
			std::cout << *itr << " ";
		}
		std::cout << std::endl;
	}
}

// sortList
// Sorts a given list of words in lexicographical order
// Pre:
//     The words contain characters that can be compared according to lexicographical order.
// Requirements on Types:
//     Must pass type: map<string,vector<string>>
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void sortList(MapType& list)
{
	for (auto& n : list)
	{
		std::sort(n.second.begin(), n.second.end());
	}
}

// insertWord
// Inserts the specified word into the list.
// Pre:
//     None.
// Requirements on Types:
//     Must pass type: map<string,vector<string>>, ands two strings
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void insertWord(MapType& list, const std::string& currentword, std::string& previousword)
{
	if (list.find(previousword) == list.end())
	{
		list.insert(MapType::value_type(previousword, ValType()));
		list[previousword].push_back(currentword);
	}
	else
	{
		if (std::find(list[previousword].begin(), list[previousword].end(), currentword) == list[previousword].end())
		{
			list[previousword].push_back(currentword);
		}
	}

	previousword = currentword;
	return;
}

// makeList
// creates map of words and then calls a function to sort
// Pre:
//     must check if file was opened correctly before passing into this function
// Requirements on Types:
//     must pass an ifstream
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
MapType makeList(std::ifstream& myfile)
{
	MapType list;
	std::string currentword = "";
	std::string previousword = "";

	myfile >> previousword;
	while (!myfile.eof())
	{
		myfile >> currentword;
		insertWord(list, currentword, previousword);
	}
	std::string temp = "";
	insertWord(list, temp, currentword);
	sortList(list);

	return list;
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

	MapType list = makeList(myfile);

	printList(list);

	myfile.close();

	return 0;
}
