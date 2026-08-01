#include "../avl.h"
#include "../hash_set_c.cpp"
#include "../skip_list.cpp"
#include "../skip_list_vec.cpp"
#include "run_result.cpp"
#include "scenario.cpp"
#include <chrono>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

struct TestType {
  std::string name;
  std::function<Container *()> init;

  TestType(std::string name, std::function<Container *()> init) {
    this->name = name;
    this->init = init;
  }
  std::string getName() { return name; }
};

long long timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

template <typename T> std::string prettyTypeName() {
  std::string res = typeid(T).name();
  while (res[0] >= '0' && res[0] <= '9') {
    res.erase(0, 1);
  }
  return res;
}

RunResult runScenario(Scenario *scenario, TestType *testType) {
  long long startTime = timeSinceEpochMillisec();

  RunResult result = RunResult(scenario, testType->name);
  Allocator::reset();

  Container *c = testType->init();
  for (int i = 0; i < scenario->size(); i++) {
    if (scenario->commands[i][0] == 'c') {
      c->contains(scenario->values[i]);
    } else if (scenario->commands[i][0] == 'i') {
      c->insert(scenario->values[i]);
    } else if (scenario->commands[i][0] == 'd') {
      c->remove(scenario->values[i]);
    } else {
      throw std::invalid_argument("Command not recognized");
    }
  }
  delete c;
  long long endTime = timeSinceEpochMillisec();
  result.finish(endTime - startTime, Allocator::maxAllocatedBytes);
  return result;
}

void readScenario(ifstream *fin, Scenario *scenario) {
  string command;
  int value;
  while ((*fin) >> command >> value) {
    scenario->add(command, value);
  }
}

string generateId(int digitCount) {
  string result = "";
  for (int i = 0; i < digitCount; i++) {
    result += rand() % 10 + '0';
  }
  return result;
}

int main() {
  srand(1337);

  vector<string> SCENARIOS_LIST = vector<string>();
  // TODO: find the tests automatically
  SCENARIOS_LIST.push_back("1.in");
  SCENARIOS_LIST.push_back("2.in");
  SCENARIOS_LIST.push_back("3.in");
  SCENARIOS_LIST.push_back("4.in");
  SCENARIOS_LIST.push_back("5.in");
  SCENARIOS_LIST.push_back("6.in");
  SCENARIOS_LIST.push_back("7.in");
  SCENARIOS_LIST.push_back("8.in");
  SCENARIOS_LIST.push_back("9.in");
  SCENARIOS_LIST.push_back("10.in");
  SCENARIOS_LIST.push_back("11.in");
  SCENARIOS_LIST.push_back("12.in");
  SCENARIOS_LIST.push_back("13.in");
  SCENARIOS_LIST.push_back("14.in");
  SCENARIOS_LIST.push_back("15.in");
  SCENARIOS_LIST.push_back("16.in");
  SCENARIOS_LIST.push_back("17.in");

  string INPUT_FOLDER = "tests/";
  string OUTPUT_LOCATION = "result" + generateId(10) + ".out";

  vector<TestType> testTypes;
  testTypes.push_back(TestType("AvlTree", []() { return new AVLTree(); }));
  testTypes.push_back(TestType("SkipList", []() { return new SkipList(); }));
  testTypes.push_back(TestType("SkipListVec", []() { return new SkipListVec(); }));
  testTypes.push_back(TestType("HashSet", []() { return new HashSet(); }));

  ofstream fout;
  fout.open(OUTPUT_LOCATION);

  fout << "No";
  for (int i = 0; i < testTypes.size(); i++) {
    fout << ", " << testTypes[i].name;
  }
  fout << "\n";

  for (int i = 0; i < SCENARIOS_LIST.size(); i++) {
    ifstream scenarioInput;
    scenarioInput.open(INPUT_FOLDER + SCENARIOS_LIST[i]);
    Scenario scenario = Scenario();
    readScenario(&scenarioInput, &scenario);
    scenarioInput.close();

    cout << "starting execution of " << SCENARIOS_LIST[i] << "\n";
    vector<RunResult> results;
    for (int j = 0; j < testTypes.size(); j++) {
      results.push_back(runScenario(&scenario, &testTypes[j]));
    }

    for (int j = 0; j < results.size(); j++) {
      cout << results[j].testedTypeName << ": " << results[j].execMs << "\n";
    }

    fout << i + 1;
    for (int j = 0; j < results.size(); j++) {
      fout << ", " << results[j].execMs;
    }
    fout << "\n";
  }
  fout.close();
  return 0;
}
