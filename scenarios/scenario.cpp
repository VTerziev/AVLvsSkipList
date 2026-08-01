#include <string>
#include <vector>

#ifndef SCENARIO_GUARD
#define SCENARIO_GUARD

using std::string;
using std::vector;

string INSERT_COMMAND = "insert";
string DELETE_COMMAND = "delete";
string CONTAINS_COMMAND = "contains";

struct Scenario {
  vector<string> commands;
  vector<int> values;

  Scenario() {
    this->commands = vector<string>();
    this->values = vector<int>();
  }

  void add(string command, int value) {
    commands.push_back(command);
    values.push_back(value);
  }

  int size() { return values.size(); }
};

#endif
