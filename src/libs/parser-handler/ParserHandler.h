#ifndef PARSERHANDLER_H
#define PARSERHANDLER_H

#include <string>

#include "NewDoc_Parser.h"
#include "IndexedDoc_Parser.h"
#include "DataBase_Parser.h"
//#include "Page_Parser.h"
#include "Info_Parser.h"
#include "../data-packets/Data_Packets.h"

class ParserHandler {

	IndexHandler *ih;

public:
	ParserHandler(IndexHandler &ih) : ih(&ih) {}

	//get saved docs
	void parse_dataBase(database_packet &database);								//return error

	//save doc
	void save(database_packet &database);	//return error
	//delete doc
	void remove_doc_from_dataBase(int selection, database_packet &database);	//retuen error

	void close_docs(database_packet &database);

	//load saved doc
	void load_doc(int selection, database_packet &database);										//return error
	//load external doc
	void add_newDoc(std::string path_to_doc, database_packet &database);									//return error

	//load doc segment
	page_packet fetch_page(word_packet wp);										//not complete
	
	//load doc segments
	std::vector<info_packet> fetch_info(std::vector<word_packet> wps, database_packet &database);
};


#endif	//PARSERHANDLER_H
