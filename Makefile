all: build wordinator


build:
	mkdir -p build

wordinator: wordinator.c
	gcc wordinator.c -o build/wordinator

clean:
	rm build/*

install:
	cp wordinator /usr/bin/wordinator
