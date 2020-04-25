

bin/mfcc: src/main.c obj/r4_fft.o obj/mfcc.o bin
	gcc src/main.c obj/r4_fft.o obj/mfcc.o -o bin/mfcc -O3 -I include/ -lm -Wall
	
obj/r4_fft.o: src/r4_fft.c obj
	gcc src/r4_fft.c -o obj/r4_fft.o -O3 -c -I include/ -Wall
	
obj/mfcc.o: src/mfcc.c obj
	gcc src/mfcc.c -o obj/mfcc.o -O3 -c -I include/ -Wall

bin:
	mkdir bin

obj:
	mkdir obj

clean:
	rm -Rf obj
	rm -Rf bin
