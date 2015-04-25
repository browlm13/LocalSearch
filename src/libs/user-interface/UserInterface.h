#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <string>
#include "query-engine/QueryEngine.h"

class UserInterface {
	QueryEngine *qe;
public:
	UserInterface(QueryEngine qe) : qe(&qe)	{}

	std::string dataBase_toString();		//calls query engine function

	//TMP
	std::string border(char c, int length);
	std::string border(char c, int length, std::string title);
};

#endif	//USERINTERFACE_H

	// ( screens )
	//homeScreen	//options: (q)uit, (c)onfig , (n)ew
		//[# of saved doc] 
	//searchScreen 	//options: (q)uit, (c)onfig, (h)ome, ( (s)ave )
		//[query]
	//infoScreen	//options: (q)uit, (h)ome, (b)ack, (j)scroll down, (k)scroll up
		//[# doc selection]
	//pageScreen	//options: (q)uit, (h)ome, (b)ack, (j)scroll down, (k)scroll up
	//configScreen	//options: (q)uit, (home)
		//[config cmds]