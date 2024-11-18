myPuzzle: imagepuzzle.o imagepuzzledriver.o
	g++ imagepuzzle.o imagepuzzledriver.o -o myPuzzle

imagepuzzle.o: imagepuzzle.cpp
	g++ -c imagepuzzle.cpp

imagepuzzledriver.o: imagepuzzledriver.cpp
	g++ -c imagepuzzledriver.cpp

clean:
	rm *.o myPuzzle
