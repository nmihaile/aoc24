
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>


void	aocprint(std::string str)
{
	std::cout << str << std::endl;
}

int main(int ac, char **av)
{
	std::string	line;
	std::fstream fs;
	std::vector<std::vector<int>>	reports;

	aocprint("aoc24-02");
	if (ac != 2)
		return (aocprint("Provide Input file"), 1);
	
	fs.open(av[1]);

	// Parsinge
	int i = 0;
	while (std::getline(fs, line))
	{
		std::istringstream is(line);
		reports.push_back(std::vector<int>());
		int n;
		while (is >> n)
			reports[i].push_back(n);
		i++;
	}

	// Printing
	for (std::vector<int>& row : reports)
	{
		for (int& it : row)
			std::cout << it << " ";
		aocprint("");
	}

	// check for valid reports
	for (std::vector<int>& row : reports)
	{
		bool valid = true;
		for (int& it : row)
		{
			valid = true;
			std::cout << it << " ";
		}
		aocprint("");
	}

	fs.close();

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input