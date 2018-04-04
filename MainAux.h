#ifndef EX1_MAINAUX_H
#define EX1_MAINAUX_H

#include <string>
#include <string.h>
#include "Files.h"

using namespace std;

endGameMessage initializeGame(Game game, const char* filePath_player1, const char* filePath_player2);

void printBadPositionMessage(endGameMessage endGameMsg);

#endif //EX1_MAINAUX_H