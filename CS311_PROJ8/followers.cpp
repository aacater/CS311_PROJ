// followers.h
// Alex Cater, Kurt Nunn, Christopher Seamount
// 2019-12-03
//
// For CS 311 Fall 2019
// Source File for Project 8, Exercise A

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>

typedef std::vector<std::string> ValType;
typedef std::map<std::string, ValType> MapType;

// prints stats about list
//		number of distinct words and key + values
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

// sorts values for each key
void sortList(MapType& list)
{
	for (auto &n : list)
	{
		std::sort(n.second.begin(), n.second.end());
	}
}

// inserts a word into list based on the word it followed
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

// read a file and properly create list
MapType makeList(std::ifstream& myfile)
{
	MapType list;
	std::string currentword = "";
	std::string previousword = "";

	myfile >> previousword;
	while (myfile)
	{
		if (myfile.eof())
		{
			break;
		}
		myfile >> currentword;
		insertWord(list, currentword, previousword);
	}
	std::string temp = "";
	insertWord(list, temp, currentword);
	sortList(list);

	return list;
}

// userPause
// Wait for user to press ENTER: read all chars through first newline.
void userPause()
{
	std::cout.flush();
	while (std::cin.get() != '\n');
}

// Main of file
// opens and creates list of followers from contents
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
		std::cout << "Press ENTER to quit ";
		userPause();
		return -1;
	}

	MapType list = makeList(myfile);

	printList(list);

	myfile.close();

	// Wait for user
	std::cout << "Press ENTER to quit ";
	userPause();

	return 0;
}