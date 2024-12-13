
#include <iostream>
#include <fstream>
#include <vector>
#include "aoc-utils.hpp"

#define INPUT "input/input05"

typedef std::pair<int,int>				Rule;
typedef std::vector<Rule>				Rules;
typedef std::vector<std::vector<int>>	Updates;

int	main(void)
{
	std::string		line;
	std::fstream	fs;
	Rules			rules;
	Updates			updates;

	aocprint("[ aoc24-05 ]");

	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(INPUT)), 1);

	// Load Rules
	while (std::getline(fs, line))
	{
		if (line[0] == '\0') break ;
		rules.emplace_back(std::stoi(line.substr(0,2)), std::stoi(line.substr(3,2)));
	}
	// Load updates
	int i = 0;
	while (std::getline(fs, line))
	{
		updates.emplace_back(std::vector<int>());
		int pos = 0;
		while (line[pos])
		{
			updates[i].emplace_back(std::stoi(line.substr(pos, 2)));
			pos += 2;
			if (line[pos] == '\0')
				break ;
			++pos;
		}
		++i;
	}

	fs.close();

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input