#include <string>
#include <iostream>
#include "MainAux.h"
using namespace std;

int main() {
    Game game;
    vector<PositioningCommand> player1PosCommands;
    const char* filePath_player1 = "../player1.rps_board";
    const char* filePath_player2 = "../player2.rps_board";
    const char* outputFilePath = "../rps.output";

    endGameMessage endGameMsg = initializeGame(game,filePath_player1,filePath_player2);
    if(endGameMsg.reason != NO_WINNER){
        endGame(game, endGameMsg, outputFilePath);
        return 0;
    }

    //endGameMsg = playGame();
    endGame(game, endGameMsg, outputFilePath);

	return 0;
}