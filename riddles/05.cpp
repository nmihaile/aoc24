
#include <iostream>
#include <fstream>
#include <vector>
#include "aoc-utils.hpp"

#define INPUT "input/input05"

typedef std::pair<int,int>	Rule;
typedef std::vector<Rule>	Rules;
typedef std::vector<int>	Update;
typedef std::vector<Update>	Updates;

bool	is_valid_order(int& p1, int& p2, Rules& rules)
{
	for (Rule& rule : rules)
		if (rule.first == p2 && rule.second == p1)
			return (false);
	return (true);
}

bool	is_valid_update(Update& update, Rules& rules)
{
	for (size_t i = 0; i < update.size() - 1; ++i)
	{
		if (!is_valid_order(update[i], update[i + 1], rules))
			return (false);
	}
	return (true);
}

void	reorder(Update& update, Rules& rules)
{
	for (size_t i = 0; i < update.size() - 1; ++i)
	{
		if (!is_valid_order(update[i], update[i + 1], rules))
		{
			std::swap(update[i], update[i + 1]);
			i = -1;
		}
	}
}

int	main(void)
{
	std::string		line;
	std::fstream	fs;
	Rules			rules;
	Updates			updates;

	aocprint("[ aoc24-05 ]");

	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(INPUT)), 1);

	// Load Rules
	while (std::getline(fs, line))
	{
		if (line[0] == '\0') break ;
		rules.emplace_back(std::stoi(line.substr(0,2)), std::stoi(line.substr(3,2)));
	}
	// Load updates
	int i = 0;
	while (std::getline(fs, line))
	{
		updates.emplace_back(std::vector<int>());
		int pos = 0;
		while (line[pos])
		{
			updates[i].emplace_back(std::stoi(line.substr(pos, 2)));
			pos += 2;
			if (line[pos] == '\0')
				break ;
			++pos;
		}
		++i;
	}
	fs.close();

	
	// q1 - check updates and sum middle page
	// q2 - reorder invalid updates and sum middle page
	size_t	q1_middle_pages = 0;
	size_t	q2_middle_pages = 0;
	for (Update& update : updates)
	{
		if (is_valid_update(update, rules))
			q1_middle_pages += update[update.size() / 2];
		else
		{
			reorder(update, rules);
			q2_middle_pages += update[update.size() / 2];
		}
	}
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << q1_middle_pages << RESET << std::endl;
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << q2_middle_pages << RESET << std::endl;

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input
// make 05