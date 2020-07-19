Datatblr: Datatblr.o
	g++ -std=c++17 Datatblr.o -o Datatblr

Datatblr.o: Datatblr.cpp
	g++ -std=c++17 -c Datatblr.cpp

clean:
	rm Datatblr.o Datatblr
