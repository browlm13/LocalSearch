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
	void startDoc_event() {}
	void startTag_event(std::string &tag_name);			
	void endTag_event(std::string &tag_name);
	void endDoc_event();		
	
public:
		//private caller
	void parse_dataBase(std::string path_to_dataBase, database_packet &database_arg);		//will remove path

	//void add_doc_to_dataBase(std::string new_path, database_packet &database);

	//will be PRIVATE function
	void save_dataBase(std::string path_to_dataBase, database_packet database_arg);			//will remove path
	//will be PRIVATE function

	DataBase_Parser(IndexHandler &ih) : ih(&ih) {}	
	~DataBase_Parser(){}
};

#endif //DATABASE_PARSER_H