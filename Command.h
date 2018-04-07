
#ifndef EX1_COMMAND_H
#define EX1_COMMAND_H

#include <iostream>
#include <vector>
#include "Cell.h"

using namespace std;

enum positioningCommandType{
	INVALID_POSITIONING_COMMAND,
	REGULAR_POSITIONING_COMMAND,
	JOKER_POSITIONING_COMMAND
};

enum commandType{
    MOVE_COMMAND,
    JOKER_COMMAND,
	INVALID_MOVE_COMMAND
};

struct Command{
	vector<commandType> steps;
	int currentStep;
    Cell source;
    Cell target;
    Cell joker;
    char new_type;
};

Command createCommand(vector<commandType> _steps, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type);

Command createCommand(vector<commandType> _steps, int _currentStep, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type);



struct PositioningCommand {
	Cell source;
	char toolType;
	positioningCommandType type;
};

PositioningCommand createPositioningCommand(char toolType, int srcY, int targetX, positioningCommandType type);


#endif //EX1_COMMAND_H
