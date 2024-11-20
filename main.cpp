#include <iostream>

#include <string>

#include <cstdlib>

#include <ctime>

#include <termios.h>

#include <unistd.h>

using namespace std;


// Function to input

string HiddenInput() {

//Hiddedninput will used to hide player inputs to prevent cheating

string input;

struct termios oldt, newt;


// The Function that will turn off the display input for certain entries

tcgetattr(STDIN_FILENO, &oldt);

newt = oldt;

newt.c_lflag &= ~(ECHO);

tcsetattr(STDIN_FILENO, TCSANOW, &newt);


// Get players input

cin >> input;


// Restore terminal echo

tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

cout << endl;

// once all desire hidden are gather echo display will be turn back on

return input;

}


class RockPaperScissors {

private:

const string choices[3] = {"1", "2", "3"}; // Array for entries

string player[2]; // Array to store both player and computer entries

int results[2]; // Array for results: 0 for draw, 1 for win, -1 for loss


int getChoiceIndex(const string& choice) {

for (int i = 0; i < 3; ++i) {

if (choices[i] == choice)

return i;

}

return -1;

}

// this is the Function that will take all entered input and determine a winner

void determineWinner() {

int index1 = getChoiceIndex(player[0]);

int index2 = getChoiceIndex(player[1]);


if (index1 == index2) {

results[0] = results[1] = 0; // draw

} else if ((index1 + 1) % 3 == index2) {

results[0] = -1; // Player 1 loses, and player 2/computer wins

results[1] = 1;

} else {

results[0] = 1; // Player 1 wins, and player 2/computer loses

results[1] = -1;

}

}


public:

RockPaperScissors(const string& player1Choice, const string& player2Choice) {

player[0] = player1Choice;

player[1] = player2Choice;

// error if the user enters anything beside 1, 2, or 3 this will raise and error

try {

if (getChoiceIndex(player[0]) == -1 || getChoiceIndex(player[1]) == -1) {

throw invalid_argument("Invalid choice entered. Please enter 1 for rock, 2 for paper or 3 for rock:");

}

determineWinner();

} catch (const invalid_argument& e) {

cerr << "Error: " << e.what() << endl;

results[0] = results[1] = -2; // Error code for invalid input

}

}

// Used a boolean statement so that if player against the computer different messages will display

void displayResult(bool theComputer) const {

if (results[0] == -2) {

cout << "Game could not be completed due to invalid input." << endl;

return;

}

// Command that will display what each player/computer entered

cout << "With unwavering resolve, Player 1 has chosen Option " << player[0] << "! The adventure is now in motion" << endl;

if (theComputer)

cout << "The Digital Titan has made their choice " << player[1] << " monumental decision that echoes through the realms of code and data!" << endl;

else

cout << "After Player 1's bold choice, Player 2 steps forward with their own ..." << player[1] << "! The forces align, and the fate of the game grows ever more intense!" <<endl;

// If/else statment will be use to determine the winner based off each entry

if (results[0] == 0) {

cout << "The forces are equal; fate has decreed a draw!" << endl;

} else if (results[0] == 1) {

cout << "\nVictory is claimed! Player One ascends as the true champion of rock paper scissors!" << endl;

} else if (theComputer) {

// "theComputer" will be used as pointer

cout << "\nThe Machine has claimed victory, its cold, calculated might overwhelms the battlefield!" << endl; // Epic message if computer wins

} else {

cout << "\nVictory is claimed! Player two ascends as the true champion of rock paper scissors!" << endl;

}

}

};


string getComputerChoice() {

srand(static_cast<unsigned int>(time(nullptr)));

const string choices[3] = {"1", "2", "3"};

int randomIndex = rand() % 3;

return choices[randomIndex];

}


int main() {
    int mode;

    // need a string to use for while loops

    char repeat = 'y';

    cout << "Enter the battlefield and forge your legacy \n \nEnter 1 for Mortal Hero vs. The Digital Titan\nEnter 2 for an epic clash of two mortal champions, locked in a battle for glory ";

    cin >> mode;

    cin.ignore(); // Clear newline character from the input

    // Y is the command that will be used if players would like to play again

    while (repeat == 'y' || repeat == 'Y') {

        if (mode == 1) {

            string playerChoice;

            cout << "\nBrave soul, enter the path you will take:\n \n1 for rock, 2 for paper or 3 for scissors: ";

            playerChoice = HiddenInput();


            string computerChoice = getComputerChoice();

            cout << "\n The Machine has cast its decision!" << endl;


            RockPaperScissors game(playerChoice, computerChoice);

            game.displayResult(true);

            // if playing against computer "true" will be used to diplay a different message


        }else if (mode == 2) {

            string player1Choice, player2Choice;

            cout << "Brave soul, enter the path you will take: \n1 for rock, 2 for paper or 3 for scissors: ";

            player1Choice = HiddenInput();

            //player 1 enters their choice

            cout << "\nAdversary, it is your time make your fateful choice: \n1 for rock, 2 for paper or 3 for scissors: ";

            player2Choice = HiddenInput();

            //player 2 enters their choice

            RockPaperScissors game(player1Choice, player2Choice);

            game.displayResult(false);

            // if playing against another player "false" will be used to display a different message



            // command will prompt asking if they would like to play again


        } else {

            cout << "Invalid game mode selected." << endl;

        }

        cout << "\nIs your spirit ready for another round of the glorious round of Rock, Paper, Scissors?\nPress ""'y'" " yes or for ""'n'" " no ";

        cin>> repeat;

    }

    cout<<"\n Your tale is far from over, bold player! Rest now, but remember: the world of Rock, Paper, Scissors awaits your return. Return when the call of adventure stirs once more!";

    return 0;
}
