#include "Files.h"

endGameMessage validatePositioningFile(const char* filePath, vector<PositioningCommand>& commands) {
    ifstream positioningFile;
    positioningFile.open(filePath, ios::in);
    if(!positioningFile.is_open()) {return createEndGameMessage(NO_POSITIONING_FILE, NO_PLAYER);}

    int lineNumber = 1;
    bool alreadyPositioned[N][M];
    memset(alreadyPositioned, 0, sizeof(bool)*M*N);
    int rockCounter = NUM_OF_R, scissorsCounter = NUM_OF_S, paperCounter = NUM_OF_P, flagCounter = NUM_OF_F, bombCounter = NUM_OF_B, jokerCounter = NUM_OF_J;

    string line;
    Parser parser;
    PositioningCommand posCmd;
    while(getline(positioningFile, line)){
        posCmd = parser.parsePositioningCommandLine(line);
        if(posCmd.type == INVALID_POSITIONING_COMMAND){
            positioningFile.close();
            return createEndGameMessage(BAD_POSITIONING_FILE_PLAYER, NO_PLAYER, lineNumber, -1);
        }
        Cell cell = posCmd.source;
        int row = getRow(cell), col = getCol(cell);

        //current cell already contains same player's tool
        if (alreadyPositioned[row][col]){
            positioningFile.close();
            return createEndGameMessage(BAD_POSITIONING_FILE_PLAYER, NO_PLAYER, lineNumber, -1);
        }
        //regular command
        if(posCmd.type == REGULAR_POSITIONING_COMMAND){
            if(posCmd.toolType == 'R') {rockCounter--;}
            else if(posCmd.toolType == 'S') {scissorsCounter--;}
            else if(posCmd.toolType == 'P') {paperCounter--;}
            else if(posCmd.toolType == 'F') {flagCounter--;}
            else  {bombCounter--;}

            //out of tools
            if(rockCounter<0 || scissorsCounter<0 || paperCounter<0 || flagCounter<0 || bombCounter<0){
                positioningFile.close();
                return createEndGameMessage(BAD_POSITIONING_FILE_PLAYER, NO_PLAYER, lineNumber, -1);
            }
        }
        //joker command
        else{
            jokerCounter--;
            //out of tools
            if (jokerCounter<0){
                positioningFile.close();
                return createEndGameMessage(BAD_POSITIONING_FILE_PLAYER, NO_PLAYER, lineNumber, -1);}
        }
        commands.push_back(posCmd);
        alreadyPositioned[row][col] = true;
        lineNumber++;
    }
    //not enough flags positioned
    if(flagCounter!=0){
        positioningFile.close();
        return createEndGameMessage(BAD_POSITIONING_FILE_PLAYER, NO_PLAYER, lineNumber, -1);
    }
    positioningFile.close();
    return createEndGameMessage(NO_WINNER, NO_PLAYER);
}

endGameMessage validateMoveFile(const char *filePath, vector<Command> &commands){
    ifstream movesFile;
    movesFile.open(filePath, ios::in);
    if(!movesFile.is_open()) {return createEndGameMessage(NO_MOVE_FILE, NO_PLAYER);}

    int lineNumber = 1;
    Parser parser;
    string line;
    Command cmd;
    while(getline(movesFile, line)){
        cmd = parser.parseMoveCommand(line);
        if(cmd.type == INVALID_MOVE_COMMAND){
            movesFile.close();
            return createEndGameMessage(BAD_MOVE_FILE_PLAYER, NO_PLAYER, lineNumber, -1);
        }
        commands.push_back(cmd);
        lineNumber++;
    }
    movesFile.close();
    return createEndGameMessage(NO_WINNER, NO_PLAYER);
}

void printBoard(ofstream& outputFile, Game& game) {
    if(outputFile.is_open()){
        for (int row = M-1; row >= 0; row--) {
            for (int col = 0; col < N; col++){
                outputFile << game.gameBoard[row][col]->toChar();
            }
            outputFile << endl;
        }
    }
}