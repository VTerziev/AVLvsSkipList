all: main generate_scenario run_scenario

BUILD_DIR=build

main: prepare avl.o
	g++ -g -o $(BUILD_DIR)/main main.cpp $(BUILD_DIR)/avl.o

generate_scenario: prepare
	g++ -g -o $(BUILD_DIR)/generate_scenario generate_scenario.cpp $(BUILD_DIR)/avl.o

run_scenario: prepare
	g++ -g -o $(BUILD_DIR)/run_scenario run_scenario.cpp $(BUILD_DIR)/avl.o

avl.o: prepare
	g++  -g -o $(BUILD_DIR)/avl.o -c avl.cpp

prepare:
	mkdir -p $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR) 
