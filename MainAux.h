#ifndef EX1_MAINAUX_H
#define EX1_MAINAUX_H

#include <string>
#include <string.h>
#include "Files.h"

using namespace std;

endGameMessage initializeGame(Game& game, const char* filePath_player1, const char* filePath_player2);

void printNoPositioningFile(endGameMessage endGameMsg);

void printNoMoveFile(endGameMessage endGameMsg);

bool badInputFile(endGameReason reason);

void printBadInputFile(endGameReason reason, playerEnum player);

void endGame(Game& game, endGameMessage endGameMsg, const char* outputFilePath);

endGameMessage playGame(Game& game, const char* filePath_player1, const char* filePath_player2);

#endif //EX1_MAINAUX_H