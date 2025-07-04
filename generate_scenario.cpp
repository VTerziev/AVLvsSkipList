#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include "scenario.h"
using std::vector;
using std::string;
using std::ofstream;
using std::ifstream;

int generateRandomNumber() {
    return (rand()*rand()+rand())%(1<<20);
}

string generateRandomCommand() {
    int randomNumber = generateRandomNumber()%3;
    if (randomNumber==0) { return CONTAINS_COMMAND; }
    if (randomNumber==1) { return DELETE_COMMAND; }
    return INSERT_COMMAND;
}

// TODO: create folder if it doesn't exist
string OUTPUT_FOLDER = "tests/";

void generateScenario1() { /// insert in ascending order
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"1.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << i+1 << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario2() { /// insert in descending order
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"2.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << 1000000-i << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario3() { /// insert in random order
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"3.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << generateRandomNumber() << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario4() { /// searching elements in a small set
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"4.in");
    for ( int i = 0 ; i < 1000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << i+1 << "\n";
    }
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << CONTAINS_COMMAND << " " << (generateRandomNumber()%1000 + 1) << "\n";
    }
    fout << "\n";
    fout.close();

}

void generateScenario5() { /// searching elements in a large set
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"5.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << i+1 << "\n";
    }
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << CONTAINS_COMMAND << " " << (generateRandomNumber()%1000000 + 1) << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario6() { /// insert many elements then delete them
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"6.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << i+1 << "\n";
    }
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << DELETE_COMMAND << " " << i+1 << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario7() { /// insert and delete
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"7.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << i+1 << "\n";
        fout << DELETE_COMMAND << " " << i+1 << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario8() { /// insert, contains and delete
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"8.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << i+1 << "\n";
        fout << CONTAINS_COMMAND << " " << i+1 << "\n";
        fout << DELETE_COMMAND << " " << i+1 << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario9() { /// many random inserts, many random contains then many random deletes
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"9.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << generateRandomNumber() << "\n";
    }
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << CONTAINS_COMMAND << " " << generateRandomNumber() << "\n";
    }
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << DELETE_COMMAND << " " << generateRandomNumber() << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario10() { /// random inserts, contains and deletes
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"10.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << INSERT_COMMAND << " " << generateRandomNumber() << "\n";
        fout << CONTAINS_COMMAND << " " << generateRandomNumber() << "\n";
        fout << DELETE_COMMAND << " " << generateRandomNumber() << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario11() { /// random all
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"11.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << generateRandomCommand() << " " << generateRandomNumber() << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario12() { /// random all
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"12.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << generateRandomCommand() << " " << generateRandomNumber() << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario13() { /// random all
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"13.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << generateRandomCommand() << " " << generateRandomNumber() << "\n";
    }
    fout << "\n";
    fout.close();
}

void generateScenario14() { /// almost inserting in increasing order
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"14.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        if (i%4) {
            fout << INSERT_COMMAND << " " << i+1 << "\n";
        } else {
            fout << generateRandomCommand() << " " << generateRandomNumber() << "\n";
        }
    }
    fout << "\n";
    fout.close();
}

void generateScenario15() { ///  almost inserting in decreasing order
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"15.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        if (i%4) {
            fout << INSERT_COMMAND << " " << 1000000-i << "\n";
        } else {
            fout << generateRandomCommand() << " " << generateRandomNumber() << "\n";
        }
    }
    fout << "\n";
    fout.close();
}

void generateScenario16() { /// mostly searching elements
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"16.in");
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        fout << CONTAINS_COMMAND << " " << generateRandomNumber() << "\n";
        fout << CONTAINS_COMMAND << " " << generateRandomNumber() << "\n";
        fout << CONTAINS_COMMAND << " " << generateRandomNumber() << "\n";

        fout << generateRandomCommand() << " " << generateRandomNumber() << "\n";
    }
    fout << "\n";
    fout.close();
}

vector<int> insertedNumbers = vector<int>();
void generateScenario17() { /// random inserts and then delete those elements
    ofstream fout;
    fout.open(OUTPUT_FOLDER+"17.in");
    insertedNumbers.clear();
    for ( int i = 0 ; i < 1000000 ; i ++ ) {
        insertedNumbers.push_back(generateRandomNumber());
        fout << INSERT_COMMAND << " " << insertedNumbers.back() << "\n";
    }
    for ( int i = 0 ; i < insertedNumbers.size() ; i ++ ) {
        fout << DELETE_COMMAND << " " << insertedNumbers[i] << "\n";
    }
    fout << "\n";
    fout.close();
    insertedNumbers.clear();
}

void generateFolderIfNotExists() {
    int status = mkdir(OUTPUT_FOLDER.c_str(), 0777);
    if (status == -1) {
        if (errno == EEXIST) {
            std::cout << "Folder already exists\n";
        } else {
            std::cout << "Result of creating the folder : " << status << "\n";
        }
    }
}

int main () {
    srand(1337);
    generateFolderIfNotExists();

    generateScenario1();
    generateScenario2();
    generateScenario3();
    generateScenario4();
    generateScenario5();
    generateScenario6();
    generateScenario7();
    generateScenario8();
    generateScenario9();
    generateScenario10();
    generateScenario11();
    generateScenario12();
    generateScenario13();
    generateScenario14();
    generateScenario15();
    generateScenario16();
    generateScenario17();
}
