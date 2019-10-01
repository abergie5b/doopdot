.PHONY: debug, clean

debug: src/main.cpp src/jpeg.h src/jpeg.cpp  src/pgm.cpp src/pgm.h
	g++ src/*.cpp -ljpeg -o bin/release/main

clean:
	rm bin/release/main/*.o
