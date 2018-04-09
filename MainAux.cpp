#include "MainAux.h"

bool badPositioningFile(endGameReason reason){
    return (reason == BAD_POSITIONING_FILE_INVALID || reason == BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS ||
            reason == BAD_POSITIONING_FILE_TOO_MANY_TOOLS || reason == BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION ||
            reason == DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS);
}

void printNoPositioningFile(endGameMessage endGameMsg){
    cout << "No Positioning input file for " << toString(endGameMsg.winner) << endl;
}

bool badMovesFile(endGameReason reason){
    return (reason == BAD_MOVE_FILE_NOT_YOUR_TOOL || reason == BAD_MOVE_FILE_TOOL_CANT_MOVE ||
            reason == BAD_MOVE_FILE_CELL_OCCUPIED || reason == BAD_MOVE_FILE_NOT_JOKER || reason == BAD_MOVE_FILE_INVALID);
}

void printNoMoveFile(endGameMessage endGameMsg){
    cout << "No Moves input file for " << toString(endGameMsg.winner) << endl;
}

bool badInputFile(endGameReason reason){
    return (badPositioningFile(reason) || badMovesFile(reason));
}

void printBadInputFile(endGameMessage msg){
    string errorMessage;
    string inputType = badPositioningFile(msg.mainReason) ? "Positioning" : "Moves";
    string msgPrefix = "Bad "+ inputType +" input file: ";
    if(msg.mainReason != DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS) {
        errorMessage = getBadInputFileMessage(msg.mainReason);
        cout << msgPrefix << errorMessage << " - " + toString(getOpposite(msg.winner)) << endl;
    }
    else{
        errorMessage = getBadInputFileMessage(msg.reason1);
        cout << msgPrefix << errorMessage << " - " + toString(PLAYER_1) << endl;
        errorMessage = getBadInputFileMessage(msg.reason2);
        cout << msgPrefix << errorMessage << " - " + toString(PLAYER_2) << endl;
    }
}

endGameMessage initializeGame(Game& game, const char* filePath_player1, const char* filePath_player2){
    game.resetGameBoard();
    vector<PositioningCommand> posCommandsPlayer1;
    vector<PositioningCommand> posCommandsPlayer2;
    endGameMessage player1Msg = validatePositioningFile(filePath_player1, posCommandsPlayer1);
    //PLAYER1 has no positioning file
    if(player1Msg.mainReason == NO_POSITIONING_FILE) {
        player1Msg.winner = PLAYER_1;
        return player1Msg;
    }
    //PLAYER 2 has no positioning file
    endGameMessage player2Msg = validatePositioningFile(filePath_player2, posCommandsPlayer2);
    if(player2Msg.mainReason == NO_POSITIONING_FILE){
        player2Msg.winner = PLAYER_2;
        return player2Msg;
    }

    //draw
    if(player1Msg.mainReason != NO_WINNER && player2Msg.mainReason != NO_WINNER){
        return createEndGameMessage
                (DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS, player1Msg.mainReason, player2Msg.mainReason,
                 NO_PLAYER, player1Msg.errorLine1, player2Msg.errorLine1);
    }
        //player 1 has lost due to bad position file
    else if(player1Msg.mainReason != NO_WINNER){
        player1Msg.winner = PLAYER_2;
        return player1Msg;
    }
        //player 2 has lost due to bad position file
    else if(player2Msg.mainReason != NO_WINNER){
        player2Msg.winner = PLAYER_1;
        return player2Msg;
    }
        //no file problems, placing tool as specified
    else{
        game.setPlayerTools(posCommandsPlayer1, PLAYER_1);
        game.setPlayerTools(posCommandsPlayer2, PLAYER_2);
        endGameMessage msg = game.checkGameWinner();
        if(msg.mainReason == DRAW_NO_MORE_MOVES)
            msg.mainReason = DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS;
        return msg;
    }
}

executeCommandMessage playTurn(Game& game, Command cmd, playerEnum player){
    game.setCurrentPlayer(player);
    return game.executeCommand(cmd);
}

endGameMessage playGame(Game& game, const char* filePath_player1, const char* filePath_player2){
    vector<Command> commandsPlayer1;
    vector<Command> commandsPlayer2;
    endGameMessage player1Msg = parsingMoveFile(filePath_player1, commandsPlayer1);
    //PLAYER1 has no moves file
    if(player1Msg.mainReason == NO_MOVE_FILE){
        player1Msg.winner = PLAYER_1;
        return player1Msg;
    }
    //PLAYER 2 has no moves file
    endGameMessage player2Msg = parsingMoveFile(filePath_player2, commandsPlayer2);
    if(player2Msg.mainReason == NO_MOVE_FILE){
        player2Msg.winner = PLAYER_2;
        return player2Msg;
    }

    int player1MoveLine = 0, player2MoveLine = 0;
    endGameMessage gameMsg;
    executeCommandMessage moveMsg;
    Command cmd;
    while(player1MoveLine < (int)commandsPlayer1.size() || player2MoveLine < (int)commandsPlayer2.size()){
        //player1 still has moves
        if(player1MoveLine < (int)commandsPlayer1.size()){
            cmd = commandsPlayer1[player1MoveLine];
            player1MoveLine++;
            for(;cmd.currentStep < (int)cmd.steps.size(); cmd.currentStep++){
                moveMsg = playTurn(game, cmd, PLAYER_1);
                //if the move is illegal
                if(moveMsg != EXECUTE_COMMAND_SUCCESS)
                    return createEndGameMessage(toReason(moveMsg), PLAYER_2, player1MoveLine, -1);
                //if the current step didnt change the joker - check for winner
                if(cmd.steps[cmd.currentStep] != JOKER_COMMAND){
                    gameMsg = game.checkGameWinner();
                    //the move led to end of the game
                    if(gameMsg.mainReason != NO_WINNER)
                        return gameMsg;
                }
            }
        }
        //player2 still has moves
        if(player2MoveLine < (int)commandsPlayer2.size()) {
            cmd = commandsPlayer2[player2MoveLine];
            player2MoveLine++;
            for(; cmd.currentStep < (int)cmd.steps.size(); cmd.currentStep++){
                moveMsg = playTurn(game, cmd, PLAYER_2);
                //if the move is illegal
                if(moveMsg != EXECUTE_COMMAND_SUCCESS){
                    return createEndGameMessage(toReason(moveMsg), PLAYER_1, player2MoveLine, -1);
                }
                //if the current step didnt change the joker - check for winner
                if(cmd.steps[cmd.currentStep] != JOKER_COMMAND){
                    gameMsg = game.checkGameWinner();
                    //the move led to end of the game
                    if(gameMsg.mainReason != NO_WINNER)
                        return gameMsg;
                }
            }
        }
    }
    //no more moves for both players
    return createEndGameMessage(DRAW_NO_MORE_MOVES, NO_PLAYER);
}

void endGame(Game& game, endGameMessage endGameMsg, const char* outputFilePath){
    if (endGameMsg.mainReason == NO_POSITIONING_FILE){
        printNoPositioningFile(endGameMsg);
        return;
    }
    else if(endGameMsg.mainReason == NO_MOVE_FILE){
        printNoMoveFile(endGameMsg);
        return;
    }
    else{
        game.raisePlayerScore(1, endGameMsg.winner);
        if(badInputFile(endGameMsg.mainReason))
            printBadInputFile(endGameMsg);
        string winner, reason, board;
        winner = getWinnerString(endGameMsg.winner);
        reason = getReasonString(endGameMsg);
        board = game.boardToString();
        generateOutputFile(outputFilePath, winner, reason, board);
    }
}