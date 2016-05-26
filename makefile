main: main.o timebased.o load.o moneybased.o keyboard.o findpath.o
	g++ -o main main.o timebased.o load.o moneybased.o keyboard.o findpath.o


timebased.o : timebased.cpp timebased.h Datastruct.h
	g++ -c  timebased.cpp

moneybased.o : moneybased.cpp moneybased.h Datastruct.h
	g++ -c moneybased.cpp

load.o : load.cpp load.h Datastruct.h
	g++ -c load.cpp

keyboard.o : keyboard.cpp timebased.h moneybased.h Datastruct.h
	g++ -c keyboard.cpp

findpath.o : findpath.cpp Datastruct.h
	g++ -c findpath.cpp

main.o : main.cpp keyboard.h
	g++ -c  main.cpp

clean:
	rm main.o timebased.o load.o moneybased.o keyboard.o findpath.o