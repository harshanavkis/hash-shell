hash: hash.o cmdlist.o
	gcc -o hash hash.o cmdlist.o

hash.o: hash.c
	gcc -O -Wall -Werror -c hash.c

cmdlist.o: utils/cmdlist.c
	gcc -O -Wall -Werror -c utils/cmdlist.c

clean:
	rm -f hash.o cmdlist.o hash
