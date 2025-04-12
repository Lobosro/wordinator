wordinator: wordinator.c libs/jsonw.c
	mkdir -p build
	gcc wordinator.c libs/jsonw.c -o build/wordinator

clean:
	rm -f build/*

install:
	cp build/wordinator /usr/bin/wordinator
	mkdir -p /usr/share/wordinator # NOT IMPLEMENTED IN CODE
	cp -r lang /usr/share/wordinator # NOT IMPLEMENTED IN CODE

update:
	rm -f /usr/bin/wordinator
	rm -fr /usr/share/wordinator
	cp build/wordinator /usr/bin/wordinator
	mkdir -p /usr/share/wordinator # NOT IMPLEMENTED IN CODE
	cp -fr lang /usr/share/wordinator # NOT IMPLEMENTED IN CODE

uninstall:
	rm -f /usr/bin/wordinator
	rm -fr /usr/share/wordinator

