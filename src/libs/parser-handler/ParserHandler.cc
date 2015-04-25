#include "ParserHandler.h"
#include "DataBase_Parser.h"

void ParserHandler::parse_dataBase(std::string path_to_dataBase, vector<doc_packet> &indexed_docs, int &dataStruct_type){
	DataBase_Parser dbp;
	dbp.parse_dataBase(path_to_dataBase, indexed_docs, dataStruct_type);
}