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
    //bad input error printing
    if(badInputFile(player1Msg.reason))
        printBadInputFile(player1Msg.reason, PLAYER_1);

    //draw
    if(player1Msg.reason != NO_WINNER && player2Msg.reason != NO_WINNER){
        return createEndGameMessage
                (DRAW_POSITIONING_FILE_BOTH_PLAYERS, NO_PLAYER, player1Msg.errorLine1, player2Msg.errorLine1);
    }
    //player 1 has lost due to bad position file
    else if(player1Msg.reason != NO_WINNER){
        player1Msg.winner = PLAYER_2;
        return player1Msg;
    }
    //player 2 has lost due to bad position file
    else if(player2Msg.reason != NO_WINNER){
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

endGameMessage playGame(Game& game, const char* filePath_player1, const char* filePath_player2){
    vector<Command> commandsPlayer1;
    vector<Command> commandsPlayer2;
    endGameMessage player1Msg = parsingMoveFile(filePath_player1, commandsPlayer1);
    //PLAYER1 has no moves file
    if(player1Msg.reason == NO_MOVE_FILE){
        player1Msg.winner = PLAYER_1;
        return player1Msg;
    }
    //PLAYER 2 has no moves file
    endGameMessage player2Msg = parsingMoveFile(filePath_player2, commandsPlayer2);
    if(player2Msg.reason == NO_MOVE_FILE){
        player2Msg.winner = PLAYER_1;
        return player2Msg;
    }

    int player1MoveLine = 0, player2MoveLine = 0;
    endGameMessage gameMsg = createEndGameMessage(NO_WINNER, NO_PLAYER);
    executeCommandMessage moveMsg;
    while(gameMsg.reason == NO_WINNER){
        //both players have no more moves
        if(!(player1MoveLine < (int)commandsPlayer1.size()) && !(player2MoveLine < (int)commandsPlayer2.size())){
            gameMsg = createEndGameMessage(DRAW_NO_MORE_MOVES, NO_PLAYER);
            break;
        }
        //player1 still has moves
        if(player1MoveLine < (int)commandsPlayer1.size()) {
            moveMsg = game.playTurn(commandsPlayer1[player1MoveLine], PLAYER_1);
            player1MoveLine++;
            //if the move is illegal
            if(moveMsg != EXECUTE_COMMAND_SUCCESS){
                gameMsg = createEndGameMessage(toReason(moveMsg), PLAYER_2, player1MoveLine, -1);
                break;
            }
            gameMsg = game.checkGameWinner();
            //the move led to end of the game
            if(gameMsg.reason != NO_WINNER)
                break;
        }
        //player2 still has moves
        if(player2MoveLine < (int)commandsPlayer2.size()) {
            moveMsg = game.playTurn(commandsPlayer2[player2MoveLine], PLAYER_2);
            player2MoveLine++;
            //if the move is illegal
            if(moveMsg != EXECUTE_COMMAND_SUCCESS){
                gameMsg = createEndGameMessage(toReason(moveMsg), PLAYER_1, player2MoveLine, -1);
                break;
            }
            gameMsg = game.checkGameWinner();
        }
    }
    return gameMsg;
}

bool badInputFile(endGameReason reason){
    return (reason == BAD_POSITIONING_FILE_INVALID || reason == BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS ||
            reason == BAD_POSITIONING_FILE_TOO_MANY_TOOLS || reason == BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION ||
            reason == BAD_MOVE_FILE_NOT_YOUR_TOOL || reason == BAD_MOVE_FILE_TOOL_CANT_MOVE ||
            reason == BAD_MOVE_FILE_CELL_OCCUPIED || reason == BAD_MOVE_FILE_NOT_JOKER || reason == BAD_MOVE_FILE_INVALID);
}

void printNoPositioningFile(endGameMessage endGameMsg){
    cout << "No Positioning input file for " << toString(endGameMsg.winner) << endl;
}

void printNoMoveFile(endGameMessage endGameMsg){
    cout << "No Moves input file for " << toString(endGameMsg.winner) << endl;
}

void printBadInputFile(endGameReason reason, playerEnum player){
    string errorMessage = getBadInputFileMessage(reason);
    cout << "Bad input file: " << errorMessage << " - "+toString(player)<< endl;
}

void endGame(Game& game, endGameMessage endGameMsg, const char* outputFilePath){
    if (endGameMsg.reason == NO_POSITIONING_FILE){
        printNoPositioningFile(endGameMsg);
        return;
    }
    else if(endGameMsg.reason == NO_MOVE_FILE){
        printNoMoveFile(endGameMsg);
        return;
    }
    else{
        game.raisePlayerScore(1, endGameMsg.winner);
        if(badInputFile(endGameMsg.reason))
            printBadInputFile(endGameMsg.reason, getOpposite(endGameMsg.winner));
        string winner, reason, board;
        winner = getWinnerString(endGameMsg.winner);
        reason = getReasonString(endGameMsg);
        board = game.boardToString();
        generateOutputFile(outputFilePath, winner, reason, board);
    }
}