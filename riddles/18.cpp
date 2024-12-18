
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

void	dfs(Mem& mem, vec2 p, const int& MemSize, int count)
{
	if (p.x < 0 || p.y < 0 || p.x > MemSize - 1 || p.y > MemSize - 1 || mem[p.y][p.x] == -2)
		return ;
	if (mem[p.y][p.x] <= count)
		return ;
	mem[p.y][p.x] = count++;
	dfs(mem, vec2{p.x + 1,p.y    }, MemSize, count);
	dfs(mem, vec2{p.x    ,p.y + 1}, MemSize, count);
	dfs(mem, vec2{p.x - 1,p.y    }, MemSize, count);
	dfs(mem, vec2{p.x    ,p.y - 1}, MemSize, count);
}

int	main()
{
	std::string		line;
	std::fstream	fs;
	Mem				mem;

	aocprint("[ aoc24-12 ]");
	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint(std::string("Failed to open file: ") + INPUT), 1);

	const int MemSize = 71;

	for (int y = 0; y <= MemSize - 1; ++y)
		mem.emplace_back(MemSize, INT_MAX);


	while (std::getline(fs, line))
	{
		static int c;
		++c;
		size_t pos = line.find(",");
		int x = std::stoi(line.substr(0,pos));
		int y = std::stoi(line.substr(pos+1));
		// std::cout << x << "," << y << std::endl;
		mem[y][x] = -2;
		if (c == 1024)
			break;
	}
	fs.close();

	// printmem(mem);

	dfs(mem, vec2{0,0}, MemSize, 0);
	// printval(mem);
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << mem[MemSize - 1][MemSize - 1] << RESET << std::endl;

	return (0);
}