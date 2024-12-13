CC			=	clang++
CPPFLAGS	=	-Wall -Wextra -Werror -std=c++11

01:
	$(CC) $(CPPFLAGS) riddles/01.cpp -o m && ./m

13:
	$(CC) $(CPPFLAGS) riddles/13.cpp -o m && ./m

fclean:
	rm -f m