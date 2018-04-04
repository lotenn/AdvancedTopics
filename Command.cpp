#include "Command.h"

Command createCommand(commandType _type, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type){
    Command cmd;
    cmd.type = _type;
    cmd.source = createCell(srcX, srcY);
    cmd.target = createCell(targetX, targetY);
    cmd.joker = createCell(jokerX, jokerY);
    cmd.new_type = _new_type;
    return cmd;
}

PositioningCommand createPositioningCommand(char _toolType, int srcX, int srcY, positioningCommandType _type){
    PositioningCommand posCmd;
    posCmd.toolType = _toolType;
    posCmd.source = createCell(srcX, srcY);
    posCmd.type = _type;
    return posCmd;
}



