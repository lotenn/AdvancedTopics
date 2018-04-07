#include <string>
#include <iostream>
#include "MainAux.h"
using namespace std;

int main() {
    Game game;
    vector<PositioningCommand> player1PosCommands;
    const char* positioningFilePath_player1 = "../player1.rps_board";
    const char* positioningFilePath_player2 = "../player2.rps_board";
    const char* outputFilePath = "../rps.output";

    endGameMessage endGameMsg = initializeGame(game,positioningFilePath_player1,positioningFilePath_player2);
    if(endGameMsg.mainReason != NO_WINNER){
        endGame(game, endGameMsg, outputFilePath);
        return 0;
    }

    const char* movesFilePath_player1 = "../player1.rps_moves";
    const char* movesFilePath_player2 = "../player2.rps_moves";

    endGameMsg = playGame(game, movesFilePath_player1, movesFilePath_player2);
    endGame(game, endGameMsg, outputFilePath);

	return 0;
}