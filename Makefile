queens: queens.c
	gcc -Wall -Werror -fsanitize=address -o queens queens.c

clean:
	rm -f queens
