#ifndef EX1_GAME_H
#define EX1_GAME_H

#include "Command.h"
#include <string.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define M 10
#define N 10
#define NUM_OF_R 2
#define NUM_OF_P 5
#define NUM_OF_S 1
#define NUM_OF_B 2
#define NUM_OF_J 2
#define NUM_OF_F 1
#define NUM_OF_TOOLS (NUM_OF_B + NUM_OF_F + NUM_OF_J + NUM_OF_P + NUM_OF_R + NUM_OF_S)

enum playerEnum {
	PLAYER_1,
	PLAYER_2,
	NO_PLAYER
};

string toString(playerEnum player);

string getWinnerString(playerEnum player);

playerEnum getOpposite(playerEnum player);

enum toolType {
	ROCK ,
	PAPER,
	SCISSORS,
	BOMB,
	FLAG,
	EMPTY,
};

toolType charToToolType(char c);

enum executeCommandMessage{
	EXECUTE_COMMAND_SUCCESS,
    EXECUTE_COMMAND_NOT_YOUR_TOOL,
    EXECUTE_COMMAND_TOOL_CANT_MOVE,
    EXECUTE_COMMAND_CELL_OCCUPIED,
    EXECUTE_COMMAND_NOT_JOKER,
	EXECUTE_COMMAND_INVALID
};

enum endGameReason{
    NO_WINNER,
    NO_MORE_FLAGS,
    NO_MOVING_TOOLS,
	NO_POSITIONING_FILE,
    BAD_POSITIONING_FILE_INVALID,
	BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS,
	BAD_POSITIONING_FILE_TOO_MANY_TOOLS,
	BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION,
	NO_MOVE_FILE,
	BAD_MOVE_FILE_NOT_YOUR_TOOL,
	BAD_MOVE_FILE_TOOL_CANT_MOVE,
	BAD_MOVE_FILE_CELL_OCCUPIED,
	BAD_MOVE_FILE_NOT_JOKER,
	BAD_MOVE_FILE_INVALID,
    DRAW_NO_MORE_MOVES,
    DRAW_POSITIONING_ENDED_WITH_NO_FLAGS,
	DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS,
    DRAW_POSITIONING_FILE_BOTH_PLAYERS
};

endGameReason toReason(executeCommandMessage msg);

string getBadInputFileMessage(endGameReason reason);

struct endGameMessage{
    endGameReason mainReason;
    endGameReason reason1;
    endGameReason reason2;
    playerEnum winner;
    int errorLine1;
    int errorLine2;
};

string getReasonString(endGameMessage);

endGameMessage createEndGameMessage(endGameReason mainReason,
									endGameReason reason1,
									endGameReason reason2,
									playerEnum winner,
									int _errorLine1,
									int _errorLine2);

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner, int _errorLine1, int _errorLine2);

endGameMessage createEndGameMessage(endGameReason reason, playerEnum winner);

bool isNumInRange(char* str, int rangeSatrt, int rangeEnd);

bool isValidToolType(char tool);

bool isCharArrValidToolType(char *c);

bool isValidJokerToolType(char tool);

bool isCharArrValidJokerToolType(char *c);

class Tool{
private:
	toolType type;
	playerEnum player;
	bool joker;
	bool isPositioned;

public:
	Tool(toolType _type, playerEnum _player, bool _joker, bool _isPositioned):
			type(_type),
			player(_player),
			joker(_joker),
			isPositioned(_isPositioned){}

	Tool(toolType _type, playerEnum _player, bool _joker):
			type(_type),
			player(_player),
			joker(_joker),
			isPositioned(false){}

	virtual ~Tool() = default;
	toolType getType() const {return this->type;}
	playerEnum getPlayer() const {return this->player;}
	virtual bool canMove() const = 0;
	virtual bool canMove(Cell source, Cell target) const = 0;
	bool isJoker() const {return this->joker;}
	virtual vector<toolType> getWeakerTools() const = 0;
	bool canCapture(Tool *other);
    executeCommandMessage setJoker(toolType joker_new_rep){
        if(this->isJoker()){
            this->type = joker_new_rep;
			return EXECUTE_COMMAND_SUCCESS;
        }
        return EXECUTE_COMMAND_NOT_JOKER;
    }
    void placeTool(){this->isPositioned = true;}
    virtual void removeTool(){this->isPositioned = false;}
    bool IsPositioned() const {return this->isPositioned;}
    virtual char toChar() const = 0;
};

class ScissorsTool : public Tool{
public:
	ScissorsTool(playerEnum _player): Tool(SCISSORS, _player, false) {}
	bool canMove() const override {return true;}
	bool canMove(Cell source, Cell target) const override {
		int sourceRow = getRow(source), sourceCol = getCol(source),
				targetRow = getRow(target), targetCol = getCol(target);
		int vertical = abs(sourceRow - targetRow), horizonal = abs(sourceCol - targetCol);
		return (vertical && !horizonal) || (horizonal && !vertical);
	}
    vector<toolType> getWeakerTools() const override{
        vector<toolType> weakerTools = {SCISSORS, PAPER, BOMB, FLAG, EMPTY};
        return weakerTools;
	}
    char toChar() const override{
		if(this->getPlayer() == PLAYER_1) {return 'S';}
		else{return 's';}
	}
};

class RockTool : public Tool{
public:
	RockTool(playerEnum _player): Tool(ROCK, _player, false) {}
	bool canMove() const override {return true;}
	bool canMove(Cell source, Cell target) const override {
		int sourceRow = getRow(source), sourceCol = getCol(source),
				targetRow = getRow(target), targetCol = getCol(target);
		int vertical = abs(sourceRow - targetRow), horizonal = abs(sourceCol - targetCol);
		return (vertical && !horizonal) || (horizonal && !vertical);
	}
    vector<toolType> getWeakerTools() const override{
        vector<toolType> weakerTools = {ROCK, SCISSORS, BOMB, FLAG, EMPTY};
        return weakerTools;
    }
	char toChar() const override{
		if(this->getPlayer() == PLAYER_1) {return 'R';}
		else{return 'r';}
	}
};

class PaperTool : public Tool{
public:
	PaperTool(playerEnum _player): Tool(PAPER, _player, false) {}
	bool canMove() const override {return true;}
	bool canMove(Cell source, Cell target) const override {
		int sourceRow = getRow(source), sourceCol = getCol(source),
				targetRow = getRow(target), targetCol = getCol(target);
		int vertical = abs(sourceRow - targetRow), horizonal = abs(sourceCol - targetCol);
		return (vertical && !horizonal) || (horizonal && !vertical);
	}
    vector<toolType> getWeakerTools() const override{
        vector<toolType> weakerTools = {PAPER, ROCK, BOMB, FLAG, EMPTY};
        return weakerTools;
    }
	char toChar() const override{
		if(this->getPlayer() == PLAYER_1) {return 'P';}
		else{return 'p';}
	}
};

class BombTool : public Tool{
public:
	BombTool(playerEnum _player): Tool(BOMB, _player, false) {}
	bool canMove() const override {return false;}
	bool canMove(Cell source, Cell target) const override {
		if(source.x ==0 && target.x ==0) return this->canMove();
		return this->canMove();
	}
    vector<toolType> getWeakerTools() const override{
        vector<toolType> weakerTools = {PAPER, ROCK, SCISSORS, BOMB, FLAG, EMPTY};
        return weakerTools;
    }
	char toChar() const override{
		if(this->getPlayer() == PLAYER_1) {return 'B';}
		else{return 'b';}
	}
};

class FlagTool : public Tool{
public:
	FlagTool(playerEnum _player): Tool(FLAG, _player, false) {}
	bool canMove() const override {return false;}
	bool canMove(Cell source, Cell target) const override {
		if(source.x ==0 && target.x ==0) return this->canMove();
		return this->canMove();
	}
    vector<toolType> getWeakerTools() const override{
        vector<toolType> weakerTools = {FLAG, EMPTY};
        return weakerTools;
    }
	char toChar() const override{
		if(this->getPlayer() == PLAYER_1) {return 'F';}
		else{return 'f';}
	}
};

class EmptyTool : public Tool{
public:
    EmptyTool(playerEnum _player): Tool(EMPTY, _player, false, false) {}
    bool canMove() const override {return false;}
	bool canMove(Cell source, Cell target) const override {
		if(source.x ==0 && target.x ==0) return this->canMove();
		return this->canMove();
	}
    vector<toolType> getWeakerTools() const override {
        vector<toolType> weakerTools = {EMPTY};
        return weakerTools;
    }
	void removeTool() override {}
    char toChar() const override{return ' ';}
};

class JokerTool : public Tool{
public:
	JokerTool(playerEnum _player): Tool(EMPTY, _player, true) {}
	bool canMove() const override {
		switch(this->getType()){
			case(SCISSORS):
				return (ScissorsTool(NO_PLAYER).canMove());
			case(ROCK):
				return (RockTool(NO_PLAYER).canMove());
			case(PAPER):
				return (PaperTool(NO_PLAYER).canMove());
			case(BOMB):
				return (BombTool(NO_PLAYER).canMove());
			default:
				return (EmptyTool(NO_PLAYER).canMove());
		}
	}
	bool canMove(Cell source, Cell target) const override {
		switch(this->getType()){
			case(SCISSORS):
				return (ScissorsTool(NO_PLAYER).canMove(source, target));
			case(ROCK):
				return (RockTool(NO_PLAYER).canMove(source, target));
			case(PAPER):
				return (PaperTool(NO_PLAYER).canMove(source, target));
			case(BOMB):
				return (BombTool(NO_PLAYER).canMove(source, target));
			default:
				return (EmptyTool(NO_PLAYER).canMove(source, target));
		}
	}
    vector<toolType> getWeakerTools() const override{
        switch(this->getType()){
            case(SCISSORS):
                return (ScissorsTool(NO_PLAYER).getWeakerTools());
            case(ROCK):
                return (RockTool(NO_PLAYER).getWeakerTools());
            case(PAPER):
                return (PaperTool(NO_PLAYER).getWeakerTools());
            case(BOMB):
                return (BombTool(NO_PLAYER).getWeakerTools());
            default:
                return (EmptyTool(NO_PLAYER).getWeakerTools());
        }
    }
	char toChar() const override{
		if(this->getPlayer() == PLAYER_1) {return 'J';}
		else{return 'j';}
	}
};

class Game {
private:
	Tool* gameBoard[N][M];
	Tool* emptyTool;
	vector<Tool*> player1Tools;
	vector<Tool*> player2Tools;
	int player1Score;
	int player2Score;
	playerEnum currentPlayer;

public:
	Game();
	~Game();
	void setPlayerTools(const vector<PositioningCommand> &commands, playerEnum player);
    void resetGameBoard();
	executeCommandMessage playTurn(Command cmd, playerEnum player);
	playerEnum getCurrentPlayer(){return currentPlayer;}
	void setCurrentPlayer(playerEnum player);
    Tool* battleWinner(Tool *source, Tool *target);
	executeCommandMessage executeCommand(Command cmd);
    executeCommandMessage executeJoker(Command cmd);
	executeCommandMessage executeMove(Command cmd);
    endGameReason playerHasLost(vector<Tool*> playerTools);
    endGameMessage checkGameWinner();
    void raisePlayerScore(int score, playerEnum player);
	string boardToString();
};

#endif //EX1_GAME_H
