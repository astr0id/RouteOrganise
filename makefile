main: main.o timebased.o load.o moneybased.o keyboard.o findpath.o ltlm.o go.o
	g++ -o main main.o timebased.o load.o moneybased.o keyboard.o findpath.o ltlm.o go.o

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

ltlm.o : LTLM.cpp LTLM.h Datastruct.h
	g++ -c LTLM.cpp

go.o : go.cpp go.h Datastruct.h
	g++ -c go.cpp 

main.o : main.cpp keyboard.h
	g++ -c  main.cpp

clean:
	rm main main.o timebased.o load.o moneybased.o keyboard.o findpath.o ltlm.o go.o