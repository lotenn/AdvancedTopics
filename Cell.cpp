#include "Cell.h"

Cell createCell(int _x, int _y){
    Cell cell;
    cell.x = _x;
    cell.y = _y;
    return cell;
}
int getRow(Cell cell){
    return cell.y - 1;
}

int getCol(Cell cell){
    return cell.x - 1;
}
