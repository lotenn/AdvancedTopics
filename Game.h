#ifndef EX1_GAME_H
#define EX1_GAME_H

#include <vector>
#include "Command.h"
#include <string.h>
#include <string>

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
	PLAYER_1 = 0,
	PLAYER_2 = 1,
	NO_PLAYER = 2
};

const string toString(playerEnum player);
const string getWinnerString(playerEnum player);

enum toolType {
	ROCK ,
	PAPER,
	SCISSORS,
	BOMB,
	FLAG,
	EMPTY,
};

enum executeCommandMessage{
	EXECUTE_COMMAND_SUCCESS = 0,
	EXECUTE_COMMAND_ILLEGAL = 1
};

enum endGameReason{
    NO_WINNER = 0,
    NO_MORE_FLAGS = 1,
    NO_MOVING_TOOLS = 2,
	NO_POSITIONING_FILE = 3,
    BAD_POSITIONING_FILE_SYNTAX = 4,
	BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS = 5,
	BAD_POSITIONING_FILE_TOO_MANY_TOOLS = 6,
	BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION = 7,
	NO_MOVE_FILE = 8,
	BAD_MOVE_FILE_PLAYER = 9,
    DRAW_NO_MORE_MOVES = 10,
    DRAW_POSITIONING_ENDED_WITH_NO_FLAGS = 11,
	DRAW_POSITIONING_ENDED_WITH_NO_MOVING_TOOLS = 12,
    DRAW_POSITIONING_FILE_BOTH_PLAYERS = 13
};

const string getBadInputFileMessage(endGameReason reason);

struct endGameMessage{
    endGameReason reason;
    playerEnum winner;
    int errorLine1;
    int errorLine2;
};

const string getReasonString(endGameMessage);

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
			isPositioned(_isPositioned = false){}

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
        return EXECUTE_COMMAND_ILLEGAL;
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



class Game
{
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
    executeCommandMessage moveTool(Game* game, Cell target);
	executeCommandMessage executeCommand(Command cmd);
    executeCommandMessage executeJoker(Command cmd);
	executeCommandMessage executeMove(Command cmd);
    endGameReason playerHasLost(vector<Tool*> playerTools);
    endGameMessage checkGameWinner();
    void raisePlayerScore(int score, playerEnum player);

	//testing
    void updateCell(Cell cell, Tool *tool){
        this->gameBoard[getRow(cell)][getCol(cell)] = tool;
    }
	string boardToString();

};
toolType charToToolType(char c);

#endif //EX1_GAME_H
