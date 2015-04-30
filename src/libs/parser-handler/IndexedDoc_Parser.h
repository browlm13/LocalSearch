#ifndef INDEXEDDOC_PARSER_H
#define INDEXEDDOC_PARSER_H

//#include <string>
//#include <vector>
#include "xmlshark/XMLShark.h"
#include "../data-packets/Data_Packets.h"
#include "index-handler/IndexHandler.h"

		/*
			description:	sends over line
							by line to index handler
							t, gtf, tf, loc, p
														*/

//--------------------------
//		IndexedDoc_Parser	
//			--------------------------

class IndexedDoc_Parser : public XMLShark {

	word_packet wp;
	IndexHandler *ih;
	database_packet *database_ptr;

		//Events (called by Shark)
	void startDoc_event() {}
	void endDoc_event()	{}
	void startTag_event(std::string &tag_name);			
	void endTag_event(std::string &tag_name);				
	
public:

		//private caller
	void parse(int selection, database_packet &database);									//needs to be passed

	IndexedDoc_Parser(IndexHandler &ih) 	: ih(&ih) {}	
	~IndexedDoc_Parser(){}
};

#endif //INDEXEDDOC_PARSER_H