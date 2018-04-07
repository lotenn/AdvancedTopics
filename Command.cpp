#include "Command.h"

Command createCommand(commandType _type, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type, int _executionsLeft){
    Command cmd;
    cmd.type = _type;
    cmd.source = createCell(srcX, srcY);
    cmd.target = createCell(targetX, targetY);
    cmd.joker = createCell(jokerX, jokerY);
    cmd.new_type = _new_type;
    cmd.executionsLeft = _executionsLeft;
    return cmd;
}


Command createCommand(commandType _type, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type){
    return createCommand( _type,  srcX,  srcY,  targetX,  targetY,  jokerX,  jokerY,  _new_type,  1);

    }

PositioningCommand createPositioningCommand(char _toolType, int srcX, int srcY, positioningCommandType _type){
    PositioningCommand posCmd;
    posCmd.toolType = _toolType;
    posCmd.source = createCell(srcX, srcY);
    posCmd.type = _type;
    return posCmd;
}



