#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include "xmlshark/XMLShark.h"
#include "../data-packets/Data_Packets.h"

//--------------------------
//		DataBase_Parser		
//			--------------------------

class DataBase_Parser : public XMLShark {
private:

	database_packet *database_ptr;
	doc_packet dp;

		//Events (called by Shark)
	void startDoc_event() {}
	void endDoc_event()	{}
	void startTag_event(std::string &tag_name);			
	void endTag_event(std::string &tag_name);		
	
public:
		//private caller
	void parse_dataBase(std::string path_to_dataBase, database_packet &database_arg);
	void save_dataBase(std::string path_to_dataBase, database_packet database_arg);

	DataBase_Parser(){}	
	~DataBase_Parser(){}
};

#endif //DATABASE_PARSER_H