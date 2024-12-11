
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

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

typedef unsigned long		Stone;
typedef std::vector<Stone> 	Stones;

void aocprint(std::string str)
{
	std::cout << str << std::endl;
}

void	strip_zeros(std::string& str)
{
	unsigned long n = std::stoul(str);
	str = std::to_string(n);
}

void	blink(Stones &stones)
{
	Stones nstones;
	for (Stone& stone : stones)
	{
		if (stone == 0)
		{
			nstones.emplace_back(1);
			continue ;
		}

		std::string str(std::to_string(stone));
		strip_zeros(str);
		size_t len = str.length();
		if (len % 2 == 0)
		{
			len /= 2;
			std::string s = str.substr(0, len);
			strip_zeros(s);
			nstones.emplace_back(std::stoul(s));

			s = str.substr(len, len);
			strip_zeros(s);
			nstones.emplace_back(std::stoul(s));
			continue ;
		}

		nstones.emplace_back(stone * 2024);
	}
	stones = nstones;
}

int	main(int ac, char **av)
{
	std::string		str;
	std::fstream	fs;
	Stones			stones;
	Stones			stones2;

	if (ac != 2)
		return (aocprint("Provide Input file"), 1);
	
	fs.open(av[1]);
	if (fs.is_open() == false)
		return (aocprint("Failed to open file: " + std::string(av[1])), 1);

	while (std::getline(fs, str, ' '))
	{
		unsigned long n = std::stoul(str);
		stones.emplace_back(n);
	}
	
	stones2 = stones;

	for (int i = 0; i < 25; i++)
		blink(stones);
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << stones.size() << RESET << std::endl;

	for (int i = 0; i < 75; i++)
		blink(stones2);
	std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << stones2.size() << RESET << std::endl;

	// Print 
	// for (Stone& stone : stones)
	// 	std::cout << std::setw(10) << stone.first << " | " << std::setw(10) << stone.second << std::endl;

	fs.close();

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input