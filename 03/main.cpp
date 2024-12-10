#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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

size_t	get_next_do(std::string str, size_t pos)
{
	return ( str.find("do()", pos));
}

size_t	get_next_dont(std::string str, size_t pos)
{
	return ( str.find("don't()", pos));
}

int	main(int ac, char **av)
{
	std::string	line;
	std::string str;
	std::fstream fs;

	aocprint("[ aoc24-03 ]");
	if (ac != 2)
		return (aocprint("Provide Input file"), 1);
	
	// load data from file
	fs.open(av[1]);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(av[1])), 1);
	while (std::getline(fs, line))
		str += line;
	fs.close();
	

	// find all valid mul(xxx,xxx)	
	size_t	sum = 0;
	size_t pos = 0;
	while ((pos = str.find("mul", pos)) != std::string::npos)
	{
		if (str[pos + 3] != '(')
		{
			pos += 4;
			continue ;
		}
		pos += 4;
		size_t	end = pos;
		while (std::isdigit(str[end]))
			end++;
		std::string n1 = str.substr(pos, end - pos);
		pos = end;
		if (str[pos] != ',')
		{
			pos++;
			continue ;
		}
		end = ++pos;
		while (std::isdigit(str[end]))
			end++;
		std::string n2 = str.substr(pos, end - pos);
		pos = end;
		if (str[pos] != ')')
		{
			pos++;
			continue ;
		}

		sum += std::stoi(n1) * std::stoi(n2);

		pos++;
		if (str[pos] == '\0')
			break ;
	}
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << sum << RESET << std::endl;


	// #####################################
	// #####################################


	// find only enabled by do() mul(xxx,xxx)
	size_t	sum2 = 0;
	pos = 0;
	size_t dont = get_next_dont(str, pos);
	while ((pos = str.find("mul", pos)) != std::string::npos)
	{
		if (dont != std::string::npos && pos > dont)
		{
			pos = get_next_do(str, dont);
			dont = get_next_dont(str, pos);
			continue ;
		}
		if (str[pos + 3] != '(')
		{
			pos += 4;
			continue ;
		}
		pos += 4;
		size_t	end = pos;
		while (std::isdigit(str[end]))
			end++;
		std::string n1 = str.substr(pos, end - pos);
		pos = end;
		if (str[pos] != ',')
		{
			pos++;
			continue ;
		}
		end = ++pos;
		while (std::isdigit(str[end]))
			end++;
		std::string n2 = str.substr(pos, end - pos);
		pos = end;
		if (str[pos] != ')')
		{
			pos++;
			continue ;
		}

		sum2 += std::stoi(n1) * std::stoi(n2);

		pos++;
		if (str[pos] == '\0')
			break ;
	}
	std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << sum2 << RESET << std::endl;

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input