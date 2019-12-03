#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>

typedef std::vector<std::string> ValType;
typedef std::map<std::string, ValType> MapType;

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

void sortList(MapType& list)
{
	for (auto &n : list)
	{
		std::sort(n.second.begin(), n.second.end());
	}
}

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