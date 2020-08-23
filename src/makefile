SOURCES = main.o boot_info.o call_func.o commands.o files.o formatting.o globals.o initiate.o

Datatblr: $(SOURCES)
	g++ -std=c++17 $(SOURCES) -o Datatblr

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

boot_info.o: boot_info.cpp
	g++ -std=c++17 -c boot_info.cpp

call_func.o: call_func.cpp
	g++ -std=c++17 -c call_func.cpp

commands.o: commands.cpp
	g++ -std=c++17 -c commands.cpp

files.o: files.cpp
	g++ -std=c++17 -c files.cpp

formatting.o: formatting.cpp
	g++ -std=c++17 -c formatting.cpp

globals.o: globals.cpp
	g++ -std=c++17 -c globals.cpp

initiate.o: initiate.cpp
	g++ -std=c++17 -c initiate.cpp


clean:
	rm $(SOURCES)
