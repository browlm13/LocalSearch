#include "ParserHandler.h"

//TMP
#include <iostream>

void ParserHandler::parse_dataBase(database_packet &database){
	DataBase_Parser dbp(*ih);
	dbp.parse_dataBase(database);
}

void ParserHandler::load_doc(std::string path_to_doc){
	IndexedDoc_Parser idp(*ih);
	idp.parse(path_to_doc);
}

void ParserHandler::add_doc_to_dataBase(std::string new_path, database_packet &database){
	DataBase_Parser dbp(*ih);
	dbp.add_doc_to_dataBase(new_path, database);
}

void ParserHandler::add_newDoc(string path_to_doc){
	NewDoc_Parser ndp(*ih);
	ndp.parse(path_to_doc);
}