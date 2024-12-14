CC			=	clang++
CPPFLAGS	=	-Wall -Wextra -Werror -std=c++11

01:
	$(CC) $(CPPFLAGS) riddles/01.cpp -o m && ./m

02:
	$(CC) $(CPPFLAGS) riddles/02.cpp -o m && ./m

03:
	$(CC) $(CPPFLAGS) riddles/03.cpp -o m && ./m

04:
	$(CC) $(CPPFLAGS) riddles/04.cpp -o m && ./m

05:
	$(CC) $(CPPFLAGS) riddles/05.cpp -o m && ./m

11:
	$(CC) $(CPPFLAGS) riddles/11.cpp -o m && ./m

12:
	$(CC) $(CPPFLAGS) riddles/12.cpp -o m && ./m

13:
	$(CC) $(CPPFLAGS) riddles/13.cpp -o m && ./m

fclean:
	rm -f m