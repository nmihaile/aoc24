
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

typedef std::pair<std::string, unsigned long>	Stone;
typedef std::vector<Stone> 			Stones;

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
		if (stone.second == 0)
		{
			nstones.emplace_back("1", 1);
			continue ;
		}

		size_t len = stone.first.length();
		if (len % 2 == 0)
		{
			len /= 2;
			std::string str = stone.first.substr(0, len);
			strip_zeros(str);
			nstones.emplace_back(str, std::stoul(str));

			str = stone.first.substr(len, len);
			strip_zeros(str);
			nstones.emplace_back(str, std::stoul(str));
			continue ;
		}

		// unsigned long n = std::stoul(stone.first);
		unsigned long n = stone.second * 2024;
		nstones.emplace_back(std::to_string(n), n);
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
		stones.emplace_back(std::to_string(n), n);
	}
	
	stones2 = stones;

	for (int i = 0; i < 25; i++)
		blink(stones);
	std::cout << BLUE << "Answer 01: " << LIGHTYELLOW << BOLD << stones.size() << RESET << std::endl;

	// for (int i = 0; i < 75; i++)
	// 	blink(stones2);
	// std::cout << BLUE << "Answer 02: " << LIGHTYELLOW << BOLD << stones2.size() << RESET << std::endl;

	// Print 
	// for (Stone& stone : stones)
	// 	std::cout << std::setw(10) << stone.first << " | " << std::setw(10) << stone.second << std::endl;

	fs.close();

	return (0);
}

// clang++ -Wall -Wextra -Werror -std=c++11  main.cpp && ./a.out input