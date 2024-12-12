CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Ilib/SFML-2.5.1/include -pthread
LDFLAGS = -Llib/SFML-2.5.1/lib -lsfml-graphics -lsfml-window -lsfml-system -pthread -lstdc++

SRC = src/main.cpp src/Game.cpp src/Waiter.cpp src/Chef.cpp src/Customer.cpp src/Semaphore.cpp src/Wait.cpp
OBJ_DIR = obj
OBJ = $(SRC:src/%.cpp=$(OBJ_DIR)/%.o)
EXEC = restaurante

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -f $(OBJ) $(EXEC)
	rm -rf $(OBJ_DIR)