
#ifndef EX1_CELL_H
#define EX1_CELL_H

/*
 * A struct implements x,y coordinates of a game tool
 */
struct Cell{
    int x;
    int y;
};

Cell createCell(int _x, int _y);

int getRow(Cell cell);

int getCol(Cell cell);

#endif //EX1_CELL_H
