#include <string>
#include <iostream>
#include "MainAux.h"
using namespace std;

int main() {
    Game game;
    vector<PositioningCommand> player1PosCommands;
    const char* filePath_player1 = "../player1.rps_board";
    const char* filePath_player2 = "../player2.rps_board";

    endGameMessage endGameMsg = initializeGame(game,filePath_player1,filePath_player2);
    if (endGameMsg.reason = NO_POSITIONING_FILE){
        printBadPositionMessage(endGameMsg);
        return 0;
    }

    else if(endGameMsg.winner == DRAW){
        if(endGameMsg.reason == D){

        }
    }



	return 0;
}