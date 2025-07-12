
all: main generate_scenario run_scenario

BUILD_DIR=build

main: prepare
	g++ -o $(BUILD_DIR)/main main.cpp

generate_scenario: prepare
	g++ -o $(BUILD_DIR)/generate_scenario generate_scenario.cpp

run_scenario: prepare
	g++ -o $(BUILD_DIR)/run_scenario run_scenario.cpp

prepare:
	mkdir $(BUILD_DIR)

clean: 
	rm -rf $(BUILD_DIR) 
