CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -std=c++11 -Wall

TARGET = hw06

SRC = hw06.cpp
OBJ = hw06.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJ)

hw06.o: main.cpp BankAccount.h CD.h CheckingAccount.h SavingAccount.h
	$(CXX) $(CXXFLAGS) -c hw06.cpp

clean:
	rm -f $(TARGET) $(OBJ)
