CC=gcc

.PHONY: mkdir
mkdir:
	mkdir -p bin

.PHONY: test
test: mkdir
	$(CC) -g test/test.c -o bin/test
	./bin/test

.PHONY: install
install:
	sudo mkdir -p /usr/local/include/lbuch
	sudo cp *.h /usr/local/include/lbuch
