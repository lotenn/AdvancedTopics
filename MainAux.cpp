#include "MainAux.h"

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

