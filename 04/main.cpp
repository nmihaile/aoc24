
#include <iostream>
#include <fstream>
#include "aoc-util.hpp"

typedef std::vector<std::vector<char>> Puzzle;

void	print_puzzle(Puzzle& puzzle)
{
	for (const std::vector<char>& line : puzzle)
	{
		for (char c : line)
			std::cout << c;
		std::cout << std::endl;
	}
}

bool	search(Puzzle& puzzle, int dx, int dy, std::string word)
{
	return (true);
}

int	main(int ac, char **av)
{
	std::string		line;
	std::fstream	fs;

	Puzzle	puzzle;

	aocprint("[ aoc24-04 ]");
	if (ac != 2)
		return (aocprint("Provide Input file"), 1);

	fs.open(av[1]);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(av[1])), 1);

	// Load input
	while (std::getline(fs, line))
		puzzle.emplace_back(line.begin(), line.end());

	fs.close();

	print_puzzle(puzzle);

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input