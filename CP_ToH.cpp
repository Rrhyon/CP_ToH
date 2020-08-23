/*
  Name:             Phillip Tette
  Class:            CIS170L
  Professor:        Penn Wu
  Project Name:     Tower of Hanoi
  Date:             20200810
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "ctutilities.h"

using namespace std;

// Global Variables
vector<vector<string>> highScores;
vector<int> towers[3];
const string scoreboard = "scoreboard.csv";

const string tableHeader[] = {
    "+----------------------------------------------+\n",
    "|              High Score List                 |\n",
    "+----------------------------------------------+\n",
    "| Tower Size | Perfect | High Score | Initials |\n",
    "+----------------------------------------------+\n"
};

const vector<vector<string>> defaultTable = {
    {" 3","   7","0000","XXX"},
    {" 4","  15","0000","XXX"},
    {" 5","  31","0000","XXX"},
    {" 6","  63","0000","XXX"},
    {" 7"," 127","0000","XXX"},
    {" 8"," 255","0000","XXX"},
    {" 9"," 511","0000","XXX"},
    {"10","1023","0000","XXX"}
};

const string ruleBook[] = {
    "+----------------------------------------------+\n",
    "|                      Rules                   |\n",
    "|   1. You may only move one disc at a time.   |\n",
    "|   2. You may only move the uppermost disc    |\n",
    "|      that is at the top of the tower.        |\n",
    "|   3. You may not place a larger disc on top  |\n",
    "|      of a smaller disc.                      |\n",
    "|                                              |\n",
    "|                    Good Luck!                |\n",
    "+----------------------------------------------+\n"
};

/******************************************************************************
*                                 Functions
******************************************************************************/

vector<vector<string>> loadScoreboard() {
    /* Will attempt to open a file named "scoreboard.csv".
     * If the file exists, it will open the file with an input
     * stream only. It will then read the file line by line,
     * using the helper function "parseCSV" and will assign each
     * returned "line" vector to the scores vector of vectors,
     * until there are no new lines. If the file doesn't exist,
     * the file "scoreboard.csv" will be created and opened with
     * an input, output, and truncate stream; then using the 
     * default values provided in the program, the scoreboard
     * will be created.
     */
    vector<vector<string>> scores;
    fstream file;
    string line;

    file.open(scoreboard, fstream::in);
    cout << "    Thank you for playing the Tower of Hanoi." << endl;
    if (fileExists(scoreboard)) {
        while (getline(file, line)) {
            scores.push_back(parseCSV(line));
        }
    }
    else {
        file.open(scoreboard, fstream::in | fstream::out | fstream::trunc);
        for (int i = 0; i < defaultTable.size(); i++) {
            file << defaultTable[i][0] + "," + defaultTable[i][1] + "," + 
                    defaultTable[i][2] + "," + defaultTable[i][3] << endl;
        }
        scores = defaultTable;
        }
    file.close();
    return scores;
}

void saveScoreboard() {
    fstream file;
    file.open(scoreboard, fstream::out);
    for (unsigned int i = 0; i < highScores.size(); i++) {
        file << writeCSV(highScores[i]) << endl;
    }
    file.close();
}

void displayScoreboard() {

    for (int i = 0; i < sizeof(tableHeader) / sizeof(tableHeader[0]); i++) {
        cout << tableHeader[i];
    }
    for (unsigned int i = 0; i < highScores.size(); i++) {
        cout << "| "    + highScores[i][0] + " Discs" +
            "   |  "    + highScores[i][1] +
            "   |    "  + highScores[i][2] +
            "    |    " + highScores[i][3] + 
            "   |"      << endl;
    }
    cout << tableHeader[4];
}

void checkHighScore(int numDiscs,  int playerScore) {

    saveScoreboard();
}

void gameOptions() {
    string selected;
    // This function will allow the player to choose how to proceed once the game is started.
    vector<string> options = { "P", "R", "Q" };
    while (!isValidOption(selected, options)) {
        selected = capsMe(input("\nPlease select one of the following menu options.\n"
                "    P to Play, R for Rules, or Q to quit: "));
    }
    if (selected == "P") {
        cout << "\n        Excellent, let's get started!!!\n\n";
    }
    else if (selected == "R") {
        cout << endl;
        for (int i = 0; i < sizeof(ruleBook) / sizeof(ruleBook[0]); i++)
            cout << ruleBook[i];
        gameOptions();
    }
    else if (selected == "Q") {
        exit(0);
    }
}

int chooseDifficulty() {
    // This functions will serve only to ask the user to select their difficulty.
    string discQuantity;
    vector<string> validNum = { "3", "4", "5", "6", "7", "8", "9", "10" };
    while (!isValidOption(discQuantity, validNum)) {
        discQuantity = input("Select the numbers of discs you would like to start with (3-10): ");
    }
    return stoi(discQuantity);
}

void showTowerState(vector<int> state) {
    
    for (int peg = 1; peg <= 3; peg++) {
        vector<string> stack;
        cout << "Discs on Peg " << peg << ": ";
        // find all discs on this peg
        for (unsigned int disc = state.size() - 1; disc >= 1; disc--) {
            if (state[disc] == peg) {
                stack.push_back(to_string(disc));
            }
        }
        // Print all matching discs 
        if (!stack.empty()) {
            cout << writeCSV(stack);
        }
        cout << endl;
    }
}

int moveDisc() {

    return stoi(input("Select the disc you would like to move: "));
}

bool checkGameState(vector<int> state) {
    // Checks that all the discs are located on the same peg, other than peg one
    if (state[1] == 1) {
        return false;
    }
    for (unsigned int disc = state.size() - 1; disc > 1; disc--) {
        if(state[1] != state[disc]){
            return false;
        }
    }
    return true;
}

int doGameLoop(const int discs) {

    vector<int> discState;
    int moveCount = 0;
    bool inPlay = true;
    // Put an empty value slot 0
    discState.push_back(0);
    for (int disc = 1; disc <= discs; disc++) {
        // Start all discs on first tower
        discState.push_back(1);
    }
    while (inPlay) {
        showTowerState(discState);
        cout << "Number of moves: " + to_string(moveCount) << endl;
        moveDisc();
        moveCount++;
        inPlay = checkGameState(discState);

    }
    checkHighScore(discs, moveCount);
    return 0;
}
    
int main() {

    highScores = loadScoreboard();

    displayScoreboard();

    gameOptions();

    int discs = chooseDifficulty();

    // Used the vector integer due to a constant requirement placed on the towerSize variable.
    // This will create the array of discs dynamically based on the option selected in chooseDifficulty.

    doGameLoop(discs);
}
