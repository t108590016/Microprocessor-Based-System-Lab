CROSS_COMPILE = aarch64-linux-gnu-
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
CXXFLAGS=-std=c++11
OBJ=lab5_2.o
SRC=lab5_2.cpp
EXE=Lab5
all:$(EXE)
$(EXE):$(OBJ)
	$(CXX) -o $(EXE) $(OBJ)
$(OBJ):$(SRC)
	$(CXX) -c $(SRC)
clean:
	rm -f $(EXE)
	rm -f $(OBJ)
