.PHONY: debug, clean

debug: src/main.cpp
	g++ src/main.cpp src/common/*.cpp src/formats/*.cpp src/algorithms/*.cpp -ljpeg -o bin/release/main

clean:
	rm bin/release/*
