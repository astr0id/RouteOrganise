main: main.o timebased.o load.o moneybased.o
	g++ -o main main.o timebased.o load.o moneybased.o

timebased.o : timebased.cpp timebased.h Datastruct.h
	g++ -c timebased.cpp

moneybased.o : moneybased.cpp moneybased.h Datastruct.h
	g++ -c moneybased.cpp

load.o : load.cpp load.h Datastruct.h
	g++ -c load.cpp

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o timebased.o load.o moneybased.o