
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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

typedef std::vector<std::vector<char>>	Garden;

void	aocprint(std::string str)
{
	std::cout << str << std::endl;
}

void	print_garden(Garden garden)
{
	for (size_t y = 0; y < garden.size(); y++)
	{
		for (size_t x = 0; x < garden[y].size(); x++)
			std::cout << garden[y][x];
		std::cout << std::endl;
	}
}

size_t	calc(Garden& garden, int x, int y, int sx, int sy, char plant, size_t& area)
{
	if (x < 0 || y < 0 || x >= sx || y >= sy)
		return (1);

	size_t	perim	= 0;
	char	curr	= garden[y][x];

	if (islower(curr) && toupper(curr) == plant)
		return (0);
	if (curr != plant)
		return (1);

	garden[y][x] = tolower(curr);
	++area;

	perim += calc(garden, x - 1, y    , sx, sy, plant, area);
	perim += calc(garden, x    , y - 1, sx, sy, plant, area);
	perim += calc(garden, x + 1, y    , sx, sy, plant, area);
	perim += calc(garden, x    , y + 1, sx, sy, plant, area);

	return (perim);
}

int	main(int ac, char **av)
{
	std::string		line;
	std::fstream	fs;
	Garden			garden;

	aocprint("[ aoc24-12 ]");

	if (ac != 2)
		return (aocprint("Provide Input file"), 1);
	
	fs.open(av[1]);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(av[1])), 1);

	// Load map
	size_t y = 0;
	while (std::getline(fs, line))
	{
		garden.emplace_back(std::vector<char>());
		for (size_t x = 0; x < line.length(); ++x)
			garden[y].emplace_back(line[x]);
		++y;
	}
	fs.close();

	// Print Garden
	// print_garden(garden);

	// q1 - calc fence price
	size_t price = 0;
	size_t sx = garden[0].size();
	size_t sy = garden.size();
	for (size_t y = 0; y < sy; ++y)
	{
		for (size_t x = 0; x < sx; ++x)
		{
			if (isupper(garden[y][x]))
			{
				size_t area = 0;
				size_t perim = calc(garden, x, y, sx, sy, garden[y][x], area);
				price += perim * area;
			}
		}
	}
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << price << RESET << std::endl;


	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input