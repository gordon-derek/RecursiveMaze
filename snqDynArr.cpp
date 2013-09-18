//Implementation FILE : SnQStaticArray.cpp
//Author: Derek Gordon
//Date: 3/19/2012
//Purpose: To implement the methods of both
//	 a stack and a que class into one class.
//	these methods are declared in the header
//	file and gives the list the ability to
//	be used as a StackClass or a QueClass.
//
//Assumptions:
//	The ItemType passed in by the client will
//	be populated with an intended and valid
//	key.
//
//	The Client will write the code in a way that they will try blocks
//	of code and catch the Exception thrown by the class if there is one.
//
//Exception Handling:
//	PopDeQ on Empty
//	Retrieve on Empty
//	Exceptions Thrown to an Exception class to be handled by client

#include "snqDynArr.h"
#include <iostream>
using namespace std;

SnQClass::SnQClass()
{
	//initialize all pdm's to their default values
	snq = new ItemType [INITIAL_SIZE];
	front = 0;
	back = 1;
	size = INITIAL_SIZE;
}//end constructor

/**********************************************************************************************/

SnQClass::~SnQClass()
{
	//delete pointer to the list, returns memory to system
	delete [] snq;
}//end destructor

/**********************************************************************************************/

SnQClass::SnQClass(const SnQClass& orig)	//class object to be copied
{

	//copy size and list placements
	size = orig.size;
	front = orig.front;
	back = orig.back;
	length = orig.length;

	//set size of list to the same as orig
	snq = new ItemType [size];
	
	//cycle through orig copying items over to same 
	//spot in applying list
	for(int i = 0; i < size; i++)
		snq[i] = orig.snq[i];

}//end copy constructor

/**********************************************************************************************/

bool SnQClass::IsEmpty() const
{
	return (back == (front + 1) % size);
}//end IsEmpty

/**********************************************************************************************/

bool SnQClass::IsFull() const
{
	return false;
}//end IsFull

/**********************************************************************************************/

void SnQClass::EnQ(ItemType newItem)	//item to be inserted
{
	//list is full, need to expand
	if( back == front )
		Expand();

	//insert at back
	snq[back] = newItem;

	//set back to next location
	back = (back + 1) % size;

	length++;

}//end EnQ

/**********************************************************************************************/

void SnQClass::Push(ItemType newItem)	//item to be deleted
{
	//list is full, need to expand
	if( IsFull() )
		Expand();
		
	//insert at front
	snq[front] = newItem;

	//decrement front for new top of list
	front = (front + size - 1) % size;
	length++;
	

}//end Push

/**********************************************************************************************/

void SnQClass::PopDeQ()
{


	//cannot delete from an empty list
	if(IsEmpty())
		throw PopOnEmpty("Stack/Queue is Empty, Cannot Pop/DeQ");	

	else
	{
		//if occupancy is less than 25% and larger than initial size
		//contract the list
		if(length == (size * OCCUPANCY) && size != INITIAL_SIZE)
			Contract();
			
		//increment front for new top of list
		front = (front + 1) % size;
		length--;
	}

}//end PopDeQ

/**********************************************************************************************/

ItemType SnQClass::Retrieve() const
{

	//Cannot retrieve from an empty list
	if(IsEmpty())
		throw RetOnEmpty("Stack/Queue is Empty, Cannot Retrive");
	else
		return snq[(front + 1) % size];

}//end Retrieve

/**********************************************************************************************/

void SnQClass::Clear()
{
	//pop items off list until empty
	while(!IsEmpty())
		PopDeQ();

	//reset front and back to default
	front = 0;
	back = 1;
}//end Clear

/**********************************************************************************************/

void SnQClass::Expand()
{
	SnQClass temp;	//stores list
	
	//temp gets all applying classes pdm's
	temp.snq = snq;
	temp.front = front;
	temp.back = back;
	temp.size = size;

	//size is doubled
	size = size * EXPAND_OP;
	//reinitialize pointer with a larger list
	snq = new ItemType[size];
	//set pdm's to default
	front = 0;
	back = 1;
	length = 0;

	//take all the elements in temp and put them in
	//applying class object
	while(!temp.IsEmpty())
	{
		EnQ(temp.Retrieve());
		temp.PopDeQ();
	}//end while

}//end Expand

/**********************************************************************************************/

void SnQClass::Contract()
{
	SnQClass temp;//stores list
	
	//temp gets all applying classes pdm's
	temp.snq = snq;
	temp.front = front;
	temp.back = back;
	temp.size = size;

	//size is halved
	size = size / CONTRACT_OP;
	//reinitialize pointer to smaller list
	snq = new ItemType[size];
	//reset pdm's back to defaults
	front = 0;
	back = 1;
	length = 0;
	
	//take all the elements in temp and put them in
	//applying class object
	while(!temp.IsEmpty())
	{
		EnQ(temp.Retrieve());
		temp.PopDeQ();
	}//end while
}//end Contract

/**********************************************************************************************/

bool SnQClass::operator==(SnQClass rtOp)	//class object to compare
{
	//set positions to top of list
	int currPos = (front + 1) % size;
	int rtOpPos = (rtOp.front + 1) % size;

	//sizes must be same to be equal
	if(size != rtOp.size)
		return false;

	//cycle through lists checking item by item
	while(currPos != back && rtOpPos != rtOp.back)
	{
		if(snq[currPos].direction != rtOp.snq[rtOpPos].direction)
			return false;

		//go to next item down the list
		currPos = (currPos + 1) % size;
		rtOpPos = (rtOpPos + 1) % size;
	}//end while

	return true;
}//end operator==

/**********************************************************************************************/

void SnQClass::operator =(const SnQClass& orig)	//class object to be copied
{


	//copy size and list placements
	size = orig.size;
	front = orig.front;
	back = orig.back;
	length = orig.length;

	//set size of list to the same as orig
	snq = new ItemType [size];
	
	//cycle through orig copying items over to same 
	//spot in applying list
	for(int i = 0; i < size; i++)
		snq[i] = orig.snq[i];

}//end operator=