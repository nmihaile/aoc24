
#include <iostream>
#include <string>
#include <fstream>
#include "aoc-utils.hpp"

#define INPUT "input/input06"

typedef std::vector<std::vector<char>>	Map;

typedef struct s_vec2
{
	int x;
	int y;
}	vec2;

typedef struct s_guard
{
	vec2	p;
	vec2	d;
} 	Guard;

void	printmap(Map& map)
{
	int steps = 0;
	for (std::vector<char> line : map)
	{
		for (char c : line)
		{
			if (c == 'X')
				++steps;
			std::cout << c;
		}
		std::cout << std::endl;
	}
		std::cout << steps << std::endl;
}

Guard	getGuard(Map& map)
{
	for (int y = 0; y < static_cast<int>(map.size()); ++y)
		for (int x = 0; x < static_cast<int>(map[y].size()); ++x)
		{
			if (map[y][x] == '^')
				return {{x,y},{0,-1}};
		}
	return {{0,0},{0,-1}};
}

bool	is_outside(vec2 p, vec2& ms)
{
	if (p.x < 0 || p.y < 0 || p.x >= ms.x || p.y >= ms.y)
		return (true);
	return (false);
}

bool	is_obstical(vec2& p, Map& map)
{
	if (map[p.y][p.x] == '#')
		return (true);
	return (false);
}

bool	move(Map& map, Guard& guard, vec2& ms)
{
	vec2	np = {guard.p.x + guard.d.x,
				  guard.p.y + guard.d.y};

	if (is_outside(np, ms))
	{
		map[guard.p.y][guard.p.x] = 'X';
		return (false);
	}

	if (is_obstical(np, map))
	{
		if 		(guard.d.x == 0 && guard.d.y==-1) { guard.d.x = 1; guard.d.y = 0; }
		else if (guard.d.x == 1 && guard.d.y== 0) { guard.d.x = 0; guard.d.y = 1; }
		else if (guard.d.x == 0 && guard.d.y== 1) { guard.d.x =-1; guard.d.y = 0; }
		else if (guard.d.x ==-1 && guard.d.y== 0) { guard.d.x = 0; guard.d.y =-1; }
		return (true);
	}
	map[guard.p.y][guard.p.x] = 'X';
	guard.p.x += guard.d.x;
	guard.p.y += guard.d.y;
	return (true);
}

int	countGuardedPos(Map& map)
{
	int steps = 0;
	for (std::vector<char> line : map)
	{
		for (char c : line)
		{
			if (c == 'X')
				++steps;
		}
	}
	return (steps);
}

int	main()
{
	std::string		line;
	std::fstream	fs;
	Map				map;
	Guard			guard;
	vec2			map_size = {0,0};

	aocprint("[ aoc24-06 ]");

	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(INPUT)), 1);

	// load the map
	while (std::getline(fs, line))
	{
		++map_size.y;
		map.emplace_back(line.begin(), line.end());
	}
	map_size.x = map[0].size();
	guard = getGuard(map);
	fs.close();

	while (move(map, guard, map_size))
		;


	int q1_steps = countGuardedPos(map);
	// printmap(map);
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << q1_steps << RESET << std::endl;


	return (0);
}
