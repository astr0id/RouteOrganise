main: main.o timebased.o load.o
	g++ -o main main.o timebased.o load.o

timebased.o : timebased.cpp timebased.h Datastruct.h
	g++ -c timebased.cpp

load.o : load.cpp load.h Datastruct.h
	g++ -c load.cpp

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o timebased.o load.o