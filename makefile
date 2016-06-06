main: main.o load.o go.o D.o
	g++ -o main main.o load.o go.o D.o

load.o : load.cpp load.h Datastruct.h
	g++ -c load.cpp

go.o : go.cpp go.h Datastruct.h
	g++ -c go.cpp 

D.o : Datastruct.cpp Datastruct.h
	g++ -c Datastruct.cpp

main.o : main.cpp keyboard.h
	g++ -c  main.cpp

clean:
	rm main main.o load.o go.o D.o