waves: waves.h waves.c main_waves.c
	clang -Wall -lm -o waves waves.c main_waves.c
evidence_waves: waves.h waves.c evidence_waves.c
	clang -Wall -lm -o evidence_waves waves.c evidence_waves.c
clean:
	rm -f evidence_waves waves *.o *~ *.ppm
show:
	./waves -s 1000 -g 200 > my-image.ppm
	display my-image.ppm