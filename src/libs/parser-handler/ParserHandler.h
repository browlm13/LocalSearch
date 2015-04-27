#ifndef PARSERHANDLER_H
#define PARSERHANDLER_H

#include <string>

#include "NewDoc_Parser.h"
#include "IndexedDoc_Parser.h"
#include "DataBase_Parser.h"
//#include "Page_Parser.h"
//#include "Info_Parser.h"
#include "../data-packets/Data_Packets.h"

class ParserHandler {

	IndexHandler *ih;

public:
	ParserHandler(IndexHandler &ih) : ih(&ih) {}

	void parse_dataBase(database_packet &database);
	void add_doc_to_dataBase(std::string new_path, database_packet &database);

	void load_doc(std::string path_to_doc);
	void add_newDoc(std::string path_to_doc);
	page_packet fetch_page(word_packet wp);				//not complete
	info_packet fetch_info(word_packet wp);				//not complete
};


#endif	//PARSERHANDLER_H
