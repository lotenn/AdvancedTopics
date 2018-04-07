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
        if(line.find_first_not_of(" \t\n\r") == line.npos) continue;
        posCmd = parser.parsePositioningCommandLine(line);
        //bad syntax
        if(posCmd.type == INVALID_POSITIONING_COMMAND){
            positioningFile.close();
            return createEndGameMessage(BAD_POSITIONING_FILE_INVALID, NO_PLAYER, lineNumber, -1);
        }
        Cell cell = posCmd.source;
        int row = getRow(cell), col = getCol(cell);

        //current cell already contains same winner's tool
        if (alreadyPositioned[row][col]){
            positioningFile.close();
            return createEndGameMessage(BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION, NO_PLAYER, lineNumber, -1);
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
                return createEndGameMessage(BAD_POSITIONING_FILE_TOO_MANY_TOOLS, NO_PLAYER, lineNumber, -1);
            }
        }
        //joker command
        else{
            jokerCounter--;
            //out of tools
            if (jokerCounter<0){
                positioningFile.close();
                return createEndGameMessage(BAD_POSITIONING_FILE_TOO_MANY_TOOLS, NO_PLAYER, lineNumber, -1);}
        }
        commands.push_back(posCmd);
        alreadyPositioned[row][col] = true;
        lineNumber++;
    }
    //not enough flags positioned
    if(flagCounter!=0){
        positioningFile.close();
        return createEndGameMessage(BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS, NO_PLAYER, lineNumber, -1);
    }
    positioningFile.close();
    return createEndGameMessage(NO_WINNER, NO_PLAYER);
}

endGameMessage parsingMoveFile(const char *filePath, vector<Command> &commands){
    ifstream movesFile;
    movesFile.open(filePath, ios::in);
    if(!movesFile.is_open()) {return createEndGameMessage(NO_MOVE_FILE, NO_PLAYER);}

    Parser parser;
    string line;
    Command cmd;
    while(getline(movesFile, line)){
        if(line.find_first_not_of(" \t\n\r") == line.npos) {continue;}
        cmd = parser.parseMoveCommand(line);
        commands.push_back(cmd);
    }
    movesFile.close();
    return createEndGameMessage(NO_WINNER, NO_PLAYER);
}

void generateOutputFile(const char *outputFilePath, string winner, string reason, string board){
    ofstream outputFile;
    //todo: check if the file is opened properly
    outputFile.open(outputFilePath);
    outputFile << "Winner: " << winner << endl;
    outputFile << "Reason: " << reason << endl;
    outputFile << endl;
    outputFile << board << endl;
    outputFile.close();
}

