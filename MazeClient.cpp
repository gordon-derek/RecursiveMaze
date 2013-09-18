//MazeClient.cpp
//Author : Derek Gordon
//Date : April 15, 2012
//Purpose : This client takes the file inserted by the user,
//		given it is a valid file name, takes the information in the
//		file and uses it to create a gameboard size specified by file
//		along with creating the walls withen the gameboard in locations
//		specified by the file.  The client then will cycle through the 
//		gameboard, recursively, listing all posible paths to get from the starting
//		 location(left upper corner) to the ending location(right bottom corner).
//
//Input : The client will prompt the user for a filename of a file that will contain the size
//		of the maze along with any walls that may be placed in the maze.  This file will be tested
//		to comply with the rules stated.  The filename may not contain numbers and is only allowed
//		a three character extension.
//
//Processing : The client will take the file provided by the user and create the maze to the size
//		specified in the file along with placing walls in the specified locations.  The client will
//		then cycle through the maze recursively testing traveling in every direction from a given
//		location.  It will continue testing until every direction in every location has been exhausted
//		whether they lead to a completed path or a dead end.
//
//Output : Every possible path found through the maze is outputted with a list view of the directions
//		along with a graphical view of the direction traveled from each location.  These outputs will
//		be saved to the solution.out file for the user to view after running the program.
//
//Assumptions:
//		The fileName inputted does not contain any numbers and only a 3 character extension
//		Each line in the file is formatted with 1 number a space then another number
//
//Exception Handling:
//		The client will test the filename to make sure it complies with all the rules
//		If the filename is incorrect, it will ask the user to enter a valid name but
//		if the filename is correct but the contents are broken, for instance, placing a 
//		wall outside the size of the maze, the client will tell the user the problem
//		in the file and close.
//
//		If the client uses a method of a class that could return an exception, it will
//		be written to catch the exception and output the message for the user.

#include "gameboard.h"//for the maze
#include "snqDynArr.h"//for the queue that holds the path through maze

#include <iostream>//for input/output to screen
#include <fstream>//for input/output to file

const int CHARTOINT = 48;//converts ints stored in character to an integer instead of ascii #
const string FILENAME = "solution.out";	//file to be printed to

bool CheckForValid(const char * str);  //character ptr to be checked
//checks to see if the file is valid.
//valid meaning no numbers in the filename and only a 3 character extension

int GetRow(/* in */ const char * str);  //number character to be checked for valid
//gets the row from the line read from file
//returns -1 if it was not valid

int GetCol(/* in */ const char * str);	//number character to be checked for valid
//gets the col from the line read from file
//returns -1 if it was not valid

void PrintMaze(GameBoardClass maze);	//maze to be printed
//prints the maze contents O for open, X for wall

void CalculatePath(/* in */ GameBoardClass& maze,
					/* in */ SnQClass& queue);
//cycles through the maze finding all posible paths
//from the start to finish

void rCalcPath(	/* in */ DirectionEnum dir,		//direction to travel out of location
				/* in */ GameBoardClass  maze,	//maze to be cycled through
				/* in */ SnQClass  queue,		//queue that path is stored in
				/* in */ LocationRec loc,		//location currently in maze
				/* in */ LocationRec endP,		//ending location in maze
				/* in */ bool exhaust,			//if there is a direction to travel
				/* out */ int & pathCt);		//keeps number of completed paths
//Recursively cycles through each location in the maze checking all possible directions.
//Once every direction in a location is tested and exhausted, method backtracks to previous
//location.

DirectionEnum GetDir(/* in	*/ DirectionEnum dir,		//direction to be tested
					 /* in/out */ GameBoardClass& maze,	//maze to travel through
					 /* in/out */ LocationRec& loc,		//current location in maze
					 /* out */ bool& exhaust);			//whether the direction tested can be traveled
//tests dir to see if it is actually possible to travel that direction
//returns NONE and sets exhaust true if not possible.

void PrintPath(	/* in */ SnQClass queue,	//path to be printed
				/* in */ GameBoardClass maze,//for size of maze
				/* in */ int & pathCt);		//for numbering paths
//prints all data within the queue and creates a graphical output for the user

bool PathComp(LocationRec loc, LocationRec endP);
//checks to see if the path is at the ending location

void main()
{
	SnQClass path;//path from start to finish
	GameBoardClass maze;//maze to be created
	LocationRec loc;//location within the maze
	ifstream inFile;//used for file input
	ofstream oFile;	//used for file output
	string iFileName;//used for verifying the filename
	bool wallsVal = true;

	oFile.open(FILENAME);	//open file

	cout << "Please input the name of the file you wish to input: ";
	getline(cin, iFileName);

	//checks the inserted filename to make sure it is valid
	//if it is not it will ask for a new filename.
	while(!CheckForValid(iFileName.c_str()))
	{
		system("cls");//clear screen
		cout << "Filename is not Valid, Please try again" << endl << endl;
		cout << "Please input the name of the file you wish to input: ";
		getline(cin, iFileName);
		
	}//end while

	//output filename of infile
	oFile << "Filename used for maze: " << iFileName << endl;

	//the filename is valid, lets open.
	inFile.open(iFileName.c_str());
	if(inFile.good())
	{
		string line;
		getline(inFile, line);
		//first line of file, size of maze

		//get amount of rows in maze
		int row = GetRow(line.c_str());
		//get amount of columns in maze
		int col = GetCol(line.c_str());

		if(row != -1 && col != -1)//row is a valid number
		{
			maze = GameBoardClass(row, col);//set maze to the specified size
			
			while(!inFile.eof() && wallsVal == true)//line is not blank
			{
				getline(inFile, line);//all other lines are locations for walls
				//get the row number wall is placed at
				row = GetRow(line.c_str());
				col = GetCol(line.c_str());

				if(row == -1 || row >= maze.GetMaxRow()
					|| col == -1 || col >= maze.GetMaxCol())//is not a valid number
				{
					cout << "Row not valid cannot input wall at coordinates "
					<< row << "_" << col << endl;
					cout << "Program Terminating" << endl;

					oFile << "Row not valid cannot input wall at coordinates "
					<< row << "_" << col << endl;
					oFile << "Program Terminating" << endl;

					wallsVal = false;
				}

				else//is a valid number
				{
					//place wall at location
					loc.row = row;
					loc.col = col;
					//set location inactive, all inactive locations are walls
					maze.SetInActive(loc);
				}//end else
			}//end while, all walls have been placed
			if(wallsVal)
			{
				PrintMaze(maze);
				CalculatePath(maze, path);
			}
		}//end if
		else
		{
			cout << "Maze size not valid, Program Terminating" << endl;
			oFile << "Maze size not valid, Program Terminating" << endl;
		}
	}
	else
	{
		cout << "File could not be opened, Program Terminating" << endl;
		oFile << "File could not be opened, Program Terminating" << endl;
	}
}//end main

/*******************************-CheckForValid-******************************************/

//Pre: a filename has been inputted
//Post: if the filename only contains letters and a 3 character extension
//		true is returned, false otherwise
//Purpose: to check that the inputted filename obides by our rules for filenames
bool CheckForValid(const char * str)//character ptr to be checked
{
	int ct = 0; //ct after 
	int decCt = 0;

	// is the string empty?
	if (strlen(str) == 0)
		return false;

	while (*str != '\0')
	{
		if(decCt == 0)
		{

			//if there is a decimal, and its first decimal found
			if(*str == '.')
				decCt++;

			//no numbers allowed in filename/extension
			else if (*str > '0' && *str <= '9')
				return false;

		}//end if
		else if(decCt == 1)
		{
			//we are now in the extension of the file

			if(ct >= 3)//no more then 3 characters allowed in extension
				return false; //not a valid extension

			if(*str == '.')//second period in extension not allowed
				return false;

			else if(*str > '0' && *str <= '9')//no numbers allowed in filename/extension
				return false;

			ct++;

		}//end else if
		
		str++; // move to next character
	}//end while
	return true; // all string values were digits

}//End CheckForValid

/*******************************-GetRow-******************************************/

//Pre: a line has been read in from the file and does not = ""
//Post: the row number has been returned if it is a valid number
//		-1 is returned otherwise
//Purpose: to retrieve the row number from the inputted line
int GetRow(/* in */ const char * str)//number character to be checked for valid
{
	int row;

	//character in location 0 is a valid number
	if(*str >= '0' && *str <= '9')
		row = *str - CHARTOINT;

	else//-1 is returned to be handled
		row = -1;

	return row;
}//End GetRow

/*******************************-GetCol-******************************************/

//Pre: a line has been read in from the file and does not = ""
//Post: the column number has been returned if it is a valid number
//		-1 is returned otherwise
//Purpose: to retrieve the column number from the inputted line
int GetCol(/* in */ const char * str)//number character to be checked for valid
{
	int col;
	//move to location where column number should be in the line
	str = str + 2;

	//character in location is a valid number
	if(*str >= '0' && *str <= '9')
		col = *str - CHARTOINT;

	else//number is not valid -1 returned to be handled
		col = -1;

	return col;

}//End GetCol

/*******************************-PrintMaze-******************************************/

//Pre: maze has been created and all walls have been placed
//Post: The maze has been printed so the user can see the wall placement
//Purpose: to allow the user to view the maze
void PrintMaze(GameBoardClass maze)	//built maze to be outputted
{
	ofstream ofile;
	LocationRec loc;//used for testing whether location has wall or not
	ofile.open(FILENAME, ios::app);
	ofile << "O - Open		X - Wall" << endl;
	for(int i = 0; i < maze.GetMaxRow(); i++)
	{//cycle through rows
		for(int j = 0; j < maze.GetMaxCol(); j++)
		{//cycle through cols
			//set loc to test
			loc.row = i;
			loc.col = j;
			if(maze.IsActive(loc))
				ofile << " O ";//no wall
			else//wall
				ofile << " X ";
		}//end for
		ofile << endl << endl;
	}//end for
}//end PrintMaze

/*******************************-CalculatePath-******************************************/

//Pre: A maze has been created and walls have been placed, queue has been created and
//	will store one path at a time.
//Post: All available paths have been outputted after passing through the 
//	recursive method.
//Purpose: To set initial values/parameters for rCalcPath and call the recursive method 
//	which will test all possible paths through the maze.
void CalculatePath(/* in */ GameBoardClass& maze, //maze to be cycled through
					/* in */ SnQClass& queue)	  //queue that path is stored in
{
	LocationRec loc;	//current location in maze
	LocationRec endP;	//destination
	LocationRec prevLoc;//previous location in maze
	DirectionEnum dir;	//direction to try traveling
	ItemType EnQItem;	//item to be EnQed into queue
	int pathCt = 0;//count of paths printed
	bool exhaust = false;//if there is nowhere to go
	
	//set location to start position on gameboard
	loc.row = 0;
	loc.col = 0;

	prevLoc = loc;

	//define initial endpoint
	endP.row = maze.GetMaxRow() - 1;
	endP.col = maze.GetMaxCol() - 1;

	if(maze.IsActive(loc) && maze.IsActive(endP))//if there is not a wall at start & end location
	{
		dir = SOUTH;//always enter the maze going south
		EnQItem.direction = dir;//first movement inputted
		queue.EnQ(EnQItem);	
		maze.SetOccupied(loc);	//at entry location in maze
		//check to see if we can go south
		dir = GetDir(SOUTH, maze, loc, exhaust);
		rCalcPath( dir, maze, queue, loc, endP, exhaust, pathCt);
		
		//reset back to initial location
		loc = prevLoc;
		//check to see if we can go east
		dir = GetDir(EAST, maze, loc, exhaust);
		rCalcPath( dir, maze, queue, loc, endP, exhaust, pathCt);
	}//end if
}//end CalcPath

/**********************************-rCalculatePath-*************************************************/

//Pre: dir has been sent through GetDir and contains a valid dir if possible, none if not
//	maze has been created and all walls placed, also all currently visited locations in path marked
//	queue contains the current path traveled
//	loc contains the current location within the maze
//Post: An Exhaustive search of the maze for every available path from the current location
//	has been performed, any complete paths outputted.
//Purpose: To Gather every path through the maze recursively, from each location the method
//	branches out into 4 different recursive calls for each direction possible, it checks
//	to see if a location can be traveled, if it can it continues, if not it backs up and continues
//	with the next direction.
void rCalcPath(	/* in */ DirectionEnum dir,		//direction to travel out of location
				/* in */ GameBoardClass  maze,	//maze to be cycled through
				/* in */ SnQClass  queue,		//queue that path is stored in
				/* in */ LocationRec loc,		//location currently in maze
				/* in */ LocationRec endP,		//ending location in maze
				/* in */ bool exhaust,			//if there is a direction to travel
				/* out */ int & pathCt)			//keeps track of number of completed paths
{
	ItemType EnQItem;	//inserting items into the queue
	LocationRec prevLoc = loc;	//previous location

	//check to see if the path has reached the exiting location
	if(PathComp(loc, endP))
	{
		//enter the entering direction into queue
		EnQItem.direction = dir;
		queue.EnQ(EnQItem);
		//enter the south exiting movement into queue
		EnQItem.direction = SOUTH;
		queue.EnQ(EnQItem);
		PrintPath(queue, maze, pathCt);
	}//end if

	//path isn't complete and the direction could be traveled
	else if(!exhaust)
	{
		//enter direction into queue
		EnQItem.direction = dir;
		queue.EnQ(EnQItem);

		
		for(int i = (int)SOUTH; i < (int)NONE; i++)
		{
			dir = (DirectionEnum)i;
			//check south to see if it can be traveled
			dir = GetDir(dir, maze, loc, exhaust);
			rCalcPath( dir, maze, queue, loc, endP, exhaust, pathCt);
		
			if(dir != NONE)//direction was traveled
			{
				//set location traveled unoccupied
				//to allow future travel from a different location
				maze.SetUnoccupied(loc);
				//reset all directions traveled to false
				//so that it is usable next time we enter
				maze.ResetDir(loc);
			}//end if
			exhaust = false;
			loc = prevLoc;
			
		}
		//set location traveled unoccupied
		//to allow future travel from a different location
		maze.SetUnoccupied(loc);
		//reset all directions traveled to false
		//so that it is usable next time we enter
		maze.ResetDir(loc);
	}//end if
}//end Calculate Path

/*******************************-GetDir-******************************************/

//Pre: dir contains the direction we want to try to travel
//		the maze has been created,
//		loc contains the current location in the maze
//		exhaust is false
//Post: The direction we tested for travel is returned if possible, NONE
//	is returned and exhaust is set true if not possible.
//Purpose: To test to see if the next direction can be traveled.
DirectionEnum GetDir(/* in	*/ DirectionEnum dir,		//direction to be tested
					 /* in/out */ GameBoardClass& maze,	//maze to travel through
					 /* in/out */ LocationRec& loc,		//current location in maze
					 /* out */ bool& exhaust)			//whether the direction tested can be traveled
{
	//for setting directions traveled
	LocationRec prevLoc = loc;

	//dir contains a valid direction, test to see if its possible to travel
	switch((int)dir)
	{
	case 0: //check to see if there is space to travel in that direction
			//or if we have already traveled that way.
			if(loc.row < maze.GetMaxRow()-1 && !maze.beenS(loc))
			{
				//check block
				loc.row++;

				//check to make sure we havn't already been here or there isn't a wall
				if(maze.IsActive(loc) && !maze.IsOccupied(loc))
				{
					//no wall haven't been here, travel
					maze.SetBeenDir(0,prevLoc);
					maze.SetOccupied(loc);
					return dir;	//return direction tested
				}//end if
				
				//we have been there before or there is a wall
				else	
				{
					//go back to original location
					loc = prevLoc;
					exhaust = true;	//cannot move
					return NONE;	//no direction to travel
				}//end else
			}//end if
			
			//no room to move or we have traveled this direction before
			else
			{
				exhaust = true;	//nowhere to go
				return NONE;
			}//end else
			break;

	case 1: //check to see if there is space to travel in that direction
			//or if we have already traveled that way.
			if(loc.col < maze.GetMaxCol()-1 && !maze.beenE(loc))
			{
				//check block
				loc.col++;

				//check to make sure we havn't already been here or there isn't a wall
				if(maze.IsActive(loc) && !maze.IsOccupied(loc))
				{
					//no wall haven't been here, travel
					maze.SetBeenDir(0,prevLoc);
					maze.SetOccupied(loc);
					return dir;	//return direction tested
				}//end if
				
				//we have been there before or there is a wall
				else	
				{
					//go back to original location
					loc = prevLoc;
					exhaust = true;	//cannot move
					return NONE;	//no direction to travel
				}//end else
			}//end if
			
			//no room to move or we have traveled this direction before
			else
			{
				exhaust = true;	//nowhere to go
				return NONE;
			}//end else
			break;

	case 2: //check to see if there is space to travel in that direction
			//or if we have already traveled that way.
			if(loc.row > 0 && !maze.beenN(loc))
			{
				//check block
				loc.row--;

				//check to make sure we havn't already been here or there isn't a wall
				if(maze.IsActive(loc) && !maze.IsOccupied(loc))
				{
					//no wall haven't been here, travel
					maze.SetBeenDir(0,prevLoc);
					maze.SetOccupied(loc);
					return dir;	//return direction tested
				}//end if
				
				//we have been there before or there is a wall
				else	
				{
					//go back to original location
					loc = prevLoc;
					exhaust = true;	//cannot move
					return NONE;	//no direction to travel
				}//end else
			}//end if
			
			//no room to move or we have traveled this direction before
			else
			{
				exhaust = true;	//nowhere to go
				return NONE;
			}//end else
			break;

	case 3: //check to see if there is space to travel in that direction
			//or if we have already traveled that way.
			if(loc.col > 0 && !maze.beenW(loc))
			{
				//check block
				loc.col--;

				//check to make sure we havn't already been here or there isn't a wall
				if(maze.IsActive(loc) && !maze.IsOccupied(loc))
				{
					//no wall haven't been here, travel
					maze.SetBeenDir(0,prevLoc);
					maze.SetOccupied(loc);
					return dir;	//return direction tested
				}//end if
				
				//we have been there before or there is a wall
				else	
				{
					//go back to original location
					loc = prevLoc;
					exhaust = true;	//cannot move
					return NONE;	//no direction to travel
				}//end else
			}//end if
			
			//no room to move or we have traveled this direction before
			else
			{
				exhaust = true;	//nowhere to go
				return NONE;
			}//end else
			break;
	}

	return NONE;

}//End GetDir
		

/*******************************-Print Path-******************************************/

//Pre: Path through maze is complete, queue contains the complete path
//Post: The path contained in queue is printed to the screen,
//	along with a graphical view of the path through the maze.
//Purpose: Output the contents of the queue to the screen and
//	create a graphical view of the path for the user.
void PrintPath(	/* in */ SnQClass queue,	//path to be printed
				/* in */ GameBoardClass maze,//for size of maze
				/* in */ int & pathCt)		//for numbering paths
{
	GameBoardClass path = GameBoardClass(maze.GetMaxRow(), maze.GetMaxCol());
	int dir;	//for matching direction
	LocationRec loc;	//location in maze
	string output = "";//total output
	string gout = ""; //graphical maze output
	ofstream oFile;	//output file
	oFile.open(FILENAME, ios::app);
	pathCt++;//pre increment, no Path 0
	oFile << "Path " << pathCt << endl;

	//graphical output of top wall with south entrance movement
	for(int i = 0; i < maze.GetMaxCol(); i++)
	{
		if(i == 0)
			gout = "| S ";
		else
			gout = gout + " - ";
	}//end for
	gout = gout + "|\n";

	loc.row = 0;
	loc.col = 0;

	//output initial southword movement into maze
	output = output + "South \n";

	try
	{queue.PopDeQ();}//removes outputted direction from queue
	catch(PopOnEmpty exception)
	{cout << exception.GetMessage();};

	while(!queue.IsEmpty())
	{
	//cycles through the queue saving direction to output
	//in order to show path correctly.
		dir = queue.Retrieve().direction;

		
		if(dir == 0)
		{	//set BeenDir for path,
			//gives a way of reading which direction for graphical print
			path.SetBeenDir(dir, loc);
			output = output + "South \n";
			//exiting movement don't want to write outside bounds of array
			if(loc.row != maze.GetMaxRow() - 1 || loc.col != maze.GetMaxCol() - 1)
				loc.row++;	//show movement in location
		}//end if
		else if(dir == 1)
		{
			//set BeenDir for path,
			//gives a way of reading which direction for graphical print
			path.SetBeenDir(dir, loc);
			output = output + "East \n";
			loc.col++;	//show movement in location
		}//end else if
		else if(dir == 2)
		{
			//set BeenDir for path,
			//gives a way of reading which direction for graphical print
			path.SetBeenDir(dir, loc);
			output = output + "North \n";
			loc.row--;	//show movement in location
		}//end else if
		else if(dir == 3)
		{
			//set BeenDir for path,
			//gives a way of reading which direction for graphical print
			path.SetBeenDir(dir, loc);
			output = output + "West \n";
			loc.col--;	//show movement in location
		}//end else if
		try
		{queue.PopDeQ();}//removes outputted direction from queue
		catch(PopOnEmpty exception)
		{cout << exception.GetMessage();};
	}//end while

	//cycle through path, outputting the direction traveled
	//from each location if there is one.
	for(int i = 0; i < path.GetMaxRow(); i++)
	{
		//start of row border
		gout = gout + "|";
		
		for(int j = 0; j < path.GetMaxCol(); j++)
		{
			//update location
			loc.row = i;
			loc.col = j;

			//check to see if we have traveled through this location
			//if so output the direction traveled
			if(path.beenS(loc))
				gout = gout + " S ";

			else if(path.beenN(loc))
				gout = gout + " N ";

			else if(path.beenE(loc))
				gout = gout + " E ";

			else if(path.beenW(loc))
				gout = gout + " W ";

			//no directions were traveled
			else
			{
				//Check to make sure there wasn't a wall there
				if(maze.IsActive(loc))
					gout = gout + "   ";//output spaces for no wall and no direction
				else
					gout = gout + " X ";//output X to signify a wall
			}//end else
		}//end for
		//ending row border and go to next line
		gout = gout + "|\n";
	}//end for

	for(int i = 0; i < maze.GetMaxCol(); i++)
	{
		if(i == 0)
			gout = gout + "| - ";
		else if(i < maze.GetMaxCol() - 1)
			gout = gout + " - ";
		else
			gout = gout + " S ";
	}//end for
	gout = gout + "|\n";

	oFile << output << endl;//prints output to screen
	oFile << gout << endl;
}//End PrintPath

/*******************************-PathComp-******************************************/

//Pre: loc contains a valid location on the gameboard
//		endP contains the exiting location on the gameboard
//Post: true is returned if loc is at the exiting location
//		false otherwise
//Purpose: to determine if loc is infact at the end of the maze.
bool PathComp(LocationRec loc, LocationRec endP)
{
	return (loc.row == endP.row && loc.col == endP.col);
}//End PathComp