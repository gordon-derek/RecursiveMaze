//Name: gameboard.cpp
//Author: Derek Gordon
//Date: October 2, 2011
//Purpose: impliments the methods specified in gameboard.h

#include "gameboard.h"

GameBoardClass::GameBoardClass()
{

	gb = new BoardRecArr*[MAX_ROW];
	row = MAX_ROW;
	col = MAX_COL;
	for(int i = 0; i < MAX_ROW; i++)//for each row add columns
		gb[i] = new BoardRecArr[MAX_COL];
	
	//process entire gameboard
	for(int i = 0; i < MAX_ROW; i++)
	{
		for(int j = 0; j < MAX_COL; j++)
		{
			gb[i][j].active = true;
			gb[i][j].occupied = false;
			gb[i][j].beenE = false;
			gb[i][j].beenW = false;
			gb[i][j].beenS = false;
			gb[i][j].beenN = false;
		}//end for
	}//end for

	
}//End Constructor

/*******************************************************************************/

GameBoardClass::GameBoardClass( /* in */ int newRow,	//user defined row
								/* in */ int newCol )  //user defined col
{
	row = newRow;
	col = newCol;
	gb = new BoardRecArr*[row];
	for(int i = 0; i < row; i++)
		gb[i] = new BoardRecArr[col];

	//process entire gameboard
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < col; j++)
		{
			gb[i][j].active = true;
			gb[i][j].occupied = false;
			gb[i][j].beenE = false;
			gb[i][j].beenW = false;
			gb[i][j].beenS = false;
			gb[i][j].beenN = false;
		}//end for
	}//end for
}//End Non-Default Constructor

/*******************************************************************************/

void GameBoardClass::SetOccupied(/* in */ LocationRec loc) //location to set
{
	gb[loc.row][loc.col].occupied = true;
}//End SetOccupied

/*******************************************************************************/

void GameBoardClass::SetUnoccupied(/* in */ LocationRec loc) //location to set	
{
	gb[loc.row][loc.col].occupied = false;
}//End SetUnOccupied

/*******************************************************************************/

bool GameBoardClass::IsOccupied(/* in */ LocationRec loc) //location to set
{
	return gb[loc.row][loc.col].occupied;
}//End IsOccupied

/*******************************************************************************/

bool GameBoardClass::IsActive(/* in */ LocationRec loc) //location to set
{
	return gb[loc.row][loc.col].active;
}//End IsActive

/*******************************************************************************/

void GameBoardClass::SetActive(/* in */ LocationRec loc) //location to set
{
	gb[loc.row][loc.col].active = true;
}//End SetActive

/*******************************************************************************/

void GameBoardClass::SetInActive(/* in */ LocationRec loc)//location to set
{
	gb[loc.row][loc.col].active = false;
}//End SetInActive

/*******************************************************************************/

int GameBoardClass::GetMaxRow()
{
	return row;
}//End GetMaxRow

/*******************************************************************************/

int GameBoardClass::GetMaxCol()
{
	return col;
}//End GetMaxCol

/*******************************************************************************/

void GameBoardClass::SetBeenDir(/* in */ int dir, 
								/* in */ LocationRec loc)
{
	switch(dir)
	{
	case 0:gb[loc.row][loc.col].beenS = true; break;
	case 1:gb[loc.row][loc.col].beenE = true; break;
	case 2:gb[loc.row][loc.col].beenN = true; break;
	case 3:gb[loc.row][loc.col].beenW = true; break;
	}//end switch
	
}//End SetBeenDir

/*******************************************************************************/

void GameBoardClass::ResetDir(/* in */ LocationRec loc)
{
	gb[loc.row][loc.col].beenS = false;
	gb[loc.row][loc.col].beenE = false;
	gb[loc.row][loc.col].beenN = false;
	gb[loc.row][loc.col].beenW = false;
}//End ResetDir

/*******************************************************************************/

bool GameBoardClass::beenN(/* in */ LocationRec loc)
{
	return gb[loc.row][loc.col].beenN;
}//End beenN

/*******************************************************************************/

bool GameBoardClass::beenE(/* in */ LocationRec loc)
{
	return gb[loc.row][loc.col].beenE;
}//End beenE

/*******************************************************************************/

bool GameBoardClass::beenS(/* in */ LocationRec loc)
{
	return gb[loc.row][loc.col].beenS;
}//End beenS

/*******************************************************************************/

bool GameBoardClass::beenW(/* in */ LocationRec loc)
{
	return gb[loc.row][loc.col].beenW;
}//End beenW