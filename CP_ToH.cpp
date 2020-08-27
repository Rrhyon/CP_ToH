/*
  Name:             Phillip Tette
  Class:            CIS170L
  Professor:        Penn Wu
  Project Name:     Tower of Hanoi
  Date:             20200714
  Date Modified:    20200824
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
const string scoreboard = "scoreboard.csv";

const string tableHeader[] = {
    "+----------------------------------------------+\n",
    "|              High Score List                 |\n",
    "+----------------------------------------------+\n",
    "| Tower Size | Perfect | High Score | Initials |\n",
    "+----------------------------------------------+\n"
};

const vector<vector<string>> defaultTable = {
    {"3",  "7",    "0", "XXX"},
    {"4",  "15",   "0", "XXX"},
    {"5",  "31",   "0", "XXX"},
    {"6",  "63",   "0", "XXX"},
    {"7",  "127",  "0", "XXX"},
    {"8",  "255",  "0", "XXX"},
    {"9",  "511",  "0", "XXX"},
    {"10", "1023", "0", "XXX"}
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
    /* Will attempt to open a file named "scoreboard.csv". If the file exists,
     * it will open the file with an input stream only. It will then read the file
     * line by line, using the helper function "parseCSV" and will assign each
     * returned "line" vector to the scores vector of vectors, until there are no
     * new lines. If the file doesn't exist, the file "scoreboard.csv" will be
     * created and opened with an input, output, and truncate stream; then using
     * the default values provided in the program, the scoreboard will be created.
     */
    vector<vector<string>> scores;
    fstream file;
    string line;
    file.open(scoreboard, fstream::in);
    cout << "    Thank you for playing the Tower of Hanoi.\n";
    if (fileExists(scoreboard)) {
        while (getline(file, line)) {
            scores.push_back(parseCSV(line));
        }
    }
    else {
        file.open(scoreboard, fstream::out);
        for (int i = 0; i < defaultTable.size(); i++) {
            file << writeCSV(defaultTable[i]) << endl;
        }
        scores = defaultTable;
    }
    file.close();
    return scores;
}

void saveScoreboard() {
    /* Will open the "scoreboard.csv" file with an output (write) stream only.
     * The function will then read through the "highScores" vector of vectors,
     * and will add overwrite the data on the scoreboard with the most recent
     * changes using the "writeCSV" helper function.
     */
    fstream file;
    file.open(scoreboard, fstream::out | fstream::trunc);
    for (size_t i = 0; i < highScores.size(); i++) {
        file << writeCSV(highScores[i]) << endl;
    }
    file.close();
}

void displayScoreboard() {
    /* Will read through and cout the global "tableHeader", and then the 
     * "highScores" vector of vectors, and lastly grab the 4th element of the
     * "tableHeader" to close out the scoreboard display.
     */
    for (int i = 0; i < sizeof(tableHeader) / sizeof(tableHeader[0]); i++) {
        cout << tableHeader[i];
    }
    for (size_t i = 0; i < highScores.size(); i++) {
        cout << "|" + cPadMe(highScores[i][0] + " Discs", 12) +
                "|" + cPadMe(highScores[i][1], 9) +
                "|" + cPadMe(highScores[i][2], 12) +
                "|" + cPadMe(highScores[i][3], 10) + 
                "|" << endl;
    }
    cout << tableHeader[4];
}

void checkHighScore(const int numDiscs, const int playerScore) {
    // It works so I went with it.
    for (size_t i = 0; i < highScores.size(); i++) {
        if (stoi(highScores[i][0]) == numDiscs) {
            if (stoi(highScores[i][2]) == 0 || stoi(highScores[i][2]) > playerScore) {
                highScores[i][3] = input("Congratulations, you have a new high score!!!\nPlease enter your initials: ");
                highScores[i][2] = to_string(playerScore);
                saveScoreboard();
            }
            break;
        }
    }
}

bool gameOptions() {
    // This function will allow the player to choose how to proceed once the
    // game is started.
    string selected;
    const vector<string> options = { "P", "R", "Q" };
    while (!isValidOption(selected, options)) {
        selected = capsMe(input("\nPlease select one of the following menu options.\n"
                                "    P to Play, R for Rules, or Q to quit: "));
    }
    if (selected == "P") {
        cout << "\n        Excellent, let's get started!!!\n\n";
        return true;
    }
    else if (selected == "R") {
        cout << endl;
        for (int i = 0; i < sizeof(ruleBook) / sizeof(ruleBook[0]); i++) {
            cout << ruleBook[i];
        }
        return gameOptions();
    }
    else if (selected == "Q") {
        return false;
    }
    return false;
}

int chooseDifficulty() {
    // Will serve only to ask the user to select their difficulty level.
    string discQuantity;
    const vector<string> validNum = { "3", "4", "5", "6", "7", "8", "9", "10" };
    while (!isValidOption(discQuantity, validNum)) {
        discQuantity = input("Select the numbers of discs you would like to start with (3-10): ");
    }
    return stoi(discQuantity);
}

void showTowerState(const vector<int>& state) {
    // Using the provided value, "discState" from the doGameLoop, this function
    // will show to the user what peg each disc is located on.
    for (int peg = 1; peg <= 3; peg++) {
        vector<string> stack;
        cout << "Discs on Peg " << peg << ": ";
        // find all discs on this peg
        for (size_t disc = state.size() - 1; disc >= 1; disc--) {
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

bool invalidPeg(const vector<int>& state, const int srcpeg, const int destpeg = 0) {
    int srcsize = 0;
    int destsize = 0;
    for (size_t disc = 1; disc < state.size(); disc++) {
        if (state[disc] == srcpeg) {
            srcsize = int(disc);
            break;
        }
    }
    if (srcpeg != 0 && srcsize == 0) {
        cout << "Source peg is empty!" << endl;
        return true;
    }
    for (size_t disc = 1; disc < state.size(); disc++) {
        if (state[disc] == destpeg) {
            destsize = int(disc);
            break;
        }
    }
    if (destsize != 0 && srcsize > destsize) {
        cout << "Smaller disc is already on this peg." << endl;
        return true;
    }
    return false;
}

void moveDisc(vector<int>& state) {
    // Prompt the player for moves and modifies the game state.
    // Note: 'state' is an in/out parameter
    string source, dest;
    int current = 0;
    const vector<string> options = { "1", "2", "3" };
    while (!isValidOption(source, options) || invalidPeg(state, stoi(source))) {
        source = input("Select the source peg to choose a disc: ");

    }
    while (!isValidOption(dest, options) || invalidPeg(state, stoi(source), stoi(dest))) {
        dest = input("Select the destination peg to move the disc: ");
    }
    for (size_t disc = 1; disc < state.size(); disc++) {
        if (state[disc] == stoi(source)) {
            current = int(disc);
            break;
        }
    }
    state[current] = stoi(dest);
}

bool checkGameState(const vector<int>& state) {
    // Checks that all the discs are located on the same peg, other than peg one.
    if (state[1] == 1) {
        return false;
    }
    for (size_t disc = 2; disc < state.size(); disc++) {
        if(state[1] != state[disc]){
            return false;
        }
    }
    return true;
}

int doGameLoop(const int discs) {
    // Used the vector integer due to a constant requirement placed on the towerSize
    // variable. This will create the array of discs dynamically based on the option
    // selected in chooseDifficulty.
    bool isComplete = false;
    vector<int> discState;
    int moveCount = 0;
    // Put an empty value slot 0
    discState.push_back(0);
    for (int disc = 1; disc <= discs; disc++) {
        // Start all discs on first tower
        discState.push_back(1);
    }
    while (!isComplete) {
        showTowerState(discState);
        cout << "Number of moves: " + to_string(moveCount) << endl;
        isComplete = checkGameState(discState);
        if (!isComplete) {
            moveDisc(discState);
            moveCount++;
        }
    }
    return moveCount;
}

int main() {

    highScores = loadScoreboard();
    displayScoreboard();
    while (gameOptions()) {
        int discs = chooseDifficulty();
        int moveCount = doGameLoop(discs);
        checkHighScore(discs, moveCount);
        displayScoreboard();
    }
    return 0;
}
