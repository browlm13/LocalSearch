#include "ParserHandler.h"

//TMP
#include <iostream>

void ParserHandler::parse_dataBase(database_packet &database){								//return error
	DataBase_Parser dbp(*ih);
	dbp.parse_dataBase(database);						//error return
}

									//add second arg database arg
void ParserHandler::load_doc(std::string path_to_doc){										//return error
	IndexedDoc_Parser idp(*ih);

	/*
		edit:	needs to be passed refrence database
				to feed to idp as second arg
														*/

	idp.parse(path_to_doc);								//error return
}

void ParserHandler::add_doc_to_dataBase(std::string new_path, database_packet &database){	//return error
	DataBase_Parser dbp(*ih);
	dbp.add_doc_to_dataBase(new_path, database);		//error return
}

void ParserHandler::remove_doc_from_dataBase(int selection, database_packet &database){		//return error
	DataBase_Parser dbp(*ih);
	dbp.remove_doc_from_dataBase(selection, database);	//error return
}

void ParserHandler::add_newDoc(string path_to_doc){											//return error
	NewDoc_Parser ndp(*ih);
	ndp.parse(path_to_doc);								//error return
}