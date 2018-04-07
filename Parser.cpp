#include "Parser.h"

Command Parser::parseMoveCommand(string commandLine) {
    vector<commandType> steps;
    int srcX, srcY, targetX, targetY, jokerX, jokerY;
    char new_rep;
    if(commandLine.empty()) {
        steps = {INVALID_MOVE_COMMAND};
        return createCommand(steps, 0, 0, 0, 0, 0, 0, 0);
    }

    char *str = const_cast<char*>(commandLine.c_str());
    char *tokens[9];
    const char delim[] = " \t\n\r";


    tokens[0] = strtok(str, delim);
    for (int i = 1; i < 9; i++) {tokens[i] = strtok(NULL, delim);}

    //9th token  - INVALID_MOVE_COMMAND command
    if (tokens[8] != NULL || tokens[0] == NULL) {
        steps = {INVALID_MOVE_COMMAND};
        return createCommand(steps, 0, 0, 0, 0, 0, 0, 0);
    }
    //first 4 arguments are not valid numbers in range
    if (!isNumInRange(tokens[0], 1, M) || !isNumInRange(tokens[1], 1, N) || !isNumInRange(tokens[2], 1, M) ||
        !isNumInRange(tokens[3], 1, N)) {
        steps = {INVALID_MOVE_COMMAND};
        return createCommand(steps, 0, 0, 0, 0, 0, 0, 0);
    }
    //There is a 5th argument (joker command)
    else if (tokens[4] != NULL) {
        if (strcmp(tokens[4], "J:") || !isNumInRange(tokens[5], 1, M) || !isNumInRange(tokens[6], 1, N) ||
            !isCharArrValidJokerToolType(tokens[7])) {
            steps = {INVALID_MOVE_COMMAND};
            return createCommand(steps, 0, 0, 0, 0, 0, 0, 0);
        }
        //valid joker command
        else {
            steps = {MOVE_COMMAND, JOKER_COMMAND};
            srcX = atoi(tokens[0]), srcY = atoi(tokens[1]), targetX = atoi(tokens[2]), targetY = atoi(tokens[3]);
            jokerX = atoi(tokens[5]), jokerY = atoi(tokens[6]);
            new_rep = *(tokens[7]);
            return createCommand(steps, srcX, srcY, targetX, targetY, jokerX, jokerY, new_rep);
        }
    }
    //valid move command, no joker command that follows
    else {
        steps = {MOVE_COMMAND};
        srcX = atoi(tokens[0]), srcY = atoi(tokens[1]), targetX = atoi(tokens[2]), targetY = atoi(tokens[3]);
        return createCommand(steps, srcX, srcY, targetX, targetY, 0, 0, 0);
    }
}

PositioningCommand Parser::parsePositioningCommandLine(string commandLine) {
    if(commandLine.empty()) {return createPositioningCommand('\0', 0, 0, INVALID_POSITIONING_COMMAND);}
    char *str = const_cast<char*>(commandLine.c_str());
    char *tokens[5];
    const char delim[] = " \t\n\r";

    tokens[0] = strtok(str, delim);
    for (int i = 1; i < 5; i++) {
        tokens[i] = strtok(NULL, delim);
    }
    //valid positioning command
    if (isCharArrValidToolType(tokens[0]) && isNumInRange(tokens[1], 1, M) && isNumInRange(tokens[2], 1, N) && tokens[3]==NULL){
        char tool = *(tokens[0]);
        int srcX = atoi(tokens[1]), srcY = atoi(tokens[2]);
        return createPositioningCommand(tool, srcX, srcY ,REGULAR_POSITIONING_COMMAND);
    }

    else if(tokens[0]!=NULL && !strcmp(tokens[0], "J") && isNumInRange(tokens[1], 1, M) && isNumInRange(tokens[2], 1, N) && isCharArrValidJokerToolType(tokens[3])){
        char tool = *(tokens[3]);
        int srcX = atoi(tokens[1]), srcY = atoi(tokens[2]);
        return createPositioningCommand(tool, srcX, srcY, JOKER_POSITIONING_COMMAND);
    }
    else{
        return createPositioningCommand('\0', 0, 0, INVALID_POSITIONING_COMMAND);
    }
}
