#include "DataBase_Parser.h"
#include "formatting/FormatText.h"
#include <iostream>

using namespace std;
//--------------------------
//				Events		
//			--------------------------

void DataBase_Parser::startTag_event(string &tag_name){
	if(tag_name.compare("dataStruct_type") == 0)
		set_collect_characters(true);

	if(tag_name.compare("title") == 0)
		set_collect_characters(true);

	if(tag_name.compare("full") == 0)
		set_collect_characters(true);

	if(tag_name.compare("index") == 0)
		set_collect_characters(true);
}

void DataBase_Parser::endTag_event(string &tag_name){

	if(tag_name.compare("dataStruct_type") == 0){
		int type;
		string raw_type = get_characters();
		type = atoi(raw_type.c_str());
		database_ptr->dataStruct_type = type;
	}

	if(tag_name.compare("title") == 0)
		dp.title = get_characters();

	if(tag_name.compare("full") == 0)
		dp.fullDoc_path = get_characters();

	if(tag_name.compare("index") == 0)
		dp.indexDoc_path = get_characters();

	if(tag_name.compare("document") == 0)
		database_ptr->indexed_docs.push_back(dp);
}

//--------------------------
//			parse	dataBase	
//			--------------------------
void DataBase_Parser::parse_dataBase(std::string path_to_dataBase,  database_packet &database_arg){
	database_ptr = &database_arg;
	_parse(path_to_dataBase, 0);	
}
//--------------------------
//			save	dataBase	
//			--------------------------
void DataBase_Parser::save_dataBase(std::string path_to_dataBase, database_packet database){
	open_file(path_to_dataBase);
	file.write(database.toString().c_str(), database.toString().size());
	close_file();
}