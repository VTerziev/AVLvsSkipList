#include "avl.h"
#include "scenario.cpp"
#include "skip_list.cpp"
#include <chrono>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

long long timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

template <typename T> long long executionMilliseconds(Scenario *scenario) {
  long long startTime = timeSinceEpochMillisec();

  Container *c = new T();
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
  return endTime - startTime;
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
  ofstream fout;
  fout.open(OUTPUT_LOCATION);

  fout << "No, AVL, Skip-List\n";

  for (int i = 0; i < SCENARIOS_LIST.size(); i++) {
    ifstream scenarioInput;
    scenarioInput.open(INPUT_FOLDER + SCENARIOS_LIST[i]);
    Scenario scenario = Scenario();
    readScenario(&scenarioInput, &scenario);
    scenarioInput.close();

    cout << "starting execution of " << SCENARIOS_LIST[i] << "\n";
    long long millisecondsAvl = executionMilliseconds<AVLTree>(&scenario);
    cout << "avl time: " << millisecondsAvl << "\n";

    long long millisecondsSkipList = executionMilliseconds<SkipList>(&scenario);
    cout << "skip list time: " << millisecondsSkipList << "\n";

    fout << i + 1 << ", " << millisecondsAvl << ", " << millisecondsSkipList << "\n";
  }
  fout.close();
  return 0;
}
