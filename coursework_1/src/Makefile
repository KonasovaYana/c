all: cw

cw: cw.o actions_with_sentences.o main_functions.o stuctures_discribe.o
	gcc cw.o actions_with_sentences.o main_functions.o stuctures_discribe.o -o cw

cw.o: cw.c actions_with_sentences.h main_functions.h structures_discribe.h
	gcc -c cw.c

actions_with_sentences.o: actions_with_sentences.c actions_with_sentences.h
	gcc -c actions_with_sentences.c

main_functions.o: main_functions.c main_functions.h
	gcc -c main_functions.c

stuctures_discribe.o: stuctures_discribe.c structures_discribe.h
	gcc -c stuctures_discribe.c

clean:
	rm -f *.o cw