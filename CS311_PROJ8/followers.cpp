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

// sortList
// Sorts a given list of words in lexicographical order
// Pre:
//     The words contain characters that can be compared according to lexicographical order.
// Requirements on Types:
//     None.
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void sortList(MapType& list)
{
	for (auto &n : list)
	{
		std::sort(n.second.begin(), n.second.end());
	}
}

// insertWord
// Inserts the specified word into the list.
// Pre:
//     None.
// Requirements on Types:
//     None.
// Exception safety guarantee:
//     Basic Guarantee.
// exception neutral
void insertWord(std::ifstream& myfile, MapType& list, std::string& currentword, std::string& previousword, int& counter)
{
	if (previousword.empty())
	{
		previousword = currentword;
		return;
	}

	MapType::iterator itr = list.find(previousword);
	if (itr == list.end())
	{
		list.insert(MapType::value_type(previousword, ValType()));
		list[previousword].push_back(currentword);
		counter++;
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

	std::string currentword = "";
	std::string previousword = "";
	int counter = 0;
	
	MapType list;

	while (!myfile.eof())
	{
		myfile >> currentword;
		insertWord(myfile, list, currentword, previousword, counter);
	}
	std::string temp = "";
	insertWord(myfile, list, temp, currentword, counter);
	sortList(list);

	std::cout << "Number of distinct words: " << counter << std::endl << std::endl;

	for (auto n : list)
	{
		std::cout << n.first << " : ";
		for (auto itr = n.second.begin(); itr != n.second.end(); ++itr)
		{
			std::cout << *itr << " ";
		}
		std::cout << std::endl;
	}

	myfile.close();

	return 0;
}
