//Name: gameBoard.h
//Author: Derek Gordon
//Date: October 2, 2011
//Purpose: Specify the methods needed for the gameboard to function
/*
		GameBoardClass();
The constructor is used to initialize all the base properties of the gameboard
	when it's created.

		GameBoardClass( int row, int col );
Non-Default Constructor is used to initialize all the base properties of the gameboard
	when it's created.  Creates a different sized gameboard then default.
	gameboard is made with int row amount of rows and int col amount of cols.

		int GetMaxRow();
Returns the total amount of rows in the gameboard for tests.

		int GetMaxCol();
Returns the total amount of cols in the gameboard for tests.

		void SetOccupied(LocationRec loc); //location to set
SetOccupied will be used when a warrior has been placed on that location of the gameboard.

		void SetUnoccupied(LocationRec loc); //location to set	
If there is no warriors on that location on the gameboard the propertie occupied will be set to false.

		bool IsOccupied(LocationRec loc); //location to set
Checks to see if that location on the gameboard is occupied.

		bool IsActive(LocationRec loc); //location to set
Checks to see if that location on the gameboard is active.

		void SetActive(LocationRec loc); //location to set
Sets that location on the gameboard as active for warriors to be placed.

		void SetInActive( LocationRec loc); //location to set
Sets that location on the gameboard as inactive so no warriors can be placed there.

		void SetBeenDir( int dir,			//direction being traveled
						 LocationRec loc);	//location of cell traveling from
Sets the direction corrosponding with int dir to true to say that that direction has
already been traveled when exiting the cell.

		void ResetDir( LocationRec loc);   //location to set
Resets all of the directions for the cell located at loc to false.

			bool beenN(LocationRec loc);//location to set
			bool beenE(LocationRec loc);//location to set
			bool beenS(LocationRec loc);//location to set
			bool beenW(LocationRec loc);//location to set
Checks to see if that direction has already been traveled before, returns true
	if the direction has, false otherwise.
*/


#include "boardRec.h"
#include "locationRec.h"

const int MAX_ROW = 3;//used in definition of array
const int MAX_COL = 3;//used in definition of array

typedef BoardRec BoardRecArr;
class GameBoardClass
{

	public://add methods

		//default constructor
		//Pre:class has been instantiated
		//Post: class object has been initialized, 
		//		active set to true
		//		Occupied is set to false
		//Purpose: Initialize a gameboard object
		GameBoardClass();

		GameBoardClass( /* in */ int row,
						/* in */ int col );

		//Pre: a gameboard has been instantiated
		//Post: the amount of rows in the gameboard is returned
		//Purpose: to get the amount of rows in the gameboard returned to client
		int GetMaxRow();

		//Pre: a gameboard has been instantiated
		//Post: the amount of rows in the gameboard is returned
		//Purpose: to get the amount of rows in the gameboard returned to client
		int GetMaxCol();

/*-------------------------------- Occupied Methods ----------------------------------------------------*/

		//// Pre: loc contains a valid location within the gameboard
		//// Post: location specified by loc has been set to occupied
		//// Purpose: To mark a location within the gameboard as occupied
		void SetOccupied(/* in */ LocationRec loc); //location to set


		//// Pre: loc contains a valid location within the gameboard
		//// Post: location specified by loc has been set to unoccupied
		//// Purpose: To mark a location within the gameboard as unoccupied
		void SetUnoccupied(/* in */ LocationRec loc); //location to set	


		// Pre: loc contains a valid location within the gameboard
		// Post: true is returned if location specified by loc has occupants, false otherwise
		// Purpose: To check a location within the gameboard to verify occupants
		bool IsOccupied(/* in */ LocationRec loc); //location to set


/*------------------------------------Active Methods --------------------------*/

		//Pre: loc contains a valid location within the gameboard
		//Post: true is returned if the location specified is active
		//Purpose: check the location in the gameboard to verify activity 
		bool IsActive(/* in */ LocationRec loc); //location to set

		//Pre: loc contains a valid location within the gameboard
		//Post: the loc on the gameboard is set active
		//Purpose: to allow occupants in this loc on the gameboard
		void SetActive(/* in */ LocationRec loc); //location to set

		//Pre: loc contains a valid location within the gameboard
		//Post: the loc on the gameboard is set inactive
		//Purpose: to not allow occupants in this loc on the gameboard
		void SetInActive(/* in */ LocationRec loc); //location to set

/*------------------------------------ Direction Methods --------------------------*/

		//Pre: loc contains a valid location within the gameboard,
		//		dir contains a valid number that corrosponds with DirectionEnum
		//Post: the dir is set as been traveled at location loc on the gameboard
		//Purpose: to set the traveled location so that there aren't repeats
		void SetBeenDir(/* in */ int dir,			//direction being traveled
						/* in */ LocationRec loc);	//location of cell traveling from

		//Pre: loc contains a valid location within the gameboard
		//Post: all traveled directions at location loc on gameboard are
		//		set to false(not traveled)
		//Purpose: to reset all the traveled directions
		void ResetDir(/* in */ LocationRec loc);//location to set

		//Pre: loc contains a valid location within the gameboard
		//Post: bool value is returned to whether or not the direction has been traveled
		//Purpose: to check if the direction has been traveled or not.
		bool beenN(/* in */ LocationRec loc);//location to set
		bool beenE(/* in */ LocationRec loc);//location to set
		bool beenS(/* in */ LocationRec loc);//location to set
		bool beenW(/* in */ LocationRec loc);//location to set








	private:
		 BoardRecArr ** gb;//two-dimensional array pointer
		 int row;//row size of array
		 int col;//col size of array




};
