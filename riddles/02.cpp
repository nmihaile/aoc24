
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#define INPUT "input/input02"

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

void	aocprint(std::string str)
{
	std::cout << str << std::endl;
}

bool	is_valid_row(std::vector<int>& row)
{
	int	dir = row[1] - row[0];
	if (dir == 0) 
		return (false);

	dir = dir / std::abs(dir);
	int last = -1;

	for (int& it : row)
	{
		if (last == -1)
		{
			last = it;
			continue ;
		}
		if (dir > 0)
		{
			if (last == it || last < it - 3 || last > it)
				return (false);
		}
		else
		{
			if (last == it || last > it + 3 || last < it)
			return (false);
		}
		last = it;
	}
	return (true);
}

int main()
{
	std::string	line;
	std::fstream fs;
	std::vector<std::vector<int>>	reports;

	aocprint("[ aoc24-02 ]");
	
	fs.open(INPUT);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(INPUT)), 1);

	// Parsinge
	int i = 0;
	while (std::getline(fs, line))
	{
		std::istringstream is(line);
		reports.push_back(std::vector<int>());
		int n;
		while (is >> n)
			reports[i].push_back(n);
		i++;
	}

	// Printing
	// for (std::vector<int>& row : reports)
	// {
	// 	for (int& it : row)
	// 		std::cout << it << " ";
	// 	aocprint("");
	// }

	// check for valid reports
	int	valid_reports = 0;
	for (std::vector<int>& row : reports)
	{
		if (is_valid_row(row))
			valid_reports++;
	}
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << valid_reports << RESET << std::endl;

	// check for valid altered reports
	int	altered_valid_reports = 0;
	for (std::vector<int>& row : reports)
	{
		if (is_valid_row(row))
			altered_valid_reports++;
		else
		{
			for (size_t i = 0; i < row.size(); i++)
			{
				std::vector<int> r = row;
				r.erase(r.begin() + i);
				if (is_valid_row(r))
				{
					altered_valid_reports++;
					break ;
				}
			}
		}
	}
	std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << altered_valid_reports << RESET << std::endl;

	fs.close();

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input
// make 02