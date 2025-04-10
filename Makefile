wordinator: wordinator.c
	gcc wordinator.c -o wordinator

clean:
	rm wordinator

install:
	cp wordinator /usr/bin/wordinator
