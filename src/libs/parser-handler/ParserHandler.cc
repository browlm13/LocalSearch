#include "ParserHandler.h"

//TMP
#include <iostream>

void ParserHandler::parse_dataBase(database_packet &database){								//return error
	DataBase_Parser dbp(*ih);
	dbp.parse_dataBase(database);						//error return
}

void ParserHandler::close_docs(database_packet &database){
	DataBase_Parser dbp(*ih);
	dbp.close_docs(database);
}

void ParserHandler::load_doc(int selection, database_packet &database){										//return error
	IndexedDoc_Parser idp(*ih);
	idp.parse(selection, database);																					//error return
}

void ParserHandler::save(database_packet &database){	//return error
	DataBase_Parser dbp(*ih);
	dbp.save(database);		//error return
}

void ParserHandler::remove_doc_from_dataBase(int selection, database_packet &database){		//return error
	DataBase_Parser dbp(*ih);
	dbp.remove_doc_from_dataBase(selection, database);	//error return
}

void ParserHandler::add_newDoc(string path_to_doc, database_packet &database){											//return error
	NewDoc_Parser ndp(*ih);
	ndp.parse(path_to_doc, database);								//error return
}

vector<info_packet> ParserHandler::fetch_info(std::vector<word_packet> wps, database_packet &database){
	Info_Parser ip;
	return ip.parse(wps, database);
}