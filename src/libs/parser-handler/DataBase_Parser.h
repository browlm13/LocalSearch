#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include "xmlshark/XMLShark.h"
#include "index-handler/IndexHandler.h"
#include "../data-packets/Data_Packets.h"

//--------------------------
//		DataBase_Parser		
//			--------------------------

class DataBase_Parser : public XMLShark {
private:

	IndexHandler *ih;
	database_packet *database_ptr;
	doc_packet dp;

		//Events (called by Shark)
	void startDoc_event() {database_ptr->clear();}
	void startTag_event(std::string &tag_name);			
	void endTag_event(std::string &tag_name);
	void endDoc_event();		

	void save_dataBase();																//return error
	void delete_file(std::string path);													//return error
	
public:
		//private caller
	void parse_dataBase(database_packet &database_arg);									//return error
	void close_docs(database_packet &database_arg);
	void save(database_packet &database);			//return error
	void remove_doc_from_dataBase(int selection, database_packet &database);			//return error

	DataBase_Parser(IndexHandler &ih) : ih(&ih) {}	
	~DataBase_Parser(){}
};

#endif //DATABASE_PARSER_H