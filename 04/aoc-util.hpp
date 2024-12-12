#ifndef AOC_UTIL_HPP
#define AOC_UTIL_HPP

#include <iostream>
#include <string>

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

#endif