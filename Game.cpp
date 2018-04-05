#include "Game.h"

playerEnum getOpposite(playerEnum player){
    switch(player){
        case PLAYER_1:
            return PLAYER_2;
        case PLAYER_2:
            return PLAYER_1;
        default:
            return NO_PLAYER;
    }
}

const string toString(playerEnum player){
    const string toString[] = {"player 1", "player 2", "no player"};
    return toString[player];
}

const string getWinnerString(playerEnum player){
    const string getWinner[] = {"1", "2", "0"};
    return getWinner[player];
}

const string getBadInputFileMessage(endGameReason reason){
    const string getMessage[] = {
        "", //NO_WINNER
        "", //NO_MORE_FLAGS
        "", //NO_MOVING_TOOLS
        "", //NO_POSITIONING_FILE
        "wrong positioning file syntax" , //BAD_POSITIONING_FILE_SYNTAX
        "not enough flags in the positioning file", //BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS
        "too many tools in positioning file", //BAD_POSITIONING_FILE_TOO_MANY_TOOLS
        "2 tools located in the same cell in the positioning file", //BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION
        "", //NO_MOVE_FILE
        "", //BAD_MOVE_FILE_PLAYER
        "", //DRAW_NO_MORE_MOVES
        "", //DRAW_POSITIONING_ENDED_WITH_NO_FLAGS
        "", //DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS
        "" //DRAW_POSITIONING_FILE_BOTH_PLAYERS
    };
    return getMessage[reason];
}

const string getReasonString(endGameMessage endGameMsg){
    const string getReason[] = {
        "", //NO_WINNER
        "All flags of the opponent are captured", //NO_MORE_FLAGS
        "All moving PIECEs of the opponent are eaten", //NO_MOVING_TOOLS
        "", //NO_POSITIONING_FILE
        "Bad Positioning input file for player "+toString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1), //BAD_POSITIONING_FILE_SYNTAX
        "Bad Positioning input file for player "+toString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1), //BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS
        "Bad Positioning input file for player "+toString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1), //BAD_POSITIONING_FILE_TOO_MANY_TOOLS
        "Bad Positioning input file for player "+toString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1), //BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION
        "", //NO_MOVE_FILE
        "Bad Moves input file for player "+toString(getOpposite(endGameMsg.winner))+" - line "+to_string(endGameMsg.errorLine1), //BAD_MOVE_FILE_PLAYER
        "A tie - both Moves input files done without a winner", //DRAW_NO_MORE_MOVES
        "A tie - all flags are eaten by both players in the position files", //DRAW_POSITIONING_ENDED_WITH_NO_FLAGS
        "A tie - moving PIECEs are eaten by both players in the position files", //DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS
        "Bad Positioning input file for both players - player 1: line "+to_string(endGameMsg.errorLine1)+", player 2: line "+to_string(endGameMsg.errorLine2) //DRAW_POSITIONING_FILE_BOTH_PLAYERS
    };
    return getReason[endGameMsg.reason];
}

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner, int _errorLine1, int _errorLine2){
    endGameMessage message;
    message.reason = reason;
    message.winner = winner;
    message.errorLine1 = _errorLine1;
    message.errorLine2 = _errorLine2;

    return message;
}

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner){
    return createEndGameMessage(reason, winner, -1, -1);
}

bool isNumInRange(char* str, int rangeStart, int rangeEnd) {
    if (str == NULL || strlen(str)==0) {
        return false;
    }
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        //not valid digits
        if (!('0' <= str[i] && str[i] <= '9')) return false;
    }
    //str in a number
    int num = atoi(str);

    return (num >= rangeStart && num <= rangeEnd);
}

bool isValidToolType(char tool){
    switch (tool) {
        case 'R':
        case 'P':
        case 'S':
        case 'B':
        case 'F':
        case 'J':
            return true;
        default:
            return false;
    }
}

bool isCharArrValidToolType(char *c) {
    if(c == NULL) return false;
    if(strlen(c)==1){
        char tool = *c;
        return isValidToolType(tool);
    }
    return false;
}

bool isValidJokerToolType(char tool){
    switch (tool) {
        case 'R':
        case 'P':
        case 'S':
        case 'B':
            return true;
        default:
            return false;
    }
}

bool isCharArrValidJokerToolType(char *c) {
    if(c == NULL) return false;
    if(strlen(c)==1){
        char tool = *c;
        return isValidJokerToolType(tool);
    }
    return false;
}


Game::Game():emptyTool(new EmptyTool(NO_PLAYER)), player1Score(0), player2Score(0), currentPlayer(PLAYER_1){
    player1Tools.reserve(NUM_OF_TOOLS);
    player2Tools.reserve(NUM_OF_TOOLS);

    int toolIndex = 0;
    for(int i = toolIndex; toolIndex<(i+NUM_OF_R); toolIndex++){
        player1Tools.push_back(new RockTool(PLAYER_1));
        player2Tools.push_back(new RockTool(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_P); toolIndex++){
        player1Tools.push_back(new PaperTool(PLAYER_1));
        player2Tools.push_back(new PaperTool(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_S); toolIndex++){
        player1Tools.push_back(new ScissorsTool(PLAYER_1));
        player2Tools.push_back(new ScissorsTool(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_B); toolIndex++){
        player1Tools.push_back(new BombTool(PLAYER_1));
        player2Tools.push_back(new BombTool(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_J); toolIndex++){
        player1Tools.push_back(new JokerTool(PLAYER_1));
        player2Tools.push_back(new JokerTool(PLAYER_2));
    }

    for(int i = toolIndex; toolIndex<(i+NUM_OF_F); toolIndex++){
        player1Tools.push_back(new FlagTool(PLAYER_1));
        player2Tools.push_back(new FlagTool(PLAYER_2));
    }
}

Game::~Game() {
    for(int i=0; i<NUM_OF_TOOLS; i++){
        delete player1Tools[i];
        delete player2Tools[i];
    }
    delete emptyTool;
}

void Game::setPlayerTools(const vector<PositioningCommand> &commands, playerEnum player){
//    playerEnum oppositePlayer = getOppositePlayer(this->getCurrentPlayer());
    vector<Tool *> *playerTools;
    switch (player){
        case PLAYER_1:
            playerTools = &(this->player1Tools);
            break;
        case PLAYER_2:
            playerTools = &(this->player2Tools);
            break;
        default:
            break;
    }
    //iterating through all commands in "commands" vector
    for(int i=0; i<(int)commands.size(); i++){
        //extracting data from current command
        toolType _toolType = charToToolType(commands[i].toolType);
        int col = getCol(commands[i].source), row = getRow(commands[i].source);

        //Regular command
        if(commands[i].type == REGULAR_POSITIONING_COMMAND){
            for (Tool *tool:(*playerTools)) {
                //matching tool was found (not positioned, not joker, correct type)
                if (!tool->IsPositioned() && !tool->isJoker() && tool->getType() == _toolType) {
                    this->gameBoard[row][col] = this->battleWinner(tool, this->gameBoard[row][col]);
                    break;
                }
                //a matching tool must be found (commands are valid) thus no "else" statement is needed
            }

        }
        //joker commands
        else{
            //looking for next un-positioned joker
            for (Tool* tool:(*playerTools)) {
                //matching tool was found (not positioned, joker type)
                if (!tool->IsPositioned() && tool->isJoker()) {
                    tool->setJoker(_toolType);
                    tool->placeTool();
                    this->gameBoard[row][col] = this->battleWinner(tool, this->gameBoard[row][col]);
                    break;
                }
                //a matching tool must be found (commands are valid) thus no "else" statement is needed
            }
        }
    }
    //end of commands vector
}

void Game::resetGameBoard(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            gameBoard[i][j] = emptyTool;
        }
    }

    for(Tool *tool: player1Tools)
        tool->removeTool();

    for(Tool *tool: player2Tools)
        tool->removeTool();
}

executeCommandMessage Game::playTurn(Command cmd, playerEnum player){
    this->setCurrentPlayer(player);
    return executeCommand(cmd);
}

void Game::setCurrentPlayer(playerEnum player){
    if(player == NO_PLAYER)
        return;
    this->currentPlayer = player;
}

bool Tool::canCapture(Tool *other) {
    vector<toolType> weakerTools = this->getWeakerTools();
    toolType otherType = other->getType();
    for(toolType weakTool: weakerTools){
        if(weakTool == otherType)
            return true;
    }
    return false;
}

Tool* Game::battleWinner(Tool *source, Tool *target) {
    bool sourceWin = source->canCapture(target), targetWin = target->canCapture(source);
    if(sourceWin && targetWin) {
        source->removeTool();
        target->removeTool();
        return this->emptyTool;
    }
    else if(sourceWin) {
        source->placeTool();
        target->removeTool();
        return source;
    }
    else{
        target->placeTool();
        source->removeTool();
        return target;
    }
}

executeCommandMessage Game::executeMove(Command cmd){
    Cell source = cmd.source, target = cmd.target;
    int sourceRow = getRow(source), sourceCol = getCol(source), targetRow = getRow(target), targetCol = getCol(target);
    Tool *sourceTool = this->gameBoard[sourceRow][sourceCol], *targetTool = this->gameBoard[targetRow][targetCol];
    //legal move
    if(sourceTool->getPlayer() == this->getCurrentPlayer() &&
    		sourceTool->canMove(source, target) && sourceTool->getPlayer() != targetTool->getPlayer()){
        this->gameBoard[sourceRow][sourceCol] = this->emptyTool;
        this->gameBoard[targetRow][targetCol] = this->battleWinner(sourceTool, targetTool);
        return EXECUTE_COMMAND_SUCCESS;
    }
    return EXECUTE_COMMAND_ILLEGAL;
}

executeCommandMessage Game::executeJoker(Command cmd){
    //move command execution
    executeCommandMessage moveMessage = executeMove(cmd);
    if(moveMessage == EXECUTE_COMMAND_ILLEGAL)
        return moveMessage;
    //joker command execution
    Cell jokerCell = cmd.joker;
    int jokerRow = getRow(jokerCell), jokerCol = getCol(jokerCell);
    toolType joker_new_type = charToToolType(cmd.new_type);
    Tool *jokerTool = this->gameBoard[jokerRow][jokerCol];
    return jokerTool->setJoker(joker_new_type);
}

executeCommandMessage Game::executeCommand(Command cmd){
    switch(cmd.type){
        case MOVE_COMMAND:
            return executeMove(cmd);
        case JOKER_COMMAND:
            return executeJoker(cmd);
        default:
            return EXECUTE_COMMAND_ILLEGAL;
    }
}



endGameReason Game::playerHasLost(vector<Tool*> playerTools){
    int flagsCount=0;
    int movingToolsCount=0;
    for(Tool *tool:playerTools) {
        if (tool->IsPositioned()) {
            if (tool->getType() == FLAG) { flagsCount++; }
            else if (tool->canMove()) { movingToolsCount++; }
        }
    }
    if(flagsCount==0){return NO_MORE_FLAGS;}
    else if(movingToolsCount==0){return NO_MOVING_TOOLS;}
    else{return NO_WINNER;}
}

endGameMessage Game::checkGameWinner(){
    endGameReason player1LossReason = playerHasLost(this->player1Tools);
    endGameReason player2LossReason = playerHasLost(this->player2Tools);

    if(player1LossReason!=NO_WINNER && player2LossReason!=NO_WINNER){
        if(player1LossReason == NO_MORE_FLAGS){
            return createEndGameMessage(DRAW_POSITIONING_ENDED_WITH_NO_FLAGS, NO_PLAYER);
        }
        else{
            return createEndGameMessage(DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS, NO_PLAYER);
        }

    }
    else if(player1LossReason!=NO_WINNER) {return createEndGameMessage(player1LossReason, PLAYER_2);}
    else if(player2LossReason!=NO_WINNER) {return createEndGameMessage(player2LossReason, PLAYER_1);}
    else {return createEndGameMessage(NO_WINNER, NO_PLAYER);}
}

void Game::raisePlayerScore(int score, playerEnum player){
    if(player == PLAYER_1) this->player1Score+=score;
    else if(player == PLAYER_2) this->player2Score+=score;
}


toolType charToToolType(char c) {
    switch (c) {
        case 'R':
            return ROCK;
        case 'P':
            return PAPER;
        case 'S':
            return SCISSORS;
        case 'B':
            return BOMB;
        case 'F':
            return FLAG;
        default:
            return EMPTY;
    }
}

string Game::boardToString(){
    string str;
    for (int row = M-1; row >= 0; row--) {
        for (int col = 0; col < N; col++){
            str+= this->gameBoard[row][col]->toChar();
        }
        if(row != 0)
            str+="\n";
    }
    return str;
}

