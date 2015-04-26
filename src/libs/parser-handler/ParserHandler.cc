#include "ParserHandler.h"
#include "DataBase_Parser.h"


//TMP
#include <iostream>

void ParserHandler::parse_dataBase(std::string path_to_dataBase, database_packet &database){
	DataBase_Parser dbp;
	dbp.parse_dataBase(path_to_dataBase, database);
}

void ParserHandler::save_dataBase(std::string path_to_dataBase, database_packet database){
	std::cout << "wtf???";
	DataBase_Parser dbp;
	dbp.save_dataBase(path_to_dataBase, database);
}