all: run
	./mycat

run: mycat.c
	gcc -o mycat mycat.c

clean:
	rm *.o

