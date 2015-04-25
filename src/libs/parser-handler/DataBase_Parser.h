#ifndef DATABASE_PARSER_H
#define DATABASE_PARSER_H

#include <string>
#include <vector>
#include "xmlshark/XMLShark.h"
#include "../data-packets/Data_Packets.h"

//--------------------------
//		DataBase_Parser		
//			--------------------------

class DataBase_Parser : public XMLShark {
private:
	doc_packet dp;
	int *dataStruct_type_ptr; 
	std::vector<doc_packet> *indexed_docs_ptr;

		//Events (called by Shark)
	void startDoc_event() {}
	void endDoc_event()	{}
	void startTag_event(std::string &tag_name);			
	void endTag_event(std::string &tag_name);				
	
public:
		//private caller
	void parse_dataBase(std::string path_to_dataBase, vector<doc_packet> &indexed_docs, int &dataStruct_type);

	DataBase_Parser(){}	
	~DataBase_Parser(){}
};

#endif //DATABASE_PARSER_H