CC=gcc

edge_extractor.out: main.c lodepng.c
	$(CC) $^ -o $@ -lm

run: 
	./edge_extractor.out

clean:
	rm *.out
