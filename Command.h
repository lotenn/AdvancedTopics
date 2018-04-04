
#ifndef EX1_COMMAND_H
#define EX1_COMMAND_H

#include <iostream>
#include "Cell.h"

enum positioningCommandType{
	INVALID_POSITIONING_COMMAND,
	REGULAR_POSITIONING_COMMAND,
	JOKER_POSITIONING_COMMAND
};

enum commandType{
    MOVE_COMMAND = 0,
    JOKER_COMMAND = 1,
	INVALID_MOVE_COMMAND = 2
};

struct Command{
    commandType type;
    Cell source;
    Cell target;
    Cell joker;
    char new_type;
};

Command createCommand(commandType _type, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type);

struct PositioningCommand {
	Cell source;
	char toolType;
	positioningCommandType type;
};

PositioningCommand createPositioningCommand(char toolType, int srcY, int targetX, positioningCommandType type);


#endif //EX1_COMMAND_H