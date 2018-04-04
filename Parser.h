
#ifndef EX1_PARSER_H
#define EX1_PARSER_H

#include <string>
#include <string.h>
#include "Command.h"
#include "MainAux.h"

using namespace std;

class Parser {
public:
	Parser()= default;
	Parser(const Parser&)= delete;
	Parser& operator=(const Parser&)= delete;

    Command parseMoveCommand(string commandLine);
    PositioningCommand parsePositioningCommandLine(string commandLine);
};


#endif //EX1_PARSER_H
