CXX=g++
CXXFLAGS=-std=c++11
OBJ=circular_sector.o hellomake.o
SRC=circular_sector.cpp ellipse.cpp main.cpp sort.cpp triangle.cpp
EXE=hellomake #filename
all:$(EXE)
$(EXE):$(OBJ)
	$(CXX) -o $(EXE) $(OBJ)
$(OBJ):$(SRC)
	$(CXX) -c $(SRC)
clean:
	rm -f $(EXE)
	rm -f $(OBJ)