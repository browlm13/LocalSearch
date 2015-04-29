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

		//Events (called by Shark)
	void startDoc_event() {										//define start doc event in cc
		cout << "pass database refrence to indexedDoc parser, to set datastruct type durring start doc evenet.";
		ih->set_dataStruct(DataStuct_Types::AVL);				//line fixes, needs to be passed database_packet database_ptr
	}
	void endDoc_event()	{}
	void startTag_event(std::string &tag_name);			
	void endTag_event(std::string &tag_name);				
	
public:

		//private caller
	void parse(string path);									//needs to be passed

	IndexedDoc_Parser(IndexHandler &ih) 	: ih(&ih) {}	
	~IndexedDoc_Parser(){}
};

#endif //INDEXEDDOC_PARSER_H