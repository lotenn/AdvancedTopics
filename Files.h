#ifndef EX1_FILES_H
#define EX1_FILES_H

#include "Game.h"
#include "Parser.h"
#include <iostream>
#include <fstream>

/*
 * Validate a given file path contains correct tool positioning commands according to game rules.
 * if all commands are valid, "commands" vector will contain all input commands, parsed to positioningCommand type
 *
 * @args:
 * -filePath = input file contains command for player's tool positioning
 * -commands = vector of commands
 *
 * @ret: endGameMessage type
 * - (NO_POSITIONING_FILE, NO_PLAYER): in case of missing file/ file cannot be opened:
 * - (BAD_POSITIONING_FILE_INVALID, NO_PLAYER, lineNumber, -1): in case of syntax or basic  game rule related error
 * - (BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION, NO_PLAYER, lineNumber, -1): in case a cell was used twice
 * - (BAD_POSITIONING_FILE_TOO_MANY_TOOLS, NO_PLAYER, lineNumber, -1): too many tools of same type
 * - (BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS, NO_PLAYER, lineNumber, -1): not enough flags
 * - (NO_WINNER, NO_PLAYER): no winner at the end of this positioning
 */
endGameMessage validatePositioningFile(const char* filePath, vector<PositioningCommand>& commands);
/*
 * Parse a file of a player's game commands.
 * @args:
 * -filePath = input file contains player's commands
 * -commands = vector of commands
 *
 * @ret: endGameMessage type
 * - (NO_MOVE_FILE, NO_PLAYER): in case of missing / corrupted file
 * - (NO_WINNER, NO_PLAYER): else
 */
endGameMessage parsingMoveFile(const char *filePath, vector<Command> &commands);
/*
 *Generates end game output file and prints end game message.
 * in case file is not opened, error message will be printed to the console
 */
void generateOutputFile(const char *outputFilePath, string winner, string reason, string board);

#endif //EX1_FILES_H
