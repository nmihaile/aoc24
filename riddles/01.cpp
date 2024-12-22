
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unistd.h> 
#include <cmath>
#include "aoc-utils.hpp"

#define INPUT "input/input01"

int main()
{
	std::fstream 		fs;
	std::string 		line;
	std::vector<std::vector<int>>	stacks(2);
	// {
	// 	{1, 2, 4, 5, 6, 7, 8, 9},	// left col
	// 	{6, 3, 4, 4, 7, 8, 8, 3}	// right col
	// }
	size_t dist = 0;	// distance for question 01
	size_t simi = 0;	// similarity for question 02

	aocprint("[ aoc24-01 ]");

	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint(std::string("Failed to open file: ") + INPUT), 1);


	// load the data
	while (std::getline(fs, line))
	{
		std::istringstream is(line);
		int left, right;
		is >> left >> right;
		stacks[0].push_back(left);
		stacks[1].push_back(right);
	}

	// print the data
	// {int i = 0;
	// while (stacks[0][i])
	// {
	// 	std::cout << stacks[0][i] << " - " << stacks[1][i] << std::endl;
	// 	i++;
	// 	usleep(1000000);
	// }}

	// Sort the data
	std::sort( stacks[0].begin(), stacks[0].end() );
	std::sort( stacks[1].begin(), stacks[1].end() );

	// calculate the distance
	for (size_t i = 0; i < stacks[0].size(); ++i)
		dist += std::abs(stacks[0][i] - stacks[1][i]);
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << dist << RESET << std::endl;

	// calculate the similarity
	for (size_t i = 0; i < stacks[0].size(); ++i )
	{
		int count = 0;
		for (size_t j = 0; j < stacks[0].size(); ++j)
		{
			if (stacks[0][i] == stacks[1][j])
				count++;
		}
		simi += stacks[0][i] * count;
	}
	std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << simi << RESET << std::endl;

	fs.close();

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input
// make 01