
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include "aoc-utils.hpp"

#define INPUT "input/input18"

typedef struct svec2
{
	int	x;
	int	y;
}	vec2;

typedef std::vector<std::vector<int>>	Mem;

void	printmem(Mem& mem)
{
	for (std::vector<int> line : mem)
	{
		for (int c : line)
			if (c == -2)
				std::cout << '#';
			else
				std::cout << '.';
		std::cout << std::endl;
	}
}

void	printmem(Mem& mem, vec2 p)
{
	for (size_t y = 0; y < mem.size(); ++y)
	{
		for (size_t x = 0; x < mem[y].size(); ++x)
		{
			if ((int)x == p.x && (int)y == p.y)
				std::cout << LIGHTRED;
			if (mem[y][x] == -2)
				std::cout << '#';
			else
				std::cout << '.';
			if ((int)x == p.x && (int)y == p.y)
				std::cout << RESET;

		}
		std::cout << std::endl;
	}
}

void	printval(Mem& mem)
{
	for (std::vector<int> line : mem)
	{
		for (int c : line)
			if (c == -2)
				std::cout << " # ";
			else if (c == INT_MAX)
				std::cout << " _ ";
			else
			std::cout << std::setw(2) << c << ' ';
		std::cout << std::endl;
	}
}

void	clearmem(Mem& mem)
{
	for (size_t y = 0; y < mem.size(); ++y)
		for (size_t x = 0; x < mem[y].size(); ++x)
			if (mem[y][x] > -2)
				mem[y][x] = INT_MAX;
}

void	floodfill(Mem& mem, vec2 p, const int& MemSize, int count)
{
	// Nice optimisation right here:
	if (mem[MemSize - 1][MemSize - 1] < INT_MAX)
		return ;
	if (p.x < 0 || p.y < 0 || p.x > MemSize - 1 || p.y > MemSize - 1 || mem[p.y][p.x] == -2)
		return ;
	if (mem[p.y][p.x] <= count)
		return ;
	mem[p.y][p.x] = count++;
	floodfill(mem, vec2{p.x + 1,p.y    }, MemSize, count);
	floodfill(mem, vec2{p.x    ,p.y + 1}, MemSize, count);
	floodfill(mem, vec2{p.x - 1,p.y    }, MemSize, count);
	floodfill(mem, vec2{p.x    ,p.y - 1}, MemSize, count);
}

int	main()
{
	std::string			line;
	std::fstream		fs;
	Mem					mem;
	std::vector<vec2>	blocks;

	aocprint("[ aoc24-12 ]");
	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint(std::string("Failed to open file: ") + INPUT), 1);

	const int MemSize = 70 + 1;
	const int FALLEN_BYTES = 1024; // 1024
	// const int MemSize = 6 + 1;
	// const int FALLEN_BYTES = 12;

	for (int y = 0; y <= MemSize - 1; ++y)
		mem.emplace_back(MemSize, INT_MAX);


	while (std::getline(fs, line))
	{
		static int c;
		++c;
		size_t pos = line.find(",");
		vec2	v;
		v.x = std::stoi(line.substr(0,pos));
		v.y = std::stoi(line.substr(pos+1));
		// std::cout << x << "," << y << std::endl;
		if (c <= FALLEN_BYTES)
			mem[v.y][v.x] = -2;
		blocks.emplace_back(v);
	}
	fs.close();

	// printmem(mem);

	// Q1: find steps
	floodfill(mem, vec2{0,0}, MemSize, 0);
	// printval(mem);
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << mem[MemSize - 1][MemSize - 1] << RESET << std::endl;

	// Q2: find first blocking mem block
	// but kinda slow
	for (size_t i = FALLEN_BYTES; i < blocks.size(); ++i)
	{
		mem[blocks[i].y][blocks[i].x] = -2;
		clearmem(mem);
		floodfill(mem, vec2{0,0}, MemSize, 0);

		if (mem[MemSize - 1][MemSize - 1] == INT_MAX)
		{
			std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << blocks[i].x << "," << blocks[i].y << RESET << std::endl;		
			return (0);
		}
	}

	return (0);
}