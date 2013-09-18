//Specification File
//Author: Derek Gordon
//Date: November 14, 2011
//Modified: March 28,2012
//			April 22, 2012
//Purpose: To handle an exception that
//	is thrown by another class. The
//	exception will be thrown as a class
//	the class will then be caught by the
//	client that is testing the piece of code
//
//Assumptions:
//	The Exception thrown is a valid class.

#include <string>
using namespace std;

class PopOnEmpty
{
public:
	PopOnEmpty(){}//default constructor, does nothing
	PopOnEmpty(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}

private:
	string message;
};//end PopOnEmpty

class DeQOnEmpty
{
public:
	DeQOnEmpty(){}//default constructor, does nothing
	DeQOnEmpty(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}

private:
	string message;
};//end DeQOnEmpty
	
class RetOnEmpty
{
public:
	RetOnEmpty(){}//default constructor, does nothing
	RetOnEmpty(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}
private:
	string message;
};//end RetOnEmpty
	
class OutOfMem
{
public:
	OutOfMem(){}//default constructor, does nothing
	OutOfMem(string theMessage) : message(theMessage){}
	string GetMessage() const {return message;}
private:
	string message;
};//end OutOfMem
	

	