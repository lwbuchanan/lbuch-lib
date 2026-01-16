CC=gcc


mkdir:
	mkdir -p bin

test_darray: mkdir
	$(CC) test/test_darray.c -o bin/test_darray
	./bin/test_darray

install:
	sudo mkdir -p /usr/local/include/lbuch
	sudo cp *.h /usr/local/include/lbuch
