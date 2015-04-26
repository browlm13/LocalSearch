#include "ParserHandler.h"
#include "DataBase_Parser.h"


//TMP
#include <iostream>

void ParserHandler::parse_dataBase(std::string path_to_dataBase, database_packet &database){		//will remove path
	DataBase_Parser dbp(*ih);
	dbp.parse_dataBase(path_to_dataBase, database);
}

/*
//add new files, updates database, and refrence, saves database wich calls index to save
void ParserHandler::add_doc_to_dataBase(std::string new_path, database_packet &database){
	DataBase_Parser dbp(*ih);
	dbp.add_doc_to_dataBase(new_path, database);
}
*/
//to be removed for house keeping
void ParserHandler::save_dataBase(std::string path_to_dataBase, database_packet database){
	DataBase_Parser dbp(*ih);
	dbp.save_dataBase(path_to_dataBase, database);
}
//to be removed for house keeping

void ParserHandler::add_newDoc(string path_to_doc){
	NewDoc_Parser ndp(*ih);
	ndp.parse(path_to_doc);
}