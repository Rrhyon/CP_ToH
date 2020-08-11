/*
  Name:             Phillip Tette
  Class:            CIS170L
  Professor:        Penn Wu
  Project Name:     Tower of Hanoi
  Date:             20200807
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string defaultTable[] = {
    "+----------------------------------------------+\n",
    "|              High Score List                 |\n",
    "+----------------------------------------------+\n",
    "| Tower Size | Perfect | High Score | Initials |\n",
    "+----------------------------------------------+\n",
    //"|     3      |     7   |   ----     |    ___   |\n",
    //"|     4      |    15   |   ----     |    ___   |\n",
    //"|     5      |    31   |   ----     |    ___   |\n",
    //"|     6      |    63   |   ----     |    ___   |\n",
    //"|     7      |   127   |   ----     |    ___   |\n",
    //"|     8      |   255   |   ----     |    ___   |\n",
    //"|     9      |   511   |   ----     |    ___   |\n",
    //"|    10      |  1023   |   ----     |    ___   |\n",
    //"+----------------------------------------------+\n"
};

string ruleBook[] = {
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

vector<string> highScoresTable;

int loadScoreBoard(void) {
    char filename[] = "scoreboard.csv";
    fstream scoreBoard;
    string readScores;

    scoreBoard.open(filename, fstream::in);

    // If the scoreboard.txt file does exist, read and display the contents of the file.
    // If the scoreboard.txt file doesn't exist, create the scoreboard.txt file; then read and display the contents of the file.
    if (scoreBoard) {
        cout << "Thank you for playing the Tower of Hanoi, Loading Scoreboard...\n";
        while (getline(scoreBoard, readScores)) {
            highScoresTable.push_back(readScores);
        }
        scoreBoard.close();
    }
    else {
        cout << "You're the first player, creating a new high scores table!\n";
        scoreBoard.open(filename, fstream::in | fstream::out | fstream::trunc);
        for (int i = 0; i < sizeof(defaultTable) / sizeof(defaultTable[0]); i++) {
            scoreBoard << defaultTable[i];
            cout << defaultTable[i];
        }
        scoreBoard.close();
    }
    return 0;
}

void manageScoreboard() {
    //This function will handle the new high scores.
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

    loadScoreBoard();

    gameOptions();

    int towerSize = chooseDifficulty();

    // Used the vector integer due to a constant requirement placed on the towerSize variable.
    // This will create the array of discs dynamically based on the option selected in chooseDifficulty.
    vector<int> discs;
    for (int disc = 1; disc <= towerSize; disc++) {
        discs.push_back(1);
    }
}

