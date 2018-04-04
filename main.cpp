#include <string>
#include <iostream>
#include "MainAux.h"
using namespace std;

int main() {
    Game game;

    const char* filePath_player1 = "../player1.rps_board";
    const char* filePath_player2 = "../player2.rps_board";

    endGameMessage endGameMsg = initializeGame(game,filePath_player1,filePath_player2);

    cout << "Message: " << endGameMsg.reason << endl;

    cout << game.boardToString() << endl;

	return 0;
}