CXX = g++
CPPFLAGS = -Wall -g -Ilib
BIN_DIR = exe

all: $(BIN_DIR)/.dirstamp $(BIN_DIR)/pokemon

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

$(BIN_DIR)/pokemon: src/main.cpp bin/attackMove.o bin/battle.o bin/pokemon.o
	$(CXX) $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/attackMove.o: lib/attackMove.h src/attackMove.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/battle.o: lib/battle.h src/battle.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/pokemon.o: lib/pokemon.h src/pokemon.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)