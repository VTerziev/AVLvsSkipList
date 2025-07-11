#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include "skip_list.cpp"
#include "avl.cpp"
#include "scenario.cpp"
#include <chrono>

using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

long long timeSinceEpochMillisec()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

long long executionMillisecondsAvl(Scenario *scenario)
{
    long long startTime = timeSinceEpochMillisec();

    MemoryAllocator<AvlNode> *memoryAllocator = new MemoryAllocator<AvlNode>();
    AVLTree *avl = new AVLTree(memoryAllocator);
    for (int i = 0; i < scenario->size(); i++)
    {
        if (scenario->commands[i][0] == 'c')
        {
            avl->contains(scenario->values[i]);
        }
        else if (scenario->commands[i][0] == 'i')
        {
            avl->insert(scenario->values[i]);
        }
        else if (scenario->commands[i][0] == 'd')
        {
            avl->remove(scenario->values[i]);
        }
        else
        {
            throw std::invalid_argument("Command not recognized");
        }
    }
    delete avl;
    long long endTime = timeSinceEpochMillisec();
    return endTime - startTime;
}

long long executionMillisecondsSkipList(Scenario *scenario)
{
    long long startTime = timeSinceEpochMillisec();

    SlNodeFactory *nodeFactory = new SlNodeFactory();
    SkipList *skipList = new SkipList(nodeFactory);
    for (int i = 0; i < scenario->size(); i++)
    {
        if (scenario->commands[i][0] == 'c')
        {
            skipList->contains(scenario->values[i]);
        }
        else if (scenario->commands[i][0] == 'i')
        {
            skipList->insert(scenario->values[i]);
        }
        else if (scenario->commands[i][0] == 'd')
        {
            skipList->remove(scenario->values[i]);
        }
        else
        {
            throw std::invalid_argument("Command not recognized");
        }
    }
    delete skipList;
    long long endTime = timeSinceEpochMillisec();
    return endTime - startTime;
}

void readScenario(ifstream *fin, Scenario *scenario)
{
    string command;
    int value;
    while ((*fin) >> command >> value)
    {
        scenario->add(command, value);
    }
}

string generateId(int digitCount)
{
    string result = "";
    for (int i = 0; i < digitCount; i++)
    {
        result += rand() % 10 + '0';
    }
    return result;
}

int main()
{
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

    for (int i = 0; i < SCENARIOS_LIST.size(); i++)
    {
        ifstream scenarioInput;
        scenarioInput.open(INPUT_FOLDER + SCENARIOS_LIST[i]);
        Scenario *scenario = new Scenario();
        readScenario(&scenarioInput, scenario);
        scenarioInput.close();

        cout << "starting execution of " << SCENARIOS_LIST[i] << "\n";
        long long millisecondsAvl = executionMillisecondsAvl(scenario);
        cout << "avl time: " << millisecondsAvl << "\n";

        long long millisecondsSkipList = executionMillisecondsSkipList(scenario);
        cout << "skip list time: " << millisecondsSkipList << "\n";

        fout << i + 1 << ", " << millisecondsAvl << ", " << millisecondsSkipList << "\n";
        delete scenario;
    }
    fout.close();
    return 0;
}
