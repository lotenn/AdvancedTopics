#include "Command.h"

// createCommand(commandType _type, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type, int _executionsLeft){
Command createCommand(vector<commandType> _steps, int _currentStep, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type){
    Command cmd;
    cmd.steps = _steps;
    cmd.currentStep = _currentStep;
    cmd.source = createCell(srcX, srcY);
    cmd.target = createCell(targetX, targetY);
    cmd.joker = createCell(jokerX, jokerY);
    cmd.new_type = _new_type;
    return cmd;
}


Command createCommand(vector<commandType> _steps, int srcX, int srcY, int targetX, int targetY, int jokerX, int jokerY, char _new_type){
    return createCommand(_steps, 0,  srcX,  srcY,  targetX,  targetY,  jokerX,  jokerY,  _new_type);
}

PositioningCommand createPositioningCommand(char _toolType, int srcX, int srcY, positioningCommandType _type){
    PositioningCommand posCmd;
    posCmd.toolType = _toolType;
    posCmd.source = createCell(srcX, srcY);
    posCmd.type = _type;
    return posCmd;
}



