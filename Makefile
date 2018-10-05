hash: hash.o cmdlist.o pathvar.o
	gcc -o hash hash.o cmdlist.o pathvar.o

hash.o: hash.c
	gcc -O -Wall -Werror -c hash.c

cmdlist.o: utils/cmdlist.c
	gcc -O -Wall -Werror -c utils/cmdlist.c

pathvar.o: utils/pathvar.c
	gcc -O -Wall -Werror -c utils/pathvar.c

clean:
	rm -f hash.o cmdlist.o hash
