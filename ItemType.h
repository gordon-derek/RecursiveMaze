#ifndef item_h
#define item_h



#include <string>
using namespace std;


enum DirectionEnum{SOUTH,EAST,NORTH,WEST,NONE};

struct ItemType		
{					
	DirectionEnum direction;//direction path traveled
};//end struct


#endif
