#include <string>
#include <iostream>
#include "Files.h"
using namespace std;

int main() {

	vector<PositioningCommand> commands;
    vector<PositioningCommand> commands2;

    const char* filePath = "C:/Users/loten/CLionProjects/EX1/player1.rps_board";
    endGameMessage msg = validatePositioningFile(filePath, commands);
    validatePositioningFile("C:/Users/loten/CLionProjects/EX1/player2.rps_board", commands2);


    for(int i=0; i<(int)commands.size(); i++){
        cout << "cmd: " << commands.at(i).toolType << ":" << commands.at(i).source.x << "," <<  commands.at(i).source.y <<endl;
    }
    cout << "msg: " << msg.reason << endl;

    Game game;
    game.setPlayerTools(commands, PLAYER_1);
    game.setPlayerTools(commands2, PLAYER_2);

    ofstream of;
    of.open("C:/Users/loten/CLionProjects/EX1/rps.output", ios::out);


    printBoard(of,game);

    of.close();
	return 0;
}