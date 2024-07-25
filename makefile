CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -std=c++11 -Wall

TARGET = main

SRC = main.cpp
OBJ = main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJ)

main.o: main.cpp BankAccount.h CD.h CheckingAccount.h SavingAccount.h
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f $(TARGET) $(OBJ)
