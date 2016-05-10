main: main.o demo.o 
	g++ -o main main.o demo.o

demo.o : demo.cpp demo.h Datastruct.h
	g++ -c demo.cpp

main.o : main.cpp
	g++ -c main.cpp