
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include "aoc-utils.hpp"

#define INPUT "input/input13"

typedef struct s_machine
{
	std::pair<int, int> a;
	std::pair<int, int> b;
	std::pair<int, int> prize;
}	Machine;

int	get_value(std::string id, std::string del, std::string str)
{
	size_t	pos = str.find(id) + 2;

	if (del == "\0")
		return ( stoi(str.substr(pos)) );
	return ( stoi(str.substr(pos + 2, str.find(del, pos) - pos)) );
}

int	main()
{
	std::string				line;
	std::fstream			fs;
	std::vector<Machine>	machines;

	aocprint("[ aoc24-12 ]");

	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint(std::string("Failed to open file: ") + INPUT), 1);

	// load machines
	while (std::getline(fs, line))
	{
		if (line.empty())
			continue ;
		std::pair<int, int>	a, b, prize;
		a.first	 = stoi(line.substr(12,2));
		a.second = stoi(line.substr(18,2));
		std::getline(fs, line);
		b.first	 = stoi(line.substr(12,2));
		b.second = stoi(line.substr(18,2));
		std::getline(fs, line);
		prize.first	 = get_value("X", ",", line);
		prize.second = get_value("Y", "\0", line);
		machines.emplace_back((Machine){a, b, prize});
	}

	fs.close();

	return (0);
}