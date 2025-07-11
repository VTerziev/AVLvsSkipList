
all: main generate_scenario run_scenario

BUILD_DIR=build

main: prepare avl.o
	g++ -O3 -o $(BUILD_DIR)/main main.cpp $(BUILD_DIR)/avl.o

generate_scenario: prepare
	g++ -O3 -o $(BUILD_DIR)/generate_scenario generate_scenario.cpp

run_scenario: prepare
	g++ -O3 -o $(BUILD_DIR)/run_scenario run_scenario.cpp

avl.o: prepare
	g++ -O3 -o $(BUILD_DIR)/avl.o -c avl.cpp

prepare:
	mkdir -p $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR) 
