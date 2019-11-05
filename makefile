.PHONY: debug, clean

debug: src/main.cpp
	g++ src/main.cpp src/common/*.cpp src/formats/*.cpp src/algorithms/*.cpp -ljpeg -o bin/release/doopdot

clean:
	rm bin/release/*

