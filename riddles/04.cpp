
#include <iostream>
#include <fstream>
#include "aoc-utils.hpp"

#define INPUT "input/input04"

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

int	search_mas(Puzzle& puzzle, int x, int y, int w, int h)
{
	if ( (search(puzzle, x-1,y-1, 1,1, w,h, std::string("MAS")) || search(puzzle, x+1,y+1, -1,-1, w,h, std::string("MAS")))
			&&
		 (search(puzzle, x-1,y+1, 1,-1, w,h, std::string("MAS")) || search(puzzle, x+1,y-1, -1,1, w,h, std::string("MAS"))) )
		 	return (1);
	return (0);
}

int	main()
{
	std::string		line;
	std::fstream	fs;

	Puzzle	puzzle;

	aocprint("[ aoc24-04 ]");

	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(INPUT)), 1);

	// Load input
	while (std::getline(fs, line))
		puzzle.emplace_back(line.begin(), line.end());

	fs.close();

	// print_puzzle(puzzle);

	// Q1: count words in puzzle
	size_t	count_q1 = 0;
	int h = static_cast<int>(puzzle.size());
	int w = static_cast<int>(puzzle[0].size());
	for (int y = 0; y < h; ++y)
		for (int x = 0; x < w; ++x)
		{
			count_q1 += search(puzzle, x, y, -1,  0, w, h, "XMAS");
			count_q1 += search(puzzle, x, y,  1,  0, w, h, "XMAS");
			count_q1 += search(puzzle, x, y,  0, -1, w, h, "XMAS");
			count_q1 += search(puzzle, x, y,  0,  1, w, h, "XMAS");
			count_q1 += search(puzzle, x, y, -1, -1, w, h, "XMAS");
			count_q1 += search(puzzle, x, y,  1, -1, w, h, "XMAS");
			count_q1 += search(puzzle, x, y, -1,  1, w, h, "XMAS");
			count_q1 += search(puzzle, x, y,  1,  1, w, h, "XMAS");
		}
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << count_q1 << RESET << std::endl;


	// Q2: count crosed-MAS words in puzzle
	size_t	count_q2 = 0;
	for (int y = 0; y < h; ++y)
		for (int x = 0; x < w; ++x)
			count_q2 += search_mas(puzzle, x, y, w, h);
	std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << count_q2 << RESET << std::endl;


	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input
// make 04