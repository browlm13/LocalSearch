#ifndef PARSERHANDLER_H
#define PARSERHANDLER_H

#include <string>
#include "NewDoc_Parser.h"
//#include "IndexedDoc_Parser.h"
//#include "Page_Parser.h"
//#include "Info_Parser.h"
//#include "DataBase_Parser"
#include "../data-packets/Data_Packets.h"

class ParserHandler {

	IndexHandler *ih;

public:
	ParserHandler(IndexHandler &ih) : ih(&ih) {}

	void parse_dataBase(std::string path_to_dataBase, database_packet &database);
	void save_dataBase(std::string path_to_dataBase, database_packet database);

	void load_doc(std::string path_to_doc);
	void add_newDoc(std::string path_to_doc);
	page_packet fetch_page(word_packet wp);
	info_packet fetch_info(word_packet wp);
};


#endif	//PARSERHANDLER_H
