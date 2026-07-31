all: main generate_scenario run_scenario

BUILD_DIR=build
COMPILER=clang++ -std=c++17 -Wno-shift-negative-value

main: prepare avl.o
	${COMPILER} -g -o $(BUILD_DIR)/main main.cpp $(BUILD_DIR)/avl.o

generate_scenario: prepare
	${COMPILER} -g -o $(BUILD_DIR)/generate_scenario generate_scenario.cpp $(BUILD_DIR)/avl.o

run_scenario: prepare
	${COMPILER} -g -o $(BUILD_DIR)/run_scenario run_scenario.cpp $(BUILD_DIR)/avl.o

avl.o: prepare
	${COMPILER} -g -o $(BUILD_DIR)/avl.o -c avl.cpp

prepare:
	mkdir -p $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR) 
