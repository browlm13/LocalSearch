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

	//get saved docs
	void parse_dataBase(database_packet &database);								//return error

	//save doc
	void add_doc_to_dataBase(std::string new_path, database_packet &database);	//return error
	//delete doc
	void remove_doc_from_dataBase(int selection, database_packet &database);	//retuen error


			/*
				edit: add database_packet database refrence arg
					to load doc.								*/

	//load saved doc
	void load_doc(std::string path_to_doc, database_packet &database);										//return error
	//load external doc
	void add_newDoc(std::string path_to_doc);									//return error

	//load doc segment
	page_packet fetch_page(word_packet wp);										//not complete
	//load doc segment
	info_packet fetch_info(word_packet wp);										//not complete
};


#endif	//PARSERHANDLER_H
