#include "MainAux.h"

endGameMessage initializeGame(Game& game, const char* filePath_player1, const char* filePath_player2){
    game.resetGameBoard();
    vector<PositioningCommand> posCommandsPlayer1;
    vector<PositioningCommand> posCommandsPlayer2;
    endGameMessage player1Msg = validatePositioningFile(filePath_player1, posCommandsPlayer1);
    //PLAYER1 has no positioning file
    if(player1Msg.reason == NO_POSITIONING_FILE) {
        player1Msg.winner = PLAYER_1;
        return player1Msg;
    }
    //PLAYER 2 has no positioning file
    endGameMessage player2Msg = validatePositioningFile(filePath_player2, posCommandsPlayer2);
    if(player2Msg.reason == NO_POSITIONING_FILE){
        player2Msg.winner = PLAYER_2;
        return player2Msg;
    }
    //draw
    if(player1Msg.reason!=NO_WINNER && player2Msg.reason!=NO_WINNER){
        return createEndGameMessage
                (DRAW_POSITIONING_FILE_BOTH_PLAYERS, NO_PLAYER, player1Msg.errorLine1, player2Msg.errorLine1);
    }
    //player 1 has lost due to bad position file
    else if(player1Msg.reason != NO_WINNER){
        game.raisePlayerScore(1, PLAYER_2);
        player1Msg.winner = PLAYER_2;
        return player1Msg;
    }
    //player 2 has lost due to bad position file
    else if(player2Msg.reason != NO_WINNER){
        game.raisePlayerScore(1, PLAYER_1);
        player2Msg.winner = PLAYER_1;
        return player2Msg;
    }
    //no file problems, placing tool as specified
    else{
        game.setPlayerTools(posCommandsPlayer1, PLAYER_1);
        game.setPlayerTools(posCommandsPlayer2, PLAYER_2);
        return game.checkGameWinner();
    }
}

void printBadPositionMessage(endGameMessage endGameMsg){
    string msgStrings[]
}