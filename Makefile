# Makefile pentru jocul 2048

build: 2048

2048: 2048.c colors.o dimensiune.o mutari.o saves.o settime.o utilitare.o
	gcc -Wall colors.o dimensiune.o mutari.o saves.o settime.o utilitare.o 2048.c -o 2048 -lcurses

utilitare: utilitare.c
	gcc -Wall -c utilitare.c

mutari: mutari.c
	gcc -Wall -c mutari.c

dimensiune: dimensiune.c
	gcc -Wall -c dimensiune.c

colors: colors.c
	gcc -Wall -c colors.c

saves: saves.c
	gcc -Wall -c saves.c

setttime: settime.c
	gcc -Wall -c settime.c

.PHONY:

clean:
	rm -f 2048 *.o

memcheck: build
	valgrind --leak-check=full --show-leak-kinds=all ./2048

run: build
	./2048