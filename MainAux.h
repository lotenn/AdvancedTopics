#ifndef EX1_MAINAUX_H
#define EX1_MAINAUX_H

#include <string>
#include <string.h>
#include "Files.h"

using namespace std;

void printNoPositioningFile(endGameMessage endGameMsg);

void printNoMoveFile(endGameMessage endGameMsg);

bool badInputFile(endGameReason reason);

void printBadInputFile(endGameMessage msg);

endGameMessage initializeGame(Game& game, const char* filePath_player1, const char* filePath_player2);

endGameMessage playGame(Game& game, const char* filePath_player1, const char* filePath_player2);

void endGame(Game& game, endGameMessage endGameMsg, const char* outputFilePath);

#endif //EX1_MAINAUX_H