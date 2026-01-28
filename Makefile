wordinator: wordinator.c libs/jsonw.c
	mkdir -p build
	gcc wordinator.c libs/jsonw.c -o build/wordinator

clean:
	rm -f build/*

UNAME_S := $(shell uname)
BIN_DIR := /usr/local/bin
ifeq ($(UNAME_S),Darwin)
	ASSETS_DIR := ~/Library/Application\ Support/wordinator
else
	ASSETS_DIR := /usr/share/wordinator
endif

install:
	sudo cp build/wordinator $(BIN_DIR)
ifeq ($(UNAME_S),Darwin)
		mkdir -p $(ASSETS_DIR)
else
		sudo mkdir -p $(ASSETS_DIR)
endif
ifeq ($(UNAME_S),Darwin)
		cp -r lang $(ASSETS_DIR)/
else
		sudo cp -r lang $(ASSETS_DIR)/
endif
	@echo "Wordinator was correctly installed!"

update:
	sudo rm -f /usr/local/bin/wordinator
ifeq ($(UNAME_S),Darwin)
	rm -rf $(HOME)/Library/Application\ Support/wordinator
	cp build/wordinator $(BIN_DIR)
	mkdir -p $(HOME)/Library/Application\ Support/wordinator
	cp -r lang $(HOME)/Library/Application\ Support/wordinator/
else
	sudo rm -rf /usr/share/wordinator
	cp build/wordinator $(BIN_DIR)
	sudo mkdir -p /usr/share/wordinator
	sudo cp -r lang /usr/share/wordinator/
endif
	@echo "Wordinator updated!"

uninstall:
	sudo rm -f /usr/local/bin/wordinator
ifeq ($(UNAME_S),Darwin)
	rm -rf $(HOME)/Library/Application\ Support/wordinator
else
	sudo rm -rf /usr/share/wordinator
endif
	@echo "Wordinator uninstalled!"
