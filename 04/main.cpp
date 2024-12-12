
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

bool	search(Puzzle& puzzle, int x, int y, int dx, int dy, int w, int h, std::string word)
{
	if (x < 0 || y < 0 || x >= w || y >= h)
		return (false);
	if (word.length() == 1)
	{
		if (puzzle[y][x] == word[0])
			return (true);
		return (false);
	}
	if (puzzle[y][x] == word[0])
		return ( search(puzzle, x + dx, y + dy, dx, dy, w, h, word.substr(1)) );
	return (false);
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

	// print_puzzle(puzzle);

	// Q1: count words in puzzle
	size_t	count = 0;
	int h = static_cast<int>(puzzle.size());
	int w = static_cast<int>(puzzle[0].size());
	for (int y = 0; y < h; ++y)
		for (int x = 0; x < w; ++x)
		{
			count += search(puzzle, x, y, -1,  0, w, h, "XMAS");
			count += search(puzzle, x, y,  1,  0, w, h, "XMAS");
			count += search(puzzle, x, y,  0, -1, w, h, "XMAS");
			count += search(puzzle, x, y,  0,  1, w, h, "XMAS");
			count += search(puzzle, x, y, -1, -1, w, h, "XMAS");
			count += search(puzzle, x, y,  1, -1, w, h, "XMAS");
			count += search(puzzle, x, y, -1,  1, w, h, "XMAS");
			count += search(puzzle, x, y,  1,  1, w, h, "XMAS");
		}
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << count << RESET << std::endl;

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input