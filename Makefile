UTIL = Lista.c 
MAIN = main.c
BINARY = bin_proj

all:
	gcc -Wall -Werror -g $(UTIL) $(MAIN) -o $(BINARY) -lm

optim:
	gcc -Wall -Werror -g -O3 $(UTIL) $(MAIN) -o $(BINARY) -lm

run:
	./$(BINARY)
	
debug:
	gcc -DDEBUG -Wall $(MAIN) $(UTIL) -o $(BINARY) -lm

valgrind:
	valgrind -s --tool=memcheck --leak-check=full  --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BINARY)

zip:
	zip 13687108.zip *.c *.h *.pdf Makefile

clean:
	@rm *.o