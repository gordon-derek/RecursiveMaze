//Name: boardRec.h
//Author: Derek Gordon
//Date: October 2, 2011
//Purpose: create the properties the gameboard should have

#ifndef BOARDREC_H
#define BOARDREC_H



struct BoardRec
{
	bool active; // is the cell active
	bool occupied; // is the cell occupied
	bool beenN;
	bool beenE;
	bool beenS;
	bool beenW;
};

#endif