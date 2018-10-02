CC = gcc 
CFlAGS = -xc -std=gnu11 -Wall -Werror -g -Og -fsanitize=address
all: main
clean:
	rm -f main *.o

main.o:main.c

snake.o: snake.c snake.h

main: snake.o main.o
	$(CC)  $(CFLAGS) -o $@ $^ `pkg-config --cflags --libs ncurses`
