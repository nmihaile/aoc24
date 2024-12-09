
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unistd.h> 
#include <cmath>

#define BG				"\033[48;5;4m"
#define LIGHTRED		"\033[91m"
#define LIGHTGREEN		"\033[92m"
#define LIGHTYELLOW		"\033[93m"
#define BLUE			"\033[34m"
#define LIGHTBLUE		"\033[94m"
#define LIGHTMAGENTA	"\033[95m"
#define LIGHTCYAN		"\033[96m"
#define RESET			"\033[0m"
#define BOLD			"\033[1m"

void	myprint(std::string str)
{
	std::cout << str << std::endl;
}

int main(int ac, char **av)
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

	if (ac != 2)
		return (myprint("Provide Input file"), 0);

	fs.open(av[1]);
	if (fs.is_open() == false)
		return (myprint("Failed to open file: " + std::string(av[1])), 1);


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
	{int i = 0;
	while (stacks[0][i])
	{
		dist += std::abs(stacks[0][i] - stacks[1][i]);
		i++;
	}}
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << dist << RESET << std::endl;

	// calculate the similarity
	{int i = 0;
	while (stacks[0][i])
	{
		int j = 0;
		int count = 0;
		while (stacks[1][j])
		{
			if (stacks[0][i] == stacks[1][j++])
				count++;
		}
		simi += stacks[0][i] * count;
		i++;
	}}
	std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << simi << RESET << std::endl;

	fs.close();

	return (0);
}
