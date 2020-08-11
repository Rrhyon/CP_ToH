/*
  Name:             Phillip Tette
  Class:            CIS170L
  Professor:        Penn Wu
  Project Name:     Tower of Hanoi
  Date:             20200810
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const vector<vector<string>> defaultTable = {
    {"3","0","XXX"},
    {"4","0","XXX"},
    {"5","0","XXX"},
    {"6","0","XXX"},
    {"7","0","XXX"},
    {"8","0","XXX"},
    {"9","0","XXX"},
    {"10","0","XXX"}
};

const string tableHeader[] = {
    "+----------------------------------------------+\n",
    "|              High Score List                 |\n",
    "+----------------------------------------------+\n",
    "| Tower Size | Perfect | High Score | Initials |\n",
    "+----------------------------------------------+\n"
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

// "3,8,FOO" -> {"3", "8", "FOO"}

vector<string> parseCSV(const string &line) {
    vector<string> result;
    stringstream record(line);
    string item;

    while (getline(record, item, ',')) {
        result.push_back(item);
    }
    return result;
}

vector<vector<string>> loadScoreboard(string filename) {
    vector<vector<string>> scores;
    fstream file;
    string line;

    file.open(filename, fstream::in);

    // If the scoreboard.txt file does exist, read and display the contents of the file.
    // If the scoreboard.txt file doesn't exist, create the scoreboard.txt file.
    if (file) {
        cout << "Thank you for playing the Tower of Hanoi, Loading Scoreboard...\n";
        while (getline(file, line)) {
            scores.push_back(parseCSV(line));
        }
    }
    else {
        cout << "You're the first player, creating a new high scores table!\n";
        file.open(filename, fstream::in | fstream::out | fstream::trunc);
        // The magic happens, NO IT DOESN'T
        for (int i = 0; i < defaultTable.size(); i++) {
            file << defaultTable[i][0] + "," + defaultTable[i][1] + "," + defaultTable[i][2] << endl;
        }
        scores = defaultTable;
    }
    file.close();
    return scores;
}

int printScoreboard() {
    // Read and display the contents of the scoreboard. 
    for (int i = 0; i < sizeof(tableHeader) / sizeof(tableHeader[0]); i++) {
        cout << tableHeader[i];
    }
    int fu = 0;
    return fu;
}

void manageScoreboard() {
    // This function will handle the new high scores.
    char filename[] = "scoreboard.csv";
    fstream scoreBoard;
    string highScoreInitials;

    cout << "Congratulations, you have the new high score!!!" << endl;
    cout << "Please enter your initials: ";
    cin >> highScoreInitials;

    scoreBoard.open(filename, fstream::out | fstream::trunc);


}

bool isValidOption(string choice, vector<string> values) {
    // Will validate all input assuming it's a string.
    return find(values.begin(), values.end(), choice) != values.end();
}

string capsMe(string lowercaseString) {
    // Will uppercase any string input.
    for (unsigned int i = 0; i < lowercaseString.size(); i++) {
        lowercaseString.at(i) = toupper(lowercaseString.at(i));
    }
    return lowercaseString;
}

void gameOptions() {
    string selected;
    // This function will allow the player to choose how to proceed once the game is started.
    vector<string> options = { "P", "R", "Q" };
    while (!isValidOption(selected, options)) {
        cout << "Please select one of the following menu options.\n";
        cout << "    P to Play, R for Rules, or Q to quit: ";
        cin >> selected; selected = capsMe(selected);
    }
    if (selected == "P") {
        cout << "\n        Excellent, let's get started!!!\n\n";
    }
    else if (selected == "R") {
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
        cout << "Select the numbers of discs you would like to start with (3-10): ";
        cin >> discQuantity;
    }
    return stoi(discQuantity);
}

int main() {
    vector<vector<string>> highScores = loadScoreboard("scoreboard.csv");
    printScoreboard();
    gameOptions();

    int towerSize = chooseDifficulty();

    // Used the vector integer due to a constant requirement placed on the towerSize variable.
    // This will create the array of discs dynamically based on the option selected in chooseDifficulty.
    vector<int> discs;
    for (int disc = 1; disc <= towerSize; disc++) {
        discs.push_back(1);
    }
}

