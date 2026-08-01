#include "scenario.cpp"
#include <string>

struct RunResult {
  Scenario *scenario;

  long long execMs;
  long long bytesUsed;

  std::string testedTypeName;

  RunResult(Scenario *scenario, std::string testedTypeName) {
    this->scenario = scenario;
    this->testedTypeName = testedTypeName;
  }

  void finish(long long execMs, long long bytesUsed) {
    this->execMs = execMs;
    this->bytesUsed = bytesUsed;
  }
};