#ifndef EX1_FILES_H
#define EX1_FILES_H

#include "Game.h"
#include "Parser.h"
#include <iostream>
#include <fstream>

endGameMessage validatePositioningFile(const char* filePath, vector<PositioningCommand>& commands);

endGameMessage validateMoveFile(const char *filePath, vector<Command> &commands);

#endif //EX1_FILES_H
